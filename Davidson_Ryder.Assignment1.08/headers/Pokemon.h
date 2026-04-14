#pragma once

#include <string>

namespace Pokemon {
    struct pokemon {
        int id;
        std::string name;
        int species_id;
        int height;
        int weight;
        int base_exp;
        int order;
        int is_default;
    };

    struct move{
        int id;
        std::string name;
        int gen;
        int type;
        int power;
        int pp;
        int accuracy;
        int priority;
        int target_id;
        int damage_class;
        int effect_id;
        int effect_chance;
        int contest_type;
        int contest_effect;
        int super_contest_effect;
    };

    struct move_mapping{
        int pokemon_id;
        int version;
        int move_id;
        int pokemon_move_method_id;
        int level;
        int order;
    };

    struct species{
        int id;
        std::string identifier;
        int generation_id;
        int evolves_from_species_id;
        int evolution_chain_id;
        int color_id;
        int shape_id;
        int habitat_id;
        int gender_rate;
        int capture_rate;
        int base_happiness;
        int is_baby;
        int hatch_counter;
        int has_gender_differences;
        int growth_rate_id;
        int forms_switchable;
        int is_legendary;
        int is_mythical;
        int order;
        int conquest_order;
    };

    struct experience{
        int growth_rate_id;
        int level;
        int experience;
    };

    struct type_names{
        int type_id;
        int local_language;
        std::string name;
    };

    struct stat_mapping{
        int pokemon_id;
        int stat_id;
        int base_stat;
        int effort;
    };

    struct stats{
        int id;
        int damage_type;
        std::string identifier;
        int bettle_only;
        int game_index;
    };

    struct type_mapping{
        int pokemon_id;
        int type_id;
        int slot;
    };

    std::ostream& operator<<(std::ostream& os, const pokemon& s);
    std::ostream& operator<<(std::ostream& os, const move& s);
    std::ostream& operator<<(std::ostream& os, const move_mapping& s);
    std::ostream& operator<<(std::ostream& os, const species& s);
    std::ostream& operator<<(std::ostream& os, const experience& s);
    std::ostream& operator<<(std::ostream& os, const type_names& s);
    std::ostream& operator<<(std::ostream& os, const stat_mapping& s);
    std::ostream& operator<<(std::ostream& os, const stats& s);
    std::ostream& operator<<(std::ostream& os, const type_mapping& tm);
}