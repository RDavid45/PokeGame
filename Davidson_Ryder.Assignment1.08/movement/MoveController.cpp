#include "MoveController.h"
#include <cassert>
#include <cstdlib>
#include <ncurses.h>
#include "PokemonFactory.h"

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
static void handleEncounter(Character *pc, int dist)
{
  (void)pc; // unused for now, but needed for future battling

  PokemonFactory *factory = PokemonFactory::getInstance();

  int minLevel, maxLevel;

  if (dist <= 200) {
    minLevel = 1;
    maxLevel = dist / 2;
  } else {
    minLevel = (dist - 200) / 2;
    maxLevel = 100;
  }

  if (maxLevel < minLevel) {
    maxLevel = minLevel;
  }

  int level = minLevel + rand() % (maxLevel - minLevel + 1);
  Mon *m = factory->generatePokemon(level);

  keypad(stdscr, TRUE);

  bool inBattle = true;
  while (inBattle) {
    clear();

    int row = 0;

    mvprintw(row++, 0, "----------------------------------------");
    mvprintw(row++, 0, "A wild %s appeared!", m->get_name().c_str());
    mvprintw(row++, 0, "Level %d  Gender: %c%s",
             m->get_level(),
             m->get_gender(),
             m->get_shiny() ? "  *SHINY*" : "");
    mvprintw(row++, 0, "----------------------------------------");

    row++; // blank line

    mvprintw(row++, 0, "Stats:");
    mvprintw(row++, 2, "HP : %d", m->get_hp());
    mvprintw(row++, 2, "Atk: %d   Def: %d", m->get_atk(), m->get_def());
    mvprintw(row++, 2, "SpA: %d   SpD: %d", m->get_satk(), m->get_sdef());
    mvprintw(row++, 2, "Spe: %d", m->get_spd());

    row++; // blank line

    mvprintw(row++, 0, "Moves:");
    for (int i = 0; i < (int) m->get_moves().size(); i++) {
      mvprintw(row++, 2, "- %s", m->get_moves().get(i).name.c_str());
    }

    row++;
    mvprintw(row, 0, "Press 'q' to run away");

    refresh();

    int ch = getch();
    if (ch == 'q') {
      inBattle = false;
    }
  }

  delete m;
  clear();
}

/*----------------------------------------------------------*/
static void handleBattle(Character*pc, Character* npc, int dist)
{
    PokemonFactory* factory = PokemonFactory::getInstance();

    // Only generate Pokémon once
    if (npc->getPartySize() == 0) {

        int n = 0;
        while (n < 6) {
            // Trainer always gets first Pokémon
            if (n == 0) {
                n = pc->getPartySize();
                continue;
            }

            // 60% chance to get (n+1)th Pokémon
            if (rand() % 100 < 60) {
                n++;
            } else {
                break;
            }
        }

        for (int i = 0; i < n; ++i) {
            int minLevel, maxLevel;

            if (dist <= 200) {
                minLevel = 1;
                maxLevel = dist / 2;
            } else {
                minLevel = (dist - 200) / 2;
                maxLevel = 100;
            }

            if (maxLevel < minLevel) {
                maxLevel = minLevel;
            }

            int level = minLevel + rand() % (maxLevel - minLevel + 1);
            npc->addMon(factory->generatePokemon(level));
        }
    }

    clear();
    keypad(stdscr, TRUE);

    bool inBattle = true;
    while (inBattle) {
        clear();

        mvprintw(0, 0, "A Trainer challenges you!");
        mvprintw(1, 0, "NPC Party:");

        for (int i = 0; i < npc->getPartySize(); ++i) {
            Mon* mon = npc->getMon(i);
            mvprintw(3 + i, 2, "%d. %s (Lv. %d)",
                     i + 1,
                     mon->get_name().c_str(),
                     mon->get_level());
        }

        mvprintw(20, 0, "Press 'q' to end battle and defeat trainer.");
        refresh();

        int ch = getch();
        switch (ch) {
            case 'q':
                inBattle = false;
                break;
            default:
                break;
        }
    }

    clear();
    mvprintw(22, 0, "Trainer Defeated at (%d, %d)",
             npc->getHPos(), npc->getVPos());
    refresh();

    npc->defeat();
    clear();
}

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
            if (cmap.at(nr, nc)) continue;

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
            if (cmap.at(nr, nc)) continue;

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
        if (cmap.at(nr, nc)->getNPCType() == CharacterType::TrainerLogic && !ch->isDefeated())
            handleBattle(cmap.at(nr, nc), ch, dist);

        else if (ch->getNPCType() == CharacterType::TrainerLogic && !cmap.at(nr, nc)->isDefeated())
            handleBattle(ch, cmap.at(nr, nc), dist);

        if (ch->getNPCType() != CharacterType::TrainerLogic)
            scheduleNextMove(m);
        return -1;
    }

    cmap.placeCharacter(nullptr, ch->getVPos(), ch->getHPos());
    cmap.placeCharacter(ch, nr, nc);
    if(ch->getNPCType() == CharacterType::TrainerLogic && b.getTerrainAT(nr, nc) == ':' && rand() %100 < 10){
        handleEncounter(ch, dist);
    }

    assert(cmap.at(ch->getVPos(), ch->getHPos()) == ch);



    if (ch->getType() == Type::Trainer)
        costs.updateCosts(b, nr, nc);

    if (ch->getNPCType() != CharacterType::TrainerLogic)
        scheduleNextMove(m);

    return 0;
}