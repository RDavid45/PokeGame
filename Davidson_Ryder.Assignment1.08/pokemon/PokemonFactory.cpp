#include "PokemonFactory.h"
#include "CSVReader.h"
#include <cstdlib>
#include <cmath>

PokemonFactory* PokemonFactory::instance = nullptr;

PokemonFactory::PokemonFactory(){
    CSVReader r;
    pokemon = r.load_pokemon();
    moves = r.load_moves();
    move_mappings = r.load_pokemon_moves();
    species = r.load_pokemon_species();
    experience = r.load_experience();
    type_names = r.load_type_names();
    type_mappings = r.load_pokemon_types();
    stats = r.load_stats();
    stat_mapping = r.load_pokemon_stats();
}

PokemonFactory * PokemonFactory::getInstance(){
    if (!instance){
        instance = new PokemonFactory();
    }
    return instance;
}


Mon* PokemonFactory::generatePokemon(int level) {
    // Pick random Pokémon
    int i = rand() % pokemon.size();
    Pokemon::pokemon p = pokemon.get(i);
    int species_id = p.species_id;

    // Determine Pokémon types
    int type1 = -1;
    int type2 = -1;

    for (int j = 0; j < (int) type_mappings.size(); j++) {
        auto tm = type_mappings.get(j);
        if (tm.pokemon_id != species_id) continue;

        if (tm.slot == 1) {
            type1 = tm.type_id;
        } else if (tm.slot == 2) {
            type2 = tm.type_id;
        }
    }


    // Roll IVs
    int iv_hp   = rand() % 16;
    int iv_atk  = rand() % 16;
    int iv_def  = rand() % 16;
    int iv_satk = rand() % 16;
    int iv_sdef = rand() % 16;
    int iv_spd  = rand() % 16;

    // Get base stats
    int base_hp = 0, base_atk = 0, base_def = 0;
    int base_satk = 0, base_sdef = 0, base_spd = 0;

    for (int j = 0; j < (int) stat_mapping.size(); j++) {
        auto sm = stat_mapping.get(j);
        if (sm.pokemon_id != species_id) continue;

        switch (sm.stat_id) {
            case 1: base_hp = sm.base_stat; break;
            case 2: base_atk = sm.base_stat; break;
            case 3: base_def = sm.base_stat; break;
            case 4: base_satk = sm.base_stat; break;
            case 5: base_sdef = sm.base_stat; break;
            case 6: base_spd = sm.base_stat; break;
        }
    }

    // Compute stats
    int hp = ((base_hp + iv_hp) * 2 * level) / 100 + level + 10;
    int atk = ((base_atk + iv_atk) * 2 * level) / 100 + 5;
    int def = ((base_def + iv_def) * 2 * level) / 100 + 5;
    int satk = ((base_satk + iv_satk) * 2 * level) / 100 + 5;
    int sdef = ((base_sdef + iv_sdef) * 2 * level) / 100 + 5;
    int spd = ((base_spd + iv_spd) * 2 * level) / 100 + 5;

    // Collect level-up moves
    ArrayList<Pokemon::move> possible;

    do {
        possible.clear();

        for (int j = 0; j < (int) move_mappings.size(); j++) {
            auto mm = move_mappings.get(j);
            if (mm.pokemon_id != species_id) continue;
            if (mm.pokemon_move_method_id != 1) continue;
            if (mm.level > level) continue;

            for (int k = 0; k < (int) moves.size(); k++) {
                if (moves.get(k).id == mm.move_id) {
                    possible.add(moves.get(k));
                    break;
                }
            }
        }

        if (possible.size() == 0) level++;

    } while (possible.size() == 0);

    // Build Mon
    Mon* mon = new Mon();
    mon->set_species_id(species_id);
    mon->set_name(p.name);
    mon->set_type(type1, type2);
    mon->set_level(level);
    mon->set_ivs(iv_hp, iv_atk, iv_def, iv_satk, iv_sdef, iv_spd);

    mon->set_hp(hp);
    mon->set_atk(atk);
    mon->set_def(def);
    mon->set_satk(satk);
    mon->set_sdef(sdef);
    mon->set_spd(spd);

    mon->set_gender(rand() % 2 ? 'M' : 'F');
    mon->set_shiny(rand() % 8192 == 0);

    // Add up to two moves
    mon->add_move(possible.get(rand() % possible.size()));
    if ((int) possible.size() > 1) {
        mon->add_move(possible.get(rand() % possible.size()));
    }

    return mon;
}