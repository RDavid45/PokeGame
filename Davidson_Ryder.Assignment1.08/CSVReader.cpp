#include "CSVReader.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/stat.h>
#include <iostream>



CSVReader::CSVReader() {
    root_path = find_database_root();
    if (root_path.empty()) {
        std::cerr << "Error: pokedex not found\n";
        std::exit(1);
    }

    csv_path = root_path + "/pokedex/data/csv/";
}

bool CSVReader::dir_exists(const std::string &path) {
    struct stat sb{};
    return stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode);
}

std::string CSVReader::find_database_root() {
    if (dir_exists("/share/cs327/pokedex"))
        return "/share/cs327/pokedex";

    const char *home = getenv("HOME");
    if (home) {
        std::string p = std::string(home) + "/.poke327/pokedex";
        if (dir_exists(p))
            return p;
    }

    return "";
}


ArrayList<std::string> CSVReader::split_csv_line(const std::string &line) {
    ArrayList<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, ',')) {
        fields.add(field);
    }

    if (!line.empty() && line.back() == ',')
        fields.add("");

    return fields;
}

int CSVReader::to_int_or_max(const std::string &s) {
    return s.empty() ? INT_MAX : std::stoi(s);
}


ArrayList<Pokemon::pokemon> CSVReader::load_pokemon() {
    ArrayList<Pokemon::pokemon> list;
    std::ifstream f(csv_path + "pokemon.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::pokemon p{};

        p.id         = to_int_or_max(c[0]);
        p.name       = c[1];
        p.species_id = to_int_or_max(c[2]);
        p.height     = to_int_or_max(c[3]);
        p.weight     = to_int_or_max(c[4]);
        p.base_exp   = to_int_or_max(c[5]);
        p.order      = to_int_or_max(c[6]);
        p.is_default = to_int_or_max(c[7]);

        list.add(p);
    }
    return list;
}

ArrayList<Pokemon::move> CSVReader::load_moves() {
    ArrayList<Pokemon::move> list;
    std::ifstream f(csv_path + "moves.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::move m{};

        m.id                   = to_int_or_max(c[0]);
        m.name                 = c[1];
        m.gen                  = to_int_or_max(c[2]);
        m.type                 = to_int_or_max(c[3]);
        m.power                = to_int_or_max(c[4]);
        m.pp                   = to_int_or_max(c[5]);
        m.accuracy             = to_int_or_max(c[6]);
        m.priority             = to_int_or_max(c[7]);
        m.target_id            = to_int_or_max(c[8]);
        m.damage_class         = to_int_or_max(c[9]);
        m.effect_id            = to_int_or_max(c[10]);
        m.effect_chance        = to_int_or_max(c[11]);
        m.contest_type         = to_int_or_max(c[12]);
        m.contest_effect       = to_int_or_max(c[13]);
        m.super_contest_effect = to_int_or_max(c[14]);

        list.add(m);
    }
    return list;
}

ArrayList<Pokemon::move_mapping> CSVReader::load_pokemon_moves() {
    ArrayList<Pokemon::move_mapping> list;
    std::ifstream f(csv_path + "pokemon_moves.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::move_mapping p{};

        p.pokemon_id            = to_int_or_max(c[0]);
        p.version               = to_int_or_max(c[1]);
        p.move_id               = to_int_or_max(c[2]);
        p.pokemon_move_method_id= to_int_or_max(c[3]);
        p.level                 = to_int_or_max(c[4]);
        p.order                 = to_int_or_max(c[5]);

        list.add(p);
    }
    return list;
}

ArrayList<Pokemon::species> CSVReader::load_pokemon_species() {
    ArrayList<Pokemon::species> list;
    std::ifstream f(csv_path + "pokemon_species.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::species s{};

        s.id                     = to_int_or_max(c[0]);
        s.identifier             = c[1];
        s.generation_id          = to_int_or_max(c[2]);
        s.evolves_from_species_id= to_int_or_max(c[3]);
        s.evolution_chain_id     = to_int_or_max(c[4]);
        s.color_id               = to_int_or_max(c[5]);
        s.shape_id               = to_int_or_max(c[6]);
        s.habitat_id             = to_int_or_max(c[7]);
        s.gender_rate            = to_int_or_max(c[8]);
        s.capture_rate           = to_int_or_max(c[9]);
        s.base_happiness         = to_int_or_max(c[10]);
        s.is_baby                = to_int_or_max(c[11]);
        s.hatch_counter          = to_int_or_max(c[12]);
        s.has_gender_differences = to_int_or_max(c[13]);
        s.growth_rate_id         = to_int_or_max(c[14]);
        s.forms_switchable       = to_int_or_max(c[15]);
        s.is_legendary           = to_int_or_max(c[16]);
        s.is_mythical            = to_int_or_max(c[17]);
        s.order                  = to_int_or_max(c[18]);
        s.conquest_order         = to_int_or_max(c[19]);

        list.add(s);
    }
    return list;
}

ArrayList<Pokemon::experience> CSVReader::load_experience() {
    ArrayList<Pokemon::experience> list;
    std::ifstream f(csv_path + "experience.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::experience e{};

        e.growth_rate_id = to_int_or_max(c[0]);
        e.level          = to_int_or_max(c[1]);
        e.experience     = to_int_or_max(c[2]);

        list.add(e);
    }
    return list;
}


ArrayList<Pokemon::type_names> CSVReader::load_type_names() {
    ArrayList<Pokemon::type_names> list;
    std::ifstream f(csv_path + "type_names.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);

        if (to_int_or_max(c[1]) != 9)
            continue;

        Pokemon::type_names t{};
        t.type_id        = to_int_or_max(c[0]);
        t.local_language = to_int_or_max(c[1]);
        t.name           = c[2];

        list.add(t);
    }
    return list;
}

ArrayList<Pokemon::stat_mapping> CSVReader::load_pokemon_stats() {
    ArrayList<Pokemon::stat_mapping> list;
    std::ifstream f(csv_path + "pokemon_stats.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::stat_mapping s{};

        s.pokemon_id = to_int_or_max(c[0]);
        s.stat_id    = to_int_or_max(c[1]);
        s.base_stat  = to_int_or_max(c[2]);
        s.effort     = to_int_or_max(c[3]);

        list.add(s);
    }
    return list;
}

ArrayList<Pokemon::stats> CSVReader::load_stats() {
    ArrayList<Pokemon::stats> list;
    std::ifstream f(csv_path + "stats.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::stats s{};

        s.id           = to_int_or_max(c[0]);
        s.damage_type  = to_int_or_max(c[1]);
        s.identifier   = c[2];
        s.bettle_only  = to_int_or_max(c[3]);
        s.game_index   = to_int_or_max(c[4]);

        list.add(s);
    }
    return list;
}

ArrayList<Pokemon::type_mapping> CSVReader::load_pokemon_types() {
    ArrayList<Pokemon::type_mapping> list;
    std::ifstream f(csv_path + "pokemon_types.csv");
    std::string line;
    std::getline(f, line);

    while (std::getline(f, line)) {
        auto c = split_csv_line(line);
        Pokemon::type_mapping t{};

        t.pokemon_id = to_int_or_max(c[0]);
        t.type_id    = to_int_or_max(c[1]);
        t.slot       = to_int_or_max(c[2]);

        list.add(t);
    }
    return list;
}