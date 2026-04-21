#include "MoveController.h"
#include <cassert>
#include <cstdlib>
#include <ncurses.h>
#include "Battle.h"

/*----------------------------------------------------------*/
MoveController::MoveController(Board& b,
                               MovementCosts& mc,
                               CharacterMap& cmap, int dist)
    : b(b), costs(mc), cmap(cmap), dist(dist)
{
    heap = new Heap<Move>();
}

MoveController::~MoveController()
{
    delete heap;
}

Move MoveController::getNextMove(){
    assert(!heap->isEmpty());
    return heap->pop();
}

/*----------------------------------------------------------*/
inline bool MoveController::inBounds(int r, int c)
{
    return r > 0 && r < 20 && c > 0 && c < 79;
}

/*----------------------------------------------------------*/
int MoveController::scheduleMove(const Move& m)
{
    heap->add(m);
    return 0;
}

/*----------------------------------------------------------*/
int MoveController::findNextDirection(int r, int c) const
{
    static const int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    static const int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    int choices[8];
    int cnt = 0;

    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (!inBounds(nr, nc)) continue;
        if (costs.otherAt(nr, nc).weight > 100) continue;
        choices[cnt++] = i;
    }

    return cnt > 0 ? choices[rand() % cnt] : -1;
}

/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
int MoveController::scheduleNextMove(Move& m)
{
    Character* ch = m.c;

    static const int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    static const int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    int r = ch->getVPos();
    int c = ch->getHPos();

    auto STALL = [&] {
        m.dx = 0;
        m.dy = 0;
        m.when += 10;
    };

    switch (ch->getNPCType()) {

    /* ========================= HIKER ========================= */
    case CharacterType::HikerLogic: {
        int bestI = -1;
        int bestCost = MovementCosts::INF;
        int start = rand() % 8;

        for (int k = 0; k < 8; k++) {
            int i  = (start + k) & 7;
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (!inBounds(nr, nc)) continue;
            if (cmap.at(nr, nc) && cmap.at(nr, nc)->getNPCType() != CharacterType::TrainerLogic) continue;

            const Cost& tile = costs.hikerAt(nr, nc);
            if (tile.cost >= MovementCosts::INF) continue;

            if (tile.cost < bestCost) {
                bestCost = tile.cost;
                bestI = i;
            }
        }

        int hereCost = costs.hikerAt(r, c).cost;

        if (bestI >= 0 && bestCost < hereCost) {
            m.dx = dc[bestI];
            m.dy = dr[bestI];
            m.when += costs.hikerAt(r + m.dy, c + m.dx).weight;
        } else {
            STALL();
        }
        break;
    }

    /* ========================= RIVAL ========================= */
    case CharacterType::RivalLogic: {
        int bestI = -1;
        int bestCost = MovementCosts::INF;
        int start = rand() % 8;

        for (int k = 0; k < 8; k++) {
            int i  = (start + k) & 7;
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (!inBounds(nr, nc)) continue;
            if (cmap.at(nr, nc) && cmap.at(nr, nc)->getNPCType() != CharacterType::TrainerLogic) continue;

            const Cost& tile = costs.rivalAt(nr, nc);
            if (tile.cost < bestCost) {
                bestCost = tile.cost;
                bestI = i;
            }
        }

        if (bestI >= 0 &&
            bestCost < costs.rivalAt(r, c).cost) {
            m.dx = dc[bestI];
            m.dy = dr[bestI];
            m.when += costs.rivalAt(r + m.dy, c + m.dx).weight;
        } else {
            STALL();
        }
        break;
    }

    /* ======================= SENTINAL ======================== */
    case CharacterType::SentinelLogic:
        m.dx = 0;
        m.dy = 0;
        m.when += MovementCosts::INF;
        break;

    /* ======================= WANDERER ======================== */
    case CharacterType::WandererLogic: {
        int nr = r + m.dy;
        int nc = c + m.dx;

        bool canContinue =
            !(nr == r && nc == c) &&
            inBounds(nr, nc) &&
            b.getTerrainAT(r, c) == b.getTerrainAT(nr, nc) &&
            costs.otherAt(nr, nc).weight < 100;

        if (!canContinue) {
            int i = findNextDirection(r, c);
            if (i < 0) {
                STALL();
                break;
            }
            m.dx = dc[i];
            m.dy = dr[i];
            nr   = r + m.dy;
            nc   = c + m.dx;
        }

        m.when += costs.otherAt(nr, nc).weight;
        break;
    }

    /* ======================= EXPLORER ======================== */
    case CharacterType::ExplorerLogic: {
        int nr = r + m.dy;
        int nc = c + m.dx;

        if (!inBounds(nr, nc) ||
            costs.otherAt(nr, nc).weight >= 100 ||
            cmap.at(nr, nc))
        {
            int i = findNextDirection(r, c);
            if (i < 0) {
                STALL();
                break;
            }
            m.dx = dc[i];
            m.dy = dr[i];
            nr = r + m.dy;
            nc = c + m.dx;
        }

        m.when += costs.otherAt(nr, nc).weight;
        break;
    }

    /* ========================= PACER ========================= */
    case CharacterType::PacerLogic: {
        if (m.dx == 0 && m.dy == 0) {
            int i = findNextDirection(r, c);
            if (i < 0) {
                STALL();
                break;
            }
            m.dx = dc[i];
            m.dy = dr[i];
        }

        int nr = r + m.dy;
        int nc = c + m.dx;

        if (!inBounds(nr, nc) ||
            costs.otherAt(nr, nc).weight >= 100 ||
            cmap.at(nr, nc))
        {
            m.dx = -m.dx;
            m.dy = -m.dy;
            nr = r + m.dy;
            nc = c + m.dx;

            if (!inBounds(nr, nc) ||
                costs.otherAt(nr, nc).weight >= 100 ||
                cmap.at(nr, nc))
            {
                STALL();
                break;
            }
        }

        m.when += costs.otherAt(nr, nc).weight;
        break;
    }

    default:
        STALL();
        break;
    }

    heap->add(m);
    return 0;
}

Mon* MoveController::getRandomMon(){
    PokemonFactory* factory = PokemonFactory::getInstance();

        int minLevel, maxLevel;
        if (dist <= 200) {
            minLevel = 1;
            maxLevel = dist / 2;
        } else {
            minLevel = (dist - 200) / 2;
            maxLevel = 100;
        }

        if (maxLevel < minLevel)
            maxLevel = minLevel;

        int level = minLevel + rand() % (maxLevel - minLevel + 1);
        Mon* wild = factory->generatePokemon(level);
        return wild;
}


int MoveController::handleMove(Move& m)
{
    Character* ch = m.c;

    int nr = ch->getVPos() + m.dy;
    int nc = ch->getHPos() + m.dx;

    if (!inBounds(nr, nc)) {
        if (ch->getNPCType() != CharacterType::TrainerLogic)
            scheduleNextMove(m);
        return -1;
    }

    if (cmap.at(nr, nc) && cmap.at(nr, nc) != ch) {

        Character* a = ch;
        Character* b = cmap.at(nr, nc);

        if (a->getPartySize() == 0){
            a->addMon(getRandomMon());
            while (a->getPartySize() < 6){
                if (rand() % 100 < 60){
                    a->addMon(getRandomMon());
                } else {
                    break;
                }
            }
        }
        if (b->getPartySize() == 0){
            b->addMon(getRandomMon());
            while (b->getPartySize() < 6){
                if (rand() % 100 < 60){
                    b->addMon(getRandomMon());
                } else {
                    break;
                }
            }
        }
        // Trainer (map NPC) vs player
        if (b->getNPCType() == CharacterType::TrainerLogic && !a->isDefeated()) {
            Battle battle(
                b,          // player
                a,          // trainer
                nullptr,    // no wild mon
                true,       // trainer battle
                "Trainer Battle"
            );
            battle.start();
        }
        // Player trainer walking into undefeated trainer
        else if (a->getNPCType() == CharacterType::TrainerLogic && !b->isDefeated()) {
            Battle battle(
                a,          // player
                b,          // trainer
                nullptr,
                true,
                "Trainer Battle"
            );
            battle.start();
        }

        // Non‑trainer NPCs still keep moving
        if (a->getNPCType() != CharacterType::TrainerLogic){
            scheduleNextMove(m);
        }

        return -1;
    }


    cmap.placeCharacter(nullptr, ch->getVPos(), ch->getHPos());
    cmap.placeCharacter(ch, nr, nc);
    if (ch->getNPCType() == CharacterType::TrainerLogic &&b.getTerrainAT(nr, nc) == ':' && rand() % 100 < 10)
    {
        Mon* wild = getRandomMon();

        // Start battle via new Battle class
        Battle battle(
            ch,         // player
            nullptr,    // no trainer
            wild,       // wild Pokémon
            false,      // not trainer battle
            "A wild " + wild->get_name() + " appeared!"
        );

        battle.start();
    }

    assert(cmap.at(ch->getVPos(), ch->getHPos()) == ch);



    if (ch->getType() == Type::Trainer)
        costs.updateCosts(b, nr, nc);

    if (ch->getNPCType() != CharacterType::TrainerLogic)
        scheduleNextMove(m);

    return 0;
}