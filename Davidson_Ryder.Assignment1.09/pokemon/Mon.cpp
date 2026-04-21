#include "Mon.h"

// constructor / destructor
Mon::Mon()
    : species_id(0),
      level(1),
      iv_hp(0), iv_atk(0), iv_def(0),
      iv_satk(0), iv_sdef(0), iv_spd(0),
      hp(0), atk(0), def(0), satk(0), sdef(0), spd(0),
      currentHp(0),
      shiny(false),
      gender('M') {
    types[0] = Pokemon::No_TYPE;
    types[1] = Pokemon::No_TYPE;
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
Pokemon::Type Mon::get_type(int i) const {
    return types[i];
}

void Mon::set_type(Pokemon::Type t1, Pokemon::Type t2) {
    types[0] = t1;
    types[1] = t2;
}

// stats
int Mon::get_hp() const { return hp; }
void Mon::set_hp(int v) { hp = v; heal(v);}

int Mon::get_currentHp() const {
    return currentHp;
}

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

void Mon::use_move(Mon *target, int move){
    static constexpr float TYPE_CHART[19][19] = {
    /* ATK \ DEF
                0    NRM   FGT   FLY   PSN   GRD   RCK   BUG   GST   STL   FIR   WAT   GRS   ELE   PSY   ICE   DRA   DRK   FRY */
    /* 0 No */ {1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1},
    /* 1 N  */ {1,    1,    1,    1,    1,    1,  .5f,    1,    0,  .5f,    1,    1,    1,    1,    1,    1,    1,    1,    1},
    /* 2 F  */ {1,    2,    1,  .5f,  .5f,    1,    2,  .5f,    0,    2,    1,    1,    1,    1,  .5f,    2,    1,    2,  .5f},
    /* 3 FL */ {1,    1,    2,    1,    1,    1,  .5f,    2,    1,    0,    1,    1,    2,  .5f,    1,    1,    1,    1,    1},
    /* 4 P  */ {1,    1,    1,    1,  .5f,  .5f,  .5f,    1,  .5f,    0,    1,    1,    2,    1,    1,    1,    1,    1,    2},
    /* 5 G  */ {1,    1,    1,    0,    2,    1,    2,  .5f,    1,    2,    2,    1,  .5f,    2,    1,    1,    1,    1,    1},
    /* 6 R  */ {1,    1,  .5f,    2,    1,  .5f,    1,    2,    1,  .5f,    2,    1,    1,    1,    1,    2,    1,    1,    1},
    /* 7 B  */ {1,    1,  .5f,  .5f,  .5f,    1,    1,    1,  .5f,  .5f,  .5f,    1,    2,    1,    2,    1,    1,    2,  .5f},
    /* 8 Gh */ {1,    0,    1,    1,    1,    1,    1,    1,    2,    1,    1,    1,    1,    1,    2,    1,  .5f,  .5f,    1},
    /* 9 St */ {1,    1,    1,    1,    1,    1,    2,    1,    1,  .5f,  .5f,  .5f,    1,  .5f,    1,    2,    1,    1,    2},
    /*10 Fi */ {1,    1,    1,    1,    1,    1,  .5f,    2,    1,    2,  .5f,  .5f,    2,    1,    1,    2,  .5f,    1,    1},
    /*11 Wa */ {1,    1,    1,    1,    1,    2,    2,    1,    1,    1,    2,  .5f,  .5f,    1,    1,    1,  .5f,    1,    1},
    /*12 Gr */ {1,    1,    1,  .5f,  .5f,    2,    2,  .5f,    1,  .5f,  .5f,    2,  .5f,    1,    1,    1,  .5f,    1,    1},
    /*13 El */ {1,    1,    1,    2,    1,    0,    1,    1,    1,    1,    1,    2,  .5f,  .5f,    1,    1,  .5f,    1,    1},
    /*14 Ps */ {1,    1,    2,    1,    2,    1,    1,    1,    1,  .5f,    1,    1,    1,    1,  .5f,    1,    1,    0,    0},
    /*15 Ic */ {1,    1,    1,    2,    1,    2,    1,    1,    1,  .5f,  .5f,  .5f,    2,    1,    1,  .5f,    1,    1,    1},
    /*16 Dr */ {1,    1,    1,    1,    1,    1,    1,    1,    1,  .5f,    1,    1,    1,    1,    1,    2,    1,    1,    0},
    /*17 Da */ {1,    1,  .5f,    1,    1,    1,    1,    1,    2,    1,    1,    1,    1,    0,    2,    1,  .5f,   .5,  .5f},
    /*18 Fa */ {1,    1,    2,    1,  .5f,    1,    1,    1,    1,  .5f,  .5f,    1,    1,    1,    1,    1,    2,    2,    1}
    };
    Pokemon::move m = moves.get(move);

    
    // ---------------------------
    // 1. Accuracy check
    // ---------------------------
    int roll = rand() % 100;
    if (roll > m.accuracy) {
        return;
    }

    // ---------------------------
    // 2. Critical hit check
    // ---------------------------
    int crit_roll = rand() % 256;
    int crit_threshold = 256 / 24;
    float critical = (crit_roll < crit_threshold) ? 1.5f : 1.0f;

    // ---------------------------
    // 3. Random damage factor [85,100]
    // ---------------------------
    float random_factor = (85 + (rand() % 16)) / 100.0f;

    // ---------------------------
    // 4. STAB check
    // ---------------------------
    float stab = 1.0f;
    if (types[0] == m.type || types[1] == m.type) {
        stab = 1.5f;
    }

    // ---------------------------
    // 5. Type effectiveness
    // ---------------------------
    float type_effectiveness =
        TYPE_CHART[m.type][target->types[0]] *
        TYPE_CHART[m.type][target->types[1]];

    // ---------------------------
    // 6. Base damage calculation
    // ---------------------------
    float base_damage = (m.damage_class == 2) ?
        (((2 * level) / 5 + 2) *
         m.power *
         (static_cast<float>(atk) / static_cast<float>(target->def)) /
         5) + 2 : 
         (((2 * level) / 5 + 2) *
         m.power *
         (static_cast<float>(satk) / static_cast<float>(target->sdef)) /
         5) + 2;

    float damage =
        base_damage *
        critical *
        random_factor *
        stab *
        type_effectiveness;

    int final_damage = std::max(1, static_cast<int>(damage));

    // ---------------------------
    // 7. Apply damage
    // ---------------------------
    target->currentHp -= final_damage;

    if (target->currentHp < 0) {
        target->currentHp = 0;
    }
}

void Mon::heal(int amount){ currentHp = std::min(hp, currentHp + amount);}

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

