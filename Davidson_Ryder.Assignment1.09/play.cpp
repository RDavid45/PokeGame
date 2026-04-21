#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <ncurses.h>
#include <iostream>
#include "Map.h"
#include "Colors.h"
#include "PokemonFactory.h"
#include "Pokemon.h"

void chooseStarter(Character *pc) {
  PokemonFactory *factory = PokemonFactory::getInstance();

  // Generate three level-1 Pokémon
  Mon *starters[3];
  for (int i = 0; i < 3; i++) {
    starters[i] = factory->generatePokemon(50);
  }

  clear();
  mvprintw(0, 0, "Choose your starter Pokemon:");
  mvprintw(1, 0, "--------------------------------");

  for (int i = 0; i < 3; i++) {
    Mon *m = starters[i];
    int row = 3 + i * 6;

    mvprintw(row, 0, "%d) %s  (Lv %d, %c)",
             i + 1,
             m->get_name().c_str(),
             m->get_level(),
             m->get_gender());

    mvprintw(row + 1, 2, "HP: %d  Atk: %d  Def: %d",
             m->get_hp(),
             m->get_atk(),
             m->get_def());

    mvprintw(row + 2, 2, "SpA: %d  SpD: %d  Spe: %d",
             m->get_satk(),
             m->get_sdef(),
             m->get_spd());

    mvprintw(row + 3, 2, "Moves:");
    for (int j = 0; j < (int) m->get_moves().size(); j++) {
      mvprintw(row + 4 + j, 4, "- %s",
               m->get_moves().get(j).name.c_str());
    }
  }

  mvprintw(22, 0, "Press 1, 2, or 3 to choose your starter.");
  refresh();

  int choice = 0;
  while (choice < '1' || choice > '3') {
    choice = getch();
  }

  int picked = choice - '1';
  starters[picked]->heal(1000);
  // Give chosen Pokémon to the PC
  pc->addMon(starters[picked]);

  // Delete the unchosen Pokémon
  for (int i = 0; i < 3; i++) {
    if (i != picked) {
      delete starters[i];
      starters[i] = nullptr;
    }
  }

  clear();
  mvprintw(0, 0, "You chose %s!",
           pc->getMon(0)->get_name().c_str());
  mvprintw(2, 0, "Press any key to begin your adventure...");
  refresh();
  getch();
}


void handleBag(Character *pc);


int main(int argc, char *argv[]){
    srand(time(NULL));
    (void)argc;
    (void)argv;
    
    Colors::initTerminal();
    Map *m = new Map();
    Chunk* current = m->getChunk();
    Character *pc = new Character('@', CharacterType::TrainerLogic, Type::Trainer);
    chooseStarter(pc);
    Move playerMove = current->placePlayer(pc, current->getIntersectionRow(), current->getIntersectionCol());
    uint32_t running, invalid;
    int32_t key;
    running = invalid = 1;
    current->displayChunk();
    while (running) {
        invalid = 1;
            while (invalid){
                key =getch();
                switch (key) {
                    case 'y': {
                        playerMove.dx = -1;
                        playerMove.dy = -1;
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 'k': {
                        playerMove.dx = 0;
                        playerMove.dy = -1;
                        if (pc->getHPos() + playerMove.dx == current->getNGate() && pc->getVPos() + playerMove.dy == 0){
                            current->removePlayer();
                            m->moveNorth();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, 19, current->getSGate());
                            current->displayChunk();
                            break;
                        }
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 'u': {
                        playerMove.dx = +1;
                        playerMove.dy = -1;
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 'l': {
                        playerMove.dx = +1;
                        playerMove.dy = 0;
                        if (pc->getHPos() + playerMove.dx == 79 && pc->getVPos() + playerMove.dy == current->getEGate()){
                            current->removePlayer();
                            m->moveEast();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, current->getWGate(), 1);
                            current->displayChunk();
                            break;
                        }
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 'n': {
                        playerMove.dx = +1;
                        playerMove.dy = +1;
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 'j': {
                        playerMove.dx = 0;
                        playerMove.dy = +1;
                        if (pc->getHPos() + playerMove.dx == current->getSGate() && pc->getVPos() + playerMove.dy == 20){
                            current->removePlayer();
                            m->moveSouth();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, 1, current->getNGate());
                            current->displayChunk();
                            break;
                        }
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 'b': {
                        playerMove.dx = -1;
                        playerMove.dy = +1;
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 'h': {
                        playerMove.dx = -1;
                        playerMove.dy = 0;
                        if (pc->getHPos() + playerMove.dx == 0 && pc->getVPos() + playerMove.dy == current->getWGate()){
                            current->removePlayer();
                            m->moveWest();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, current->getEGate(), 79);
                            current->displayChunk();
                            break;
                        }
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case KEY_RIGHT: {
                        current->handleCenter(*pc);
                        current->handleMart(*pc);
                        break;
                        }
                    case '.': {
                        playerMove.dx = 0;
                        playerMove.dy = 0;
                        if (current->movePlayer(playerMove)){ invalid =0;}
                        break;
                        }
                    case 't': {
                        current->handleShowTrainers(*pc);
                        break;
                        }
                    case 'B': {
                        handleBag(pc);
                        current->displayChunk();
                        break;
                    }
                    case 'Q': {
                        running = 0;
                        invalid = 0;
                        break;
                        }
                    case 'f': {
                        int x = 0, y = 0;

                        // Clear the top line
                        move(0, 0);
                        clrtoeol();

                        // Prompt on the top line
                        mvprintw(0, 0, "where do you want to playerMove (x y): ");
                        refresh();

                        // Enable visible typing
                        echo();
                        curs_set(1);
                        flushinp();

                        // Read input
                        if (scanw("%d %d", &x, &y) != 2) {
                            // Invalid (non-numeric) input
                            noecho();
                            curs_set(0);

                            move(0, 0);
                            clrtoeol();
                            mvprintw(0, 0, "Invalid input.");
                            refresh();
                            break;
                        }

                        noecho();
                        curs_set(0);

                        if (x < -200 || x > 200 || y < -200 || y > 200) {
                            move(0, 0);
                            clrtoeol();
                            mvprintw(0, 0,
                                "Invalid coordinates. Must be between -200 and 200");
                            refresh();
                            break;
                        }

                        current->removePlayer();
                        m->fly(x, y);
                        current = m->getChunk();
                        playerMove = current->placePlayer(pc, current->getIntersectionRow(), current->getIntersectionCol());

                        move(0, 0);
                        clrtoeol();
                        current->displayChunk();

                        break;
                    }
                    default: {
                        mvprintw(0, 0,"invalid input               ");
                        break;
                    }   
                }
            }
        if (pc->isDefeated()){
            running = false;
        }    
    }
        
    if (current) {
        current->removePlayer();
    }

    // Delete player character
    delete pc;
    pc = nullptr;

    // Delete map (this deletes ALL chunks)
    delete m;
    m = nullptr;

    // Shutdown ncurses
    endwin();

    return 0;

}

void handleBag(Character *pc)
{
    bool running = true;

    while (running) {
        std::array<int, 3> bag = pc->getBag();
        clear();

        // ---- Title ----
        mvprintw(0, 0, "Bag");
        mvprintw(1, 0, "--------------------------------");

        // ---- Left side: Pokémon list ----
        mvprintw(3, 0, "Pokemon:");
        for (int i = 0; i < pc->getPartySize(); i++) {
            Mon *m = pc->getMon(i);
            mvprintw(5 + i, 2, "%d) %s  HP: %d/%d",
                     i + 1,
                     m->get_name().c_str(),
                     m->get_currentHp(),
                     m->get_hp());
        }

        // ---- Right side: items ----
        int col = 40;
        mvprintw(3, col, "Items:");
        mvprintw(5, col, "1) Potion  x%d", bag[0]);
        mvprintw(6, col, "2) Revive  x%d", bag[1]);
        mvprintw(7, col, "3) Pokeball  x%d", bag[2]);

        mvprintw(10, 0, "Press 1 (Potion), 2 (Revive), or TAB to exit");

        refresh();

        int choice = getch();
        if (choice == '\t') {
            running = false;
            break;
        }

        // Determine item type
        enum ItemType { POTION, REVIVE };
        ItemType item;

        if (choice == '1') {
            item = POTION;
            if (bag[0] <= 0) {
                mvprintw(12, 0, "You have no potions!");
                getch();
                continue;
            }
        } else if (choice == '2') {
            item = REVIVE;
            if (bag[1] <= 0) {
                mvprintw(12, 0, "You have no revives!");
                getch();
                continue;
            }
        } else {
            continue;
        }

        // ---- Select Pokémon ----
        mvprintw(12, 0, "Select Pokemon (1-%d)", pc->getPartySize());
        refresh();

        int p = getch() - '1';
        if (p < 0 || p >= pc->getPartySize()) {
            continue;
        }

        Mon *target = pc->getMon(p);
        bool success = false;

        if (item == POTION) {
            success = pc->usePotion(target);
        } else {
            success = pc->useRevive(target);
        }

        if (!success) {
            mvprintw(14, 0,
                     "You can't use this on that Pokemon right now.");
            getch();
        }
    }

    clear();
}

