#pragma once

#include "PetVar.h"

class Pet_Manager
{

public:
    enum class DB_Type
    {
        FILE,
        SQLITE
    };

    PetVars petVar;
    food_dish food_dish_obj;




    void addAge();

    void Digester();
    void StarvManager();

    void Hydrater();
    void Drinker();
    void H2OProcessor();
    void DehyManager();

    bool pet_death(bool& show, const char cause_of_death);

    void logDB_CMD();
public:
    void Update();
public:

    bool Save_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
    bool Load_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
};


extern const char* sqlstatement(const char* format, ...);


