#include "Mon.h"

// constructor / destructor
Mon::Mon()
    : species_id(0),
      level(1),
      iv_hp(0), iv_atk(0), iv_def(0),
      iv_satk(0), iv_sdef(0), iv_spd(0),
      hp(0), atk(0), def(0), satk(0), sdef(0), spd(0),
      shiny(false),
      gender('M') {
    types[0] = -1;
    types[1] = -1;
}

Mon::~Mon() {}

// species / identity
int Mon::get_species_id() const {
    return species_id;
}

void Mon::set_species_id(int id) {
    species_id = id;
}

std::string Mon::get_name() const {
    return name;
}

void Mon::set_name(const std::string& n) {
    name = n;
}

int Mon::get_level() const {
    return level;
}

void Mon::set_level(int l) {
    level = l;
}

// types
int* Mon::get_type() const {
    return (int*)types;
}

void Mon::set_type(int t1, int t2) {
    types[0] = t1;
    types[1] = t2;
}

// stats
int Mon::get_hp() const { return hp; }
void Mon::set_hp(int v) { hp = v; }

int Mon::get_atk() const { return atk; }
void Mon::set_atk(int v) { atk = v; }

int Mon::get_def() const { return def; }
void Mon::set_def(int v) { def = v; }

int Mon::get_satk() const { return satk; }
void Mon::set_satk(int v) { satk = v; }

int Mon::get_sdef() const { return sdef; }
void Mon::set_sdef(int v) { sdef = v; }

int Mon::get_spd() const { return spd; }
void Mon::set_spd(int v) { spd = v; }

// IVs
void Mon::set_ivs(int hp, int atk, int def, int satk, int sdef, int spd) {
    iv_hp = hp;
    iv_atk = atk;
    iv_def = def;
    iv_satk = satk;
    iv_sdef = sdef;
    iv_spd = spd;
}

// misc
bool Mon::get_shiny() const {
    return shiny;
}

void Mon::set_shiny(bool s) {
    shiny = s;
}

char Mon::get_gender() const {
    return gender;
}

void Mon::set_gender(char g) {
    gender = g;
}

// moves
void Mon::add_move(const Pokemon::move& m) {
    moves.add(m);
}

ArrayList<Pokemon::move>& Mon::get_moves() {
    return moves;
}

std::ostream& operator<<(std::ostream& os, const Mon& mon) {
    os << "=============================\n";
    os << mon.name << " (Lv. " << mon.level << ") ";

    os << (mon.gender == 'M' ? "♂" : "♀");
    if (mon.shiny) os << " ✨";
    os << "\n";

    os << "-----------------------------\n";
    os << "HP   : " << mon.hp   << "\n";
    os << "ATK  : " << mon.atk  << "\n";
    os << "DEF  : " << mon.def  << "\n";
    os << "SpATK: " << mon.satk << "\n";
    os << "SpDEF: " << mon.sdef << "\n";
    os << "SPD  : " << mon.spd  << "\n";

    os << "\nMoves:\n";
    for (int i = 0; i < (int) mon.moves.size(); i++) {
        os << " - " << mon.moves.get(i).name << "\n";
    }

    os << "=============================\n";
    return os;
}

