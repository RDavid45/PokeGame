#pragma once

#include "Pokemon.h"
#include "Mon.h"

class PokemonFactory{
    private:
        static PokemonFactory *instance;
        ArrayList<Pokemon::pokemon> pokemon;
        ArrayList<Pokemon::move> moves;
        ArrayList<Pokemon::move_mapping> move_mappings;
        ArrayList<Pokemon::species> species;
        ArrayList<Pokemon::experience> experience;
        ArrayList<Pokemon::type_names> type_names;
        ArrayList<Pokemon::type_mapping> type_mappings;
        ArrayList<Pokemon::stats> stats;
        ArrayList<Pokemon::stat_mapping> stat_mapping;
        
        PokemonFactory();
    public:
        static PokemonFactory *getInstance();
        Mon *generatePokemon(int); 

};
