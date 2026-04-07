#include "Chunk.h"
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <ncurses.h>
#include "Colors.h"

Chunk::Chunk(int vPos, int hPos, int n, int s, int w, int e) : 
board(vPos, hPos, n, s, w, e), costMap(board), characterMap(), playerMove() ,hPos(hPos), vPos(vPos), hasSpawned(false) {
    controller = new MoveController(board, costMap,  characterMap);

    
}
Chunk::~Chunk(){
    
    for (int r = 0; r < Board::HEIGHT; ++r) {
        for (int c = 0; c < Board::WIDTH; ++c) {
            Character* ch = characterMap.at(r, c);
            if (ch && ch->isNPC()) {
                delete ch;
            }
        }
    }
    delete controller;

}


void Chunk::processUntilTime(int barrierTime)
{
    while (true) {
        Move m = controller->getNextMove();

        // Stop if this move is scheduled after the barrier
        if (m.when > barrierTime) {
            controller->scheduleMove(m);
            return;
        }

        controller->handleMove(m);
        displayChunk();
    }
}


Move& Chunk::placePlayer(Character *pc, int r, int c) {
    characterMap.placeCharacter(pc, r, c);
    costMap.updateCosts(board, r, c);
    playerMove.c = pc;
    genNPCsIfNeeded();
    return playerMove;
}

void Chunk::removePlayer(){
    for (int i = 0; i < Board::HEIGHT;i++){
        for (int j=0; j < Board::WIDTH; j++){
            if (characterMap.at(i,j) && characterMap.at(i,j)->getType() == Type::Trainer){
                characterMap.placeCharacter(nullptr, i, j);
            }
        }
    }
}

bool Chunk::movePlayer(Move &m)
{
    int r  = m.c->getVPos();
    int c  = m.c->getHPos();
    int nr = r + m.dy;
    int nc = c + m.dx;

    if (costMap.trainerAt(nr, nc).weight > 100)
        return false;

    // Finalize player's move timing
    m.when += costMap.trainerAt(nr, nc).weight;

    // Schedule the player move
    controller->scheduleMove(m);

    // ✅ Advance world up to player's time
    processUntilTime(m.when);

    return true;
}


void Chunk::displayChunk() const{
    clear();

    mvprintw(0, 0, "Current pos (%d, %d)", hPos - 200, vPos - 200);

    int start_row = 1;
    int start_col = 0;


    int drawable_rows = Board::HEIGHT;
    int drawable_cols = Board::WIDTH;

    for (int i = 0; i < drawable_rows; i++) {
        move(start_row + i, start_col);
        for (int j = 0; j < drawable_cols; j++) {
            char ch;
            short pair = 0;
            attr_t attrs = A_NORMAL;

            if (characterMap.at(i, j)) {
                ch = characterMap.at(i, j)->getIcon();
                pair = Colors::CHARACTER;
                attrs |= A_BOLD;
            } else {
                ch = board.getTerrainAT(i, j);
                switch (ch) {
                    case '%': pair = Colors::ROCK; break;     
                    case '~': pair = Colors::WATER; break;    
                    case ':': pair = Colors::TGRASS; break;   
                    case '.':
                        pair = Colors::SGRASS;                  
                        attrs |= A_BOLD;                   
                        break;
                    case '^': pair = Colors::FOREST; break;   
                    case 'm': pair = Colors::MART; break; 
                    case 'c': pair = Colors::CENTER; break;     
                    default:
                        pair = 0;                          
                        break;
                }
            }

            if (pair != 0) attron(COLOR_PAIR(pair) | attrs);
            addch((chtype)ch);
            if (pair != 0) attroff(COLOR_PAIR(pair) | attrs);
        }
    }

    refresh();
}


char Chunk::iconFor(CharacterType t) {
    switch (t) {
        case CharacterType::HikerLogic:     return 'h';
        case CharacterType::RivalLogic:     return 'r';
        case CharacterType::PacerLogic:     return 'p';
        case CharacterType::WandererLogic:  return 'w';
        case CharacterType::SentinelLogic:  return 's';
        case CharacterType::ExplorerLogic:  return 'e';
        default:             return '?';
    }
}

CharacterType Chunk::randomBehavior() {
    static const CharacterType pool[6] = {
        CharacterType::HikerLogic,
        CharacterType::RivalLogic,
        CharacterType::PacerLogic,
        CharacterType::WandererLogic,
        CharacterType::SentinelLogic,
        CharacterType::ExplorerLogic
    };
    return pool[rand() % 6];
}

Type Chunk::costCategoryFor(CharacterType t) {
    switch (t) {
        case CharacterType::HikerLogic: return Type::Hiker;
        case CharacterType::RivalLogic: return Type::Rival;
        default:         return Type::Other;
    }
}

bool Chunk::isOccupied(int r, int c) const {
    return characterMap.at(r,c) != nullptr;
}

bool Chunk::canSpawn(Type cc, int r, int c) const {
    int cost;
    if (isOccupied(r, c)) return false;
    switch (cc)
    {
    case Type::Hiker:
        cost = costMap.hikerAt(r,c).cost;
        break;
    
    case Type::Rival:
        cost = costMap.rivalAt(r,c).cost;
        break;
    
    default:
        cost = costMap.otherAt(r,c).cost;
        break;
    }
    if (cost >= MovementCosts::INF) {return false;}
    return true;
}

/* ---------- NPC spawning ---------- */

int Chunk::generateNPCs(int count) {
    int placed = 0; int failed_attempts = 0;
    int max_attempts = count * 50;

    while (placed < count && failed_attempts < max_attempts) {
        CharacterType npc;
        Type cc;

        if (placed == 0) {
            npc = CharacterType::RivalLogic;
        } else if (placed == 1) {
            npc = CharacterType::HikerLogic;
        } else {
            npc = randomBehavior();
        }

        cc = costCategoryFor(npc);

        int r = (rand() % 19) + 1;
        int c = (rand() % 78) + 1;

        if (!canSpawn(cc, r, c)) {
            failed_attempts++;
            continue;
        }

        char icon = iconFor(npc);
        Character* ch = new Character(icon, npc, cc);

        characterMap.placeCharacter(ch, r, c); 

        Move m(ch, 0, 0, 0);
        controller->scheduleMove(m);

        placed++;
    }
    return placed;
}

int Chunk::genNPCsIfNeeded() {
    if (!hasSpawned) {
        hasSpawned = true;
        return generateNPCs(10);
    }
    return -1;
}

void Chunk::handleCenter(const Character& pc)const{
    if (board.getTerrainAT(pc.getVPos(), pc.getHPos()) != 'c') {return;}
    clear();
    mvprintw(0, 0, "%s", "Welcome to the Pokemon Center, press left to leave");
    int32_t key;
    while (1){
        key = getch();
        switch (key)
        {
        case KEY_LEFT:
            displayChunk();
            return;
        default:
            break;
        }
    }
}
    
void Chunk::printTrainerInfo(const Character& pc,
                      const Character& npc) const
{
    int dh = npc.getHPos() - pc.getHPos();
    int dv = npc.getVPos() - pc.getVPos();

    int mag_v = std::abs(dv);
    int mag_h = std::abs(dh);

    std::ostringstream out;
    out << npc.getIcon() << ' '
        << mag_v << ' ' << (dv <= 0 ? "north" : "south")
        << ", "
        << mag_h << ' ' << (dh <= 0 ? "west" : "east");

    addstr(out.str().c_str());
}

int min(const int i, const int j){
    if (i < j){return i;}
    return j;
}


void Chunk::handleShowTrainers(const Character &pc) const {
    int active = 1;

    int title_row = 0;
    int list_start_row = 1;

    ArrayList<const Character*> trainers; 

    
    for (int r = 0; r < Board::HEIGHT; ++r) {
        for (int c = 0; c < Board::WIDTH; ++c) {
            Character* npc = characterMap.at(r, c);
            if (npc && npc->isNPC()) {
                trainers.add(npc);
            }
        }
    }

    int numTrainers = static_cast<int>(trainers.size());
    int startAt = 0;

    int rows = getmaxy(stdscr);
    int visible_rows = rows - list_start_row;
    if (visible_rows < 0) visible_rows = 0;

    auto render = [&] {
        erase();
        mvprintw(title_row, 0, "Trainers (ESC to exit)");

        int to_show = min(visible_rows,
                          numTrainers - startAt);

        for (int i = 0; i < to_show; ++i) {
            const Character* npc = trainers[startAt + i];
            move(list_start_row + i, 0);
            printTrainerInfo(pc, *npc);
        }

        refresh();
    };

    render();

    while (active) {
        int key = getch();

        switch (key) {
            case KEY_UP:
                if (startAt > 0) {
                    --startAt;
                    render();
                }
                break;

            case KEY_DOWN:
                if (startAt + visible_rows < numTrainers) {
                    ++startAt;
                    render();
                }
                break;

            case 27: // ESC
                active = false;
                break;

            default:
                break;
        }
    }
    displayChunk();
}
