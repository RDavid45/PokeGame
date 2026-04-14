#include "Pokemon.h"
#include <iostream>
#include <climits>


#define PRINT_INT(os, x) \
    if ((x) != INT_MAX) os << (x)


namespace Pokemon {

std::ostream& operator<<(std::ostream& os, const pokemon& p) {
    PRINT_INT(os, p.id); os << ",";
    os << p.name << ",";
    PRINT_INT(os, p.species_id); os << ",";
    PRINT_INT(os, p.height); os << ",";
    PRINT_INT(os, p.weight); os << ",";
    PRINT_INT(os, p.base_exp); os << ",";
    PRINT_INT(os, p.order); os << ",";
    PRINT_INT(os, p.is_default);
    return os;
}

std::ostream& operator<<(std::ostream& os, const move& m) {
    PRINT_INT(os, m.id); os << ",";
    os << m.name << ",";
    PRINT_INT(os, m.gen); os << ",";
    PRINT_INT(os, m.type); os << ",";
    PRINT_INT(os, m.power); os << ",";
    PRINT_INT(os, m.pp); os << ",";
    PRINT_INT(os, m.accuracy); os << ",";
    PRINT_INT(os, m.priority); os << ",";
    PRINT_INT(os, m.target_id); os << ",";
    PRINT_INT(os, m.damage_class); os << ",";
    PRINT_INT(os, m.effect_id); os << ",";
    PRINT_INT(os, m.effect_chance); os << ",";
    PRINT_INT(os, m.contest_type); os << ",";
    PRINT_INT(os, m.contest_effect); os << ",";
    PRINT_INT(os, m.super_contest_effect);
    return os;
}

std::ostream& operator<<(std::ostream& os, const move_mapping& mm) {
    PRINT_INT(os, mm.pokemon_id); os << ",";
    PRINT_INT(os, mm.version); os << ",";
    PRINT_INT(os, mm.move_id); os << ",";
    PRINT_INT(os, mm.pokemon_move_method_id); os << ",";
    PRINT_INT(os, mm.level); os << ",";
    PRINT_INT(os, mm.order);
    return os;
}

std::ostream& operator<<(std::ostream& os, const species& s) {
    PRINT_INT(os, s.id); os << ",";
    os << s.identifier << ",";
    PRINT_INT(os, s.generation_id); os << ",";
    PRINT_INT(os, s.evolves_from_species_id); os << ",";
    PRINT_INT(os, s.evolution_chain_id); os << ",";
    PRINT_INT(os, s.color_id); os << ",";
    PRINT_INT(os, s.shape_id); os << ",";
    PRINT_INT(os, s.habitat_id); os << ",";
    PRINT_INT(os, s.gender_rate); os << ",";
    PRINT_INT(os, s.capture_rate); os << ",";
    PRINT_INT(os, s.base_happiness); os << ",";
    PRINT_INT(os, s.is_baby); os << ",";
    PRINT_INT(os, s.hatch_counter); os << ",";
    PRINT_INT(os, s.has_gender_differences); os << ",";
    PRINT_INT(os, s.growth_rate_id); os << ",";
    PRINT_INT(os, s.forms_switchable); os << ",";
    PRINT_INT(os, s.is_legendary); os << ",";
    PRINT_INT(os, s.is_mythical); os << ",";
    PRINT_INT(os, s.order); os << ",";
    PRINT_INT(os, s.conquest_order);
    return os;
}

std::ostream& operator<<(std::ostream& os, const experience& e) {
    PRINT_INT(os, e.growth_rate_id); os << ",";
    PRINT_INT(os, e.level); os << ",";
    PRINT_INT(os, e.experience);
    return os;
}

std::ostream& operator<<(std::ostream& os, const type_names& tn) {
    PRINT_INT(os, tn.type_id); os << ",";
    PRINT_INT(os, tn.local_language); os << ",";
    os << tn.name;
    return os;
}

std::ostream& operator<<(std::ostream& os, const stat_mapping& sm) {
    PRINT_INT(os, sm.pokemon_id); os << ",";
    PRINT_INT(os, sm.stat_id); os << ",";
    PRINT_INT(os, sm.base_stat); os << ",";
    PRINT_INT(os, sm.effort);
    return os;
}

std::ostream& operator<<(std::ostream& os, const stats& s) {
    PRINT_INT(os, s.id); os << ",";
    PRINT_INT(os, s.damage_type); os << ",";
    os << s.identifier << ",";
    PRINT_INT(os, s.bettle_only); os << ",";
    PRINT_INT(os, s.game_index);
    return os;
}

std::ostream& operator<<(std::ostream& os, const type_mapping& tm) {
    PRINT_INT(os, tm.pokemon_id); os << ",";
    PRINT_INT(os, tm.type_id); os << ",";
    PRINT_INT(os, tm.slot);
    return os;
}

}
