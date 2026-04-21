#pragma once

#include <string>
#include <cstdlib>
#include <ncurses.h>
#include "Mon.h"
#include "Character.h"
#include "PokemonFactory.h"


class Battle {
public:
    /**
     * Creates a battle controller.
     *  - pc: player character
     *  - opponent: either a wild Pokémon OR a trainer Character
     *  - trainerBattle: true if opponent is a trainer
     *  - header: text shown at top of battle UI
     *
     * Battle does NOT take ownership of any pointer.
     */
    Battle(Character* pc,
           Character* opponent,
           Mon* wild,
           bool trainerBattle,
           const std::string& header);

    /**
     * Entry point.
     * Starts the full battle UI loop and returns
     * when the battle ends (win, loss, run, or catch).
     */
    void start();

private:
    // ===================== STATE =====================
    Character* m_player;        // non-owning
    Character* m_trainer;       // non-owning, null for wild battle
    Mon*       m_wild;          // non-owning, null for trainer battle
    bool       m_isTrainerBattle;
    std::string m_header;

    Mon* m_playerActive;
    Mon* m_enemyActive;

    // ===================== UI =====================
    void drawEnemyPanel(Mon* enemy);

    void drawPlayerPanel(Mon* player);
    void drawBattleFrame();
    void printMessage(const std::string& msg);
    void clearMessageBox();
    void drawActionMenu(bool trainerBattle);

    // ===================== MENUS =====================
    int  choosePlayerMoveUI(Mon* player);
    Mon* switchPokemonUI(Character* pc);
    bool bagUI();

    // ===================== FLOW =====================
    void handleTurn();
    void handleFight();
    void handleBag();
    void handleSwitch();
    bool handleRun();

    // ===================== HELPERS =====================
    static void executeTurn(Mon* first, int firstMove,
                            Mon* second, int secondMove);

    static int chooseRandomMove(Mon* m);
    static bool attemptRun();

    static Mon* firstAlive(Character* c);
    static bool partyDefeated(Character* c);
};