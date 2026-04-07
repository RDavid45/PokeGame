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
#include "CSVReader.h"
#include "Pokemon.h"


int main(int argc, char *argv[]){
    
    if (argc == 2) {
        std::string command(argv[1]);
        CSVReader reader;

        if (command == "pokemon") {
            auto data = reader.load_pokemon();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "moves") {
            auto data = reader.load_moves();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "pokemon_moves") {
            auto data = reader.load_pokemon_moves();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "pokemon_species") {
            auto data = reader.load_pokemon_species();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "experience") {
            auto data = reader.load_experience();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "type_names") {
            auto data = reader.load_type_names();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "pokemon_stats") {
            auto data = reader.load_pokemon_stats();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "stats") {
            auto data = reader.load_stats();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else if (command == "pokemon_types") {
            auto data = reader.load_pokemon_types();
            for (size_t i = 0; i < data.size(); i++) {
                std::cout << data[i] << "\n";
            }

        } else {
            std::cerr << "Invalid data set: " << command << std::endl;
            return 1;
        }

        return 0;
    }

    Colors::initTerminal();
    srand(time(NULL));
    Map *m = new Map();
    Chunk* current = m->getChunk();
    Character *pc = new Character('@', CharacterType::TrainerLogic, Type::Trainer);
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
                        if (pc->getHPos() + playerMove.dx == current->getNGate() && pc->getVPos() + playerMove.dy == 0){
                            current->removePlayer();
                            m->moveNorth();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, 19, current->getSGate());
                            current->displayChunk();
                            break;
                        }
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
                        if (pc->getHPos() + playerMove.dx == current->getNGate() && pc->getVPos() + playerMove.dy == 0){
                            current->removePlayer();
                            m->moveNorth();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, 19, current->getSGate());
                            current->displayChunk();
                            break;
                        }
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
                        if (pc->getHPos() + playerMove.dx == current->getSGate() && pc->getVPos() + playerMove.dy == 20){
                            current->removePlayer();
                            m->moveSouth();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, 1, current->getNGate());
                            current->displayChunk();
                            break;
                        }
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
                        if (pc->getHPos() + playerMove.dx == current->getSGate() && pc->getVPos() + playerMove.dy == 20){
                            current->removePlayer();
                            m->moveSouth();
                            current = m->getChunk();
                            playerMove = current->placePlayer(pc, 1, current->getNGate());
                            current->displayChunk();
                            break;
                        }
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

