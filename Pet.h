#pragma once

#include "PetVar.h"

class PetMgr
{

public:
    enum class DB_Type
    {
        FILE,
        SQLITE
    };

    PetVars petVar;

    void addAge();

    void Feeder();
    void Eater();
    void Digester();
    void StarvManager();

    void Hydrater();
    void Drinker();
    void H2OProcessor();
    void DehyManager();

    //void companionF();

    void logDB_CMD();
public:
    void Update();
public:

    bool Save_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
    bool Load_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);

    //static std::vector<float> LoadedVs; // here u have the data but its private
};


extern const char* sqlstatement(const char* format, ...);