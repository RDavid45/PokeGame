#include "Battle.h"
#include "PokemonFactory.h"
#include <ncurses.h>

// =====================Constructor=================

Battle::Battle(Character* pc,
               Character* opponent,
               Mon* wild,
               bool trainerBattle,
               const std::string& header)
    : m_player(pc),
      m_trainer(opponent),
      m_wild(wild),
      m_isTrainerBattle(trainerBattle),
      m_header(header),
      m_playerActive(nullptr),
      m_enemyActive(nullptr)
{
}

// ======================= UI =======================

void Battle::drawBattleFrame()
{
    clear();

    // Enemy box
    mvhline(0, 0, '-', 80);
    mvhline(6, 0, '-', 80);
    mvvline(0, 79, '|', 7);

    // Player box
    mvhline(7, 0, '-', 80);
    mvhline(12, 0, '-', 80);

    // Bottom split
    mvhline(13, 0, '-', 80);
    mvvline(13, 56, '|', 11);
    mvhline(23, 0, '-', 80);

    refresh();
}

void Battle::drawEnemyPanel(Mon* enemy)
{
    int r = 1;
    int c =  56; // 56

    mvprintw(r, c, m_header.c_str());
    mvprintw(r+1, c, "-------------");

    mvprintw(r+2, c, "%s Lv:%d",
             enemy->get_name().c_str(),
             enemy->get_level());

    mvprintw(r+3, c, "HP: %d / %d",
             enemy->get_currentHp(),
             enemy->get_hp());
}


void Battle::drawPlayerPanel(Mon* player)
{
    int r = 8;
    int c = 2;

    mvprintw(r, c, "%s Lv:%d",
             player->get_name().c_str(),
             player->get_level());

    mvprintw(r+1, c, "HP: %d / %d",
             player->get_currentHp(),
             player->get_hp());
}

void Battle::drawActionMenu(bool trainerBattle)
{
    int r = 15;
    int c = 60;

    mvprintw(r, c, "1) Fight");
    mvprintw(r+1, c, "2) Bag");
    mvprintw(r+2, c, "3) Pokémon");

    if (!trainerBattle)
        mvprintw(r+3, c, "4) Run");
}

void Battle::clearMessageBox()
{
    for (int r = 14; r < 23; r++) {
        move(r, 1);
        clrtoeol();
    }
}

void Battle::printMessage(const std::string& msg)
{
    clearMessageBox();
    mvprintw(15, 2, "%s", msg.c_str());
    refresh();
}





// ======================= MENUS =======================

Mon* Battle::switchPokemonUI(Character* pc)
{
    while (true) {
        clear();
        mvprintw(0, 0, "Choose a Pokemon:");
        mvprintw(1, 0, "------------------");

        for (int i = 0; i < pc->getPartySize(); ++i) {
            Mon* m = pc->getMon(i);
            mvprintw(3 + i, 0, "%d) %-10s HP: %d/%d%s",
                     i + 1,
                     m->get_name().c_str(),
                     m->get_currentHp(),
                     m->get_hp(),
                     m->get_currentHp() <= 0 ? " (KO)" : "");
        }

        mvprintw(22, 0, "Press number or TAB to cancel");
        int ch = getch();

        if (ch == '\t')
            return nullptr;

        int idx = ch - '1';
        if (idx >= 0 && idx < pc->getPartySize())
            return pc->getMon(idx);
    }
}

bool Battle::bagUI()
{
    while (true) {
        clear();
        auto bag = m_player->getBag();

        mvprintw(0, 0, "Bag");
        mvprintw(1, 0, "-----------------");
        mvprintw(3, 0, "1) Potion  x%d", bag[0]);
        mvprintw(4, 0, "2) Revive  x%d", bag[1]);

        if (!m_isTrainerBattle)
            mvprintw(5, 0, "3) Pokeball x%d", bag[2]);

        mvprintw(22, 0, "Select item or TAB to cancel");

        int ch = getch();
        if (ch == '\t')
            return false;

        int item = ch - '1';
        if (item < 0 || item > 2)
            continue;

        Mon* target = nullptr;
        if (item < 2) {
            target = switchPokemonUI(m_player);
            if (!target) continue;
        }

        bool used = false;

        if (item == 0 && target->get_currentHp() > 0)
            used = m_player->usePotion(target);
        else if (item == 1)
            used = m_player->useRevive(target);
        else if (item == 2 && !m_isTrainerBattle)
            return m_player->throwBall(m_enemyActive);

        if (used)
            return false;
    }
}

int Battle::choosePlayerMoveUI(Mon* player)
{
    auto& moves = player->get_moves();
    clearMessageBox();

    mvprintw(14, 2, "Choose a move:");
    mvprintw(15, 2, "---------------");

    for (int i = 0; i < (int)moves.size(); ++i) {
        mvprintw(17 + i, 2,
                 "%d) %s",
                 i + 1,
                 moves.get(i).name.c_str());
    }

    int ch = getch();
    if (ch == '\t')
        return -1;

    return ch - '1';
}


// ======================= HELPERS =======================

Mon* Battle::firstAlive(Character* c)
{
    for (int i = 0; i < c->getPartySize(); ++i)
        if (c->getMon(i)->get_currentHp() > 0)
            return c->getMon(i);
    return nullptr;
}

int Battle::chooseRandomMove(Mon* m)
{
    auto& moves = m->get_moves();
    return moves.size() == 0 ? -1 : rand() % moves.size();
}

bool Battle::attemptRun()
{
    return (rand() % 100) < 50;
}

void Battle::executeTurn(Mon* first, int firstMove,
                         Mon* second, int secondMove)
{
    if (firstMove >= 0)
        first->use_move(second, firstMove);

    if (second->get_currentHp() <= 0)
        return;

    if (secondMove >= 0)
        second->use_move(first, secondMove);
}

// ======================= MAIN LOOP =======================

void Battle::start()
{
    keypad(stdscr, TRUE);
    noecho();

    m_playerActive = firstAlive(m_player);
    m_enemyActive  = m_isTrainerBattle
                     ? firstAlive(m_trainer)
                     : m_wild;

    while (true) {
        if (!m_playerActive) {
            clear();
            mvprintw(22, 0, "You blacked out!");
            m_player->defeat();
            getch();
            return;
        }

        if (!m_enemyActive) {
            clear();
            mvprintw(22, 0, m_isTrainerBattle ? "Trainer defeated!" : "Victory!");
            if (m_isTrainerBattle)
                m_trainer->defeat();
            getch();
            return;
        }

        clear();
        drawEnemyPanel(m_enemyActive);
        drawPlayerPanel(m_playerActive);

        mvprintw(21, 0, "[1] Fight  [2] Bag  [3] Pokemon");
        if (!m_isTrainerBattle)
            mvprintw(22, 0, "[4] Run");

        int ch = getch();

        if (ch == '1') {
            int pMove = choosePlayerMoveUI(m_playerActive);
            if (pMove < 0) continue;

            int eMove = chooseRandomMove(m_enemyActive);

            bool playerFirst =
                m_playerActive->get_spd() > m_enemyActive->get_spd() ||
                (m_playerActive->get_spd() == m_enemyActive->get_spd() && rand() % 2);

            if (playerFirst)
                executeTurn(m_playerActive, pMove, m_enemyActive, eMove);
            else
                executeTurn(m_enemyActive, eMove, m_playerActive, pMove);
        }
        else if (ch == '2') {
            bool ended = bagUI();
            if (ended) return;
            m_enemyActive->use_move(
                m_playerActive,
                chooseRandomMove(m_enemyActive));
        }
        else if (ch == '3') {
            Mon* swap = switchPokemonUI(m_player);
            if (swap) {
                m_playerActive = swap;
                m_enemyActive->use_move(
                    m_playerActive,
                    chooseRandomMove(m_enemyActive));
            }
        }
        else if (ch == '4' && !m_isTrainerBattle) {
            if (attemptRun()) return;
            m_enemyActive->use_move(
                m_playerActive,
                chooseRandomMove(m_enemyActive));
        }

        if (m_playerActive->get_currentHp() <= 0)
            m_playerActive = firstAlive(m_player);

        if (m_enemyActive->get_currentHp() <= 0)
            m_enemyActive = m_isTrainerBattle
                            ? firstAlive(m_trainer)
                            : nullptr;
    }
}