#pragma once

#include <string>
#include <ostream>
#include "Pokemon.h"
#include "ArrayList.h"

class Mon {
private:
    int species_id;
    std::string name;
    int level;

    // IVs
    int iv_hp, iv_atk, iv_def;
    int iv_satk, iv_sdef, iv_spd;

    // Final stats
    int hp, atk, def, satk, sdef, spd;

    bool shiny;
    char gender;

    int types[2];

    ArrayList<Pokemon::move> moves;

public:
    Mon();
    ~Mon();

    void printMon();

    // species / identity
    int get_species_id() const;
    void set_species_id(int);

    std::string get_name() const;
    void set_name(const std::string&);

    int get_level() const;
    void set_level(int);

    int* get_type() const;
    void set_type(int, int);

    // stats
    int get_hp() const;
    void set_hp(int);

    int get_atk() const;
    void set_atk(int);

    int get_def() const;
    void set_def(int);

    int get_satk() const;
    void set_satk(int);

    int get_sdef() const;
    void set_sdef(int);

    int get_spd() const;
    void set_spd(int);

    // IVs
    void set_ivs(int,int,int,int,int,int);

    // misc
    bool get_shiny() const;
    void set_shiny(bool);

    char get_gender() const;
    void set_gender(char);

    // moves
    void add_move(const Pokemon::move&);
    ArrayList<Pokemon::move>& get_moves();

    

    void printMon() const;

    // stream output
    friend std::ostream& operator<<(std::ostream& os, const Mon& mon);
};