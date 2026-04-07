#pragma once

#include <string>
#include <climits>
#include "ArrayList.h"
#include "Pokemon.h"

class CSVReader {
public:
    CSVReader();

    ArrayList<Pokemon::pokemon> load_pokemon();
    ArrayList<Pokemon::move> load_moves();
    ArrayList<Pokemon::move_mapping> load_pokemon_moves();
    ArrayList<Pokemon::species> load_pokemon_species();
    ArrayList<Pokemon::experience> load_experience();
    ArrayList<Pokemon::type_names> load_type_names();
    ArrayList<Pokemon::stat_mapping> load_pokemon_stats();
    ArrayList<Pokemon::stats> load_stats();
    ArrayList<Pokemon::type_mapping> load_pokemon_types();

private:
    std::string root_path;
    std::string csv_path;

    static std::string find_database_root();
    static bool dir_exists(const std::string &);
    static ArrayList<std::string> split_csv_line(const std::string &);
    static int to_int_or_max(const std::string &);
};