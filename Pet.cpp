
#include "Pet.h"

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <sqlite3.h>

int callback(void* NotUsed, int argc, char** argv, char** azColName) { //argc = count , **argv = char array[][] 

    float* getVarPtr = (float*)NotUsed;
    *getVarPtr = std::stof(argv[0]); // string to float
//     std::stringstream ss(argv[0]);
//     ss >> *getVarPtr;
//     ss.clear();
    // Return successful
    return 0;
}


const char* sqlstatement(const char* format, ...) 
{
    //std::string str;

    char str[1024];
    va_list args;
    va_start(args, format);
    vprintf(str, args);
    va_end(args);
    return str;

    //sqlite3_exec(master_db, var, type, values, NULL, NULL, &cr_error);
    //

    // tada
    //sqlite3_exec(master_db, sqlstatement("%s %d values %s %f","iVariables", "iv_Name, Stat", "'Health'", 1.0f), NULL, NULL, &cr_error);
}


bool Save_sql3(const char* sz_filename, PetVars obj)
{
    char* sv_error;
    int rc;

    sqlite3* master_db;
    
   // sqlite3_exec(master_db, sqlstatement("INSERT INTO %s %d values %s %f","iVariables", "iv_Name, Stat", "'Health'", obj.Health), NULL, NULL, &sv_error);



//    sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values (" + sqlite3_exec()
//     sqlite3_exec(master_db, "INSERT INTO iVariables (" + iv_Name + "," + Stat ")" values('Health', '1.0'); ", NULL, NULL, &cr_error);
//         //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Health', '1.0');", NULL, NULL, &cr_error);
//         sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Min_Health', '0.0');", NULL, NULL, &cr_error);
//         sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Health', '1.0');", NULL, NULL, &cr_error);
    return (SQLITE_OK);
}

bool Load_sql3(const char* sz_filename, PetVars& obj)
{

    char* dbl_error;
    int rc;

    sqlite3* master_db;

    // Open db
    rc = sqlite3_open_v2(sz_filename, &master_db, SQLITE_OPEN_READONLY, NULL);
    // If db NOT exist
    if (rc != SQLITE_OK)
    {


         return (rc == SQLITE_OK);
    }


    //// Fetch Variables from db
    // Health & Life
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Age';", callback, &obj.Age, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Health';", callback, &obj.Health, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Min_Health';", callback, &obj.Min_Health, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Max_Health';", callback, &obj.Max_Health, &dbl_error);
    // Hunger
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Hunger';", callback, &obj.Hunger, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Def_Hunger';", callback, &obj.Def_Hunger, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Max_Hunger';", callback, &obj.Max_Hunger, &dbl_error);
    //rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Def_Hunger_Rate';", callback, &obj.Def_Hunger_Rate, &dbl_error);
    // Starv
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Starv';", callback, &obj.Starv, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Def_Starv';", callback, &obj.Def_Starv, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Max_Starv';", callback, &obj.Max_Starv, &dbl_error);
    //rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Def_Starv_Rate';", callback, &obj.Def_Starv_Rate, &dbl_error);
    // Thirst
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Thirst';", callback, &obj.Thirst, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Def_Thirst';", callback, &obj.Def_Thirst, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Max_Thirst';", callback, &obj.Max_Thirst, &dbl_error);
    //rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Def_Thirst_Rate';", callback, &obj.Def_Thirst_Rate, &dbl_error);
    // Dehydration
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Dehy';", callback, &obj.Dehy, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Dehy_Min';", callback, &obj.Dehy_Min, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Dehy_Max';", callback, &obj.Dehy_Max, &dbl_error);
    //rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Def_Dehy_Rate';", callback, &obj.Def_Dehy_Rate, &dbl_error);
    // Water_Bowl
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Water_Bowl';", callback, &obj.Water_Bowl, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Min_Water_Bowl';", callback, &obj.Min_Water_Bowl, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Max_Water_Bowl';", callback, &obj.Max_Water_Bowl, &dbl_error);

    // Water Processing
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Water_Stomach';", callback, &obj.Water_Stomach, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Water_Stomach_Min';", callback, &obj.Water_Stomach_Min, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Water_Stomach_Max';", callback, &obj.Water_Stomach_Max, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Processed';", callback, &obj.Processed, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Processed_Min';", callback, &obj.Processed_Min, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Processed_Max';", callback, &obj.Processed_Max, &dbl_error);

    // Food Digestion
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Stomach';", callback, &obj.Stomach, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Stomach_Min';", callback, &obj.Stomach_Min, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Stomach_Max';", callback, &obj.Stomach_Max, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Digested';", callback, &obj.Digested, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Digested_Min';", callback, &obj.Digested_Min, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Digested_Max';", callback, &obj.Digested_Max, &dbl_error);

    // Food
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Food';", callback, &obj.Food, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Max_Food';", callback, &obj.Max_Food, &dbl_error);
    // Plate
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Plate';", callback, &obj.Plate, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Min_Plate';", callback, &obj.Min_Plate, &dbl_error);
    rc = sqlite3_exec(master_db, "SELECT Stat FROM iVariables WHERE iv_Name = 'Max_Plate';", callback, &obj.Max_Plate, &dbl_error);

    sqlite3_close(master_db);
    return (rc == SQLITE_OK);
}

bool Make_sql3(const char* sz_filename)
{
    char* cr_error;
    //int bDB_Ok;
    sqlite3* master_db;

    //Create Database

    int rc = sqlite3_open_v2(sz_filename, &master_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if ( rc == SQLITE_OK)
    {

        //// Create Tables
        // Companions / Saves (Personal)
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS Companions(cName CHAR, Age INTEGER, Health INTEGER, Mass INTEGER); ", NULL, NULL, &cr_error);
        // Live Stats (Personal)
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS LiveStats(Hunger INTEGER, Starvation \
                                         fk_Name CHAR DEFAULT 0 REFERENCES Companions(cName)); ", NULL, NULL, &cr_error);
        // Digestion Stats (Static / Global)
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS Digestion(InStomach INTEGER, Digested INTEGER, Waste INTEGER); ", NULL, NULL, &cr_error);
        // Food Caps (Static / Global)
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS FoodCaps(fc_Name STRING, fc_value INTEGER); ", NULL, NULL, &cr_error);
        // Adding Data to Food Caps
        sqlite3_exec(master_db, "INSERT INTO FoodCaps (fc_Name) values ('Stomach_Cap', 'Waste_Cap');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodCaps (fc_value) values ('300', '550');", NULL, NULL, &cr_error);

        // Food Types (Static / Global)
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS FoodTypes(fName STRING, fCalories INTEGER, fVitamins INTEGER, fCarbs INTEGER, fSugar INTEGER, fEmotion INTEGER); ", NULL, NULL, &cr_error);
        // fk_fCompStats_id INTEGER DEFAULT 0 REFERENCES fComponentStats(fCompStats_id)); ", NULL, NULL, &cr_error); FIXME: Foreign Keys
        // fk_fCompStats_id INTEGER DEFAULT 0 REFERENCES fComponentStats(fCompStats_id)); ", NULL, NULL, &cr_error); FIXME: Foreign Keys
    // Adding Food & Food Stats to Table - Name, Calories, Vitamins %, Carbs %, Sugar %, Emotion // This is unused, its part of a future more complex food system
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (fName, fCalories, fVitamins, fCarbs, fSugar, fEmotion) values ('Roast_Bitato', '150', '10', '90', '0', '2');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (fName, fCalories, fVitamins, fCarbs, fSugar, fEmotion) values ('Bizza_Slice', '250', '0', '100', '0', '2');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (fName, fCalories, fVitamins, fCarbs, fSugar, fEmotion) values ('Carrit', '50', '100', '0', '0', '1');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (fName, fCalories, fVitamins, fCarbs, fSugar, fEmotion) values ('Mediterranean_Balad', '100', '90', '10', '0', '1');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (fName, fCalories, fVitamins, fCarbs, fSugar, fEmotion) values ('Boughnut', '300', '0', '50', '50', '3');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (fName, fCalories, fVitamins, fCarbs, fSugar, fEmotion) values ('Chocobit_Brownie', '300', '0', '50', '50', '3');", NULL, NULL, &cr_error);
        // Food Component Stats (Static / Global) // PER ONE CALORIE
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS fComponentStats(fCompStats_id INTEGER PRIMARY KEY AUTOINCREMENT, Component CHAR, hpReduction DOUBLE, hpRestore DOUBLE, DigestionTime DOUBLE); ", NULL, NULL, &cr_error);
        // Adding Food Component Stats (Static / Global) // Try Not to Touch
        sqlite3_exec(master_db, "INSERT INTO fComponentStats (Component, hpReduction, hpRestore, DigestionTime) values ('csVitamins', '0.3', '0.5', '120000');", NULL, NULL, &cr_error); // Digestion Time in ms
        sqlite3_exec(master_db, "INSERT INTO fComponentStats (Component, hpReduction, hpRestore, DigestionTime) values ('csCarbs', '0.15', '0.1', '60000');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO fComponentStats (Component, hpReduction, hpRestore, DigestionTime) values ('csSugar', '0.05', '0', '30000');", NULL, NULL, &cr_error);
        // Living Variables
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS iVariables(iv_Name CHAR, Stat REAL); ", NULL, NULL, &cr_error);
        // Adding Default Variable Stats
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Age', '0.0');", NULL, NULL, &cr_error);
        // Health
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Health', '1.0');", NULL, NULL, &cr_error);
        //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Health', '1.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Min_Health', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Health', '1.0');", NULL, NULL, &cr_error);
        // Hunger
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Hunger', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Hunger', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Hunger', '1.0');", NULL, NULL, &cr_error);
        //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Hunger_Rate', '0.0');", NULL, NULL, &cr_error);
        // Starv
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Starv', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Starv', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Starv', '1.0');", NULL, NULL, &cr_error);
        //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Starv_Rate', '0.0');", NULL, NULL, &cr_error);
        // Thirst
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Thirst', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Thirst', '0.0');", NULL, NULL, &cr_error); // Def = Min
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Thirst', '1.0');", NULL, NULL, &cr_error);
        //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Thirst_Rate', '0.0');", NULL, NULL, &cr_error);
        // Dehydration
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Dehy', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Dehy_Min', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Dehy_Max', '1.0');", NULL, NULL, &cr_error);
        //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Def_Dehy_Rate', '0.0');", NULL, NULL, &cr_error);
        // Water Processing
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Water_Stomach', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Water_Stomach_Min', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Water_Stomach_Max', '1.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Processed', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Processed_Min', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Processed_Max', '1.0');", NULL, NULL, &cr_error);
        // Water
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Water_Bowl', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Min_Water_Bowl', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Water_Bowl', '1.0');", NULL, NULL, &cr_error);
        // Food
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Plate', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Min_Plate', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Plate', '1.5');", NULL, NULL, &cr_error);
        // Cantina
        //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Food', '1.0');", NULL, NULL, &cr_error); 
        //sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Max_Food', '0.3');", NULL, NULL, &cr_error);
        // Food Calories
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Stomach', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Stomach_Min', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Stomach_Max', '1.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Digested', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Digested_Min', '0.0');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO iVariables (iv_Name, Stat) values ('Digested_Max', '1.0');", NULL, NULL, &cr_error);
    }
    sqlite3_close(master_db);
    return (rc == SQLITE_OK);
}

bool PetMgr::Save_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/)
{
    bool result = false;
    switch (db_type)
    {
    case DB_Type::FILE:
    {
        std::ofstream inFile{ sz_filename, std::ios::in | std::ios::binary };
        if (inFile.good())
        {
            inFile.write(reinterpret_cast<char*>(&petVar), sizeof(PetVars));
            result = true;
        }
        inFile.close();
    }break;

    case DB_Type::SQLITE:
    {
        // this can be changed to an more effective way
        if(!Save_sql3(sz_filename, petVar))
        {
            Make_sql3(sz_filename);
            if (!Save_sql3(sz_filename, petVar))
            {
                throw "error save/create db !!";
            }
        }
        result = true;
    }break;
    default: break;
    }
    return result;
}

bool PetMgr::Load_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/)
{
    bool result = false;
    switch (db_type)
    {
    case DB_Type::FILE:
    {
        std::ifstream inFile{ sz_filename, std::ios::in | std::ios::binary };
        if (inFile.good())
        {
            inFile.read(reinterpret_cast<char*>(&petVar), sizeof(PetVars));
            result = true;
        }
        inFile.close();
    }break;

    case DB_Type::SQLITE:
    {
        if (!Load_sql3(sz_filename, petVar))
        {
            Make_sql3(sz_filename);
            if (!Load_sql3(sz_filename, petVar))
            {
                throw "error save/create db !!";
            }
        }
        result = true;
    }break;
        default: break;
    }
    return result;
}

#ifdef _DEBUG
void PetMgr::logDB_CMD()
{
    PetVars petVar;
    printf("\x1B[2J\x1B[H");  // clear console screen

    printf_s("\n\nStats: \n");
    printf_s("\n%.2f Age \n", petVar.Age);

    printf_s("%.2f Health \n", petVar.Health);
    //printf_s("%.2f Min_Health \n", petVar.Min_Health);
    //printf_s("%.2f Max_Health \n", petVar.Max_Health);

    printf_s("%.2f Hunger \n", petVar.Hunger);
    //printf_s("%.2f Def_Hunger \n", petVar.Def_Hunger);
    //printf_s("%.2f Max_Hunger \n", petVar.Max_Hunger);
    //printf_s("%.2f Def_Hunger_Rate \n", petVar.Def_Hunger_Rate);

    printf_s("%.2f Starvation \n", petVar.Starv);
    //printf_s("%.2f Def_Starv \n", petVar.Def_Starv);
    //printf_s("%.2f Max_Starv \n", petVar.Max_Starv);
    //printf_s("%.2f Def_Starv_Rate \n", petVar.Def_Starv_Rate);

    printf_s("%.2f Stomach \n", petVar.Stomach);
    //printf_s("%.2f Stomach_Min \n", petVar.Stomach_Min);
    //printf_s("%.2f Stomach_Max \n", petVar.Stomach_Max);

    printf_s("%.2f Digested \n", petVar.Digested);
    //printf_s("%.2f Digested_Min \n", petVar.Stomach_Min);
    //printf_s("%.2f Digested_Max \n", petVar.Digested_Max);

    printf_s("%.2f Plate \n", petVar.Plate);
    //printf_s("%.2f Min_Plate \n", petVar.Min_Plate);
    //printf_s("%.2f Max_Plate \n", petVar.Max_Plate);

    printf_s("%.2f Thirst \n", petVar.Thirst);
    //printf_s("%.2f Def_Thirst \n", petVar.Def_Thirst);
    //printf_s("%.2f Max_Thirst \n", petVar.Max_Thirst);
    //printf_s("%.2f Def_Thirst_Rate \n", petVar.Def_Thirst_Rate);

    printf_s("%.2f Dehydration \n", petVar.Dehy);
    //printf_s("%.2f Dehy_Min \n", petVar.Dehy_Min);
    //printf_s("%.2f Dehy_Max \n", petVar.Dehy_Max);
    //printf_s("%.2f Def_Dehy_Rate \n", petVar.Def_Dehy_Rate);

    printf_s("%.2f Water_Stomach \n", petVar.Water_Stomach);
    //printf_s("%.2f Water_Stomach_Min \n", petVar.Water_Stomach_Min);
    //printf_s("%.2f Water_Stomach_Max \n", petVar.Water_Stomach_Max);

    printf_s("%.2f Processed \n", petVar.Processed);
    //printf_s("%.2f Processed_Min \n", petVar.Stomach_Min);
    //printf_s("%.2f Processed_Max \n", petVar.Processed_Max);

    printf_s("%.2f Water_Bowl \n", petVar.Water_Bowl);
    //printf_s("%.2f Min_Water_Bowl \n", petVar.Min_Water_Bowl);
    //printf_s("%.2f Max_Water_Bowl \n", petVar.Max_Water_Bowl);

    printf_s("Is the pet alive? %s \n", (petVar.ALIVE ? "Yes" : "The RSPCA Has been Notified.") ); // bool in c++ know // cool, just that starv taking a while to update it was at -0.40
}

#else
void StatVars::logDB_CMD(){}
#endif


void PetMgr::Update()
{
    addAge();
    Eater();
    Digester();
    StarvManager();
    Drinker();
    H2OProcessor();
    DehyManager();

    logDB_CMD();
}


// When button pressed make food avaiable
void PetMgr::Feeder()
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Plate < petVar.Max_Plate) // Add food to Plate if not Full
        {
            petVar.Plate += 20.00f;
            if (petVar.Plate > petVar.Max_Plate)
            {
                petVar.Plate = petVar.Max_Plate;
            }
        }
        else // Plate Full inform user
        {
            petVar.Plate = petVar.Max_Plate;
            std::cout << "Plate Full" << std::endl;
        }
    }
}

// If Plate has Food - Eat and fill Stomach
void PetMgr::Eater() // 
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Plate > petVar.Min_Plate) // If Plate has food
        {
            if (petVar.Hunger > 0.05f && (petVar.AWAKE == true)) // If Hungry
            {
                if (petVar.Stomach < petVar.Stomach_Max) // Eat food if not full //          Must put limit on Times can be fed in one day // This I'll add later
                {
                    petVar.Plate -= 0.03f; // Reduce Food available to eat 3f max 0/3
                    petVar.Stomach += 0.3f; // Increase Ingested Calories // 
                }
                else
                {
                    std::cout << "Companion cannot eat any more" << std::endl;
                }
            }
        }
    }
}

// If has consumed food, digest food
void PetMgr::Digester()
{
    if (petVar.ALIVE == true) //Alive Check
    {
        if (petVar.Stomach > petVar.Stomach_Min && petVar.Digested < petVar.Digested_Max) // If ingested calories > 0 some not good here
        {
            //std::clamp(petVar.Stomach, petVar.Stomach_Min, petVar.Stomach_Max);

            petVar.Stomach -= 0.025f;
            petVar.Digested += 0.025f;
            if (petVar.Stomach < petVar.Stomach_Min)
            {
                petVar.Stomach = petVar.Stomach_Min;
            }
            if (petVar.Hunger > petVar.Def_Hunger) // Reduce Hunger and Starvation when Digesting
            {
                petVar.Hunger -= 0.02f;
                if (petVar.Hunger < petVar.Def_Hunger)
                {
                    petVar.Hunger = petVar.Def_Hunger;
                }

            }
        }
        if (petVar.Digested > petVar.Digested_Min)
        {
            petVar.Digested -= 0.006f;

            if (petVar.Digested < petVar.Digested_Min)
            {
                petVar.Digested = petVar.Digested_Min;
            }
            if (petVar.Health < petVar.Max_Health)
            {
                petVar.Health += 0.01f;
            }
            if (petVar.Starv > petVar.Def_Starv && petVar.Digested > petVar.Digested_Min)
            {
                petVar.Starv -= 0.04f;
            }
        }
        if (petVar.Digested <= petVar.Digested_Min)
        {
            petVar.Hunger += 0.025f;
        }
    }
    else
    {
        // cant feed an dead pet
        petVar.ALIVE = false;
    }

}

void PetMgr::StarvManager() // Starv Manager
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Health <= petVar.Min_Health)
        {
            petVar.ALIVE = false;
            std::cout << "Starvation Death" << std::endl;
        }
        //Hunger & Starv Cap 
        if (petVar.Hunger >= petVar.Max_Hunger)
        {
            petVar.Hunger = petVar.Max_Hunger;
            petVar.Starv += 0.01f;
        }
        if (petVar.Starv >= petVar.Max_Starv)
        {
            petVar.Starv = petVar.Max_Starv;
            petVar.Health -= 0.0025f;
        }
    }
}


//// Water Stat Loops

// Fill Water Bowl with Button Press
void PetMgr::Hydrater()
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Water_Bowl < petVar.Max_Water_Bowl) // Add Water to Bowl if not Full // Want to add 1% until its 100 animation
        {
            petVar.Water_Bowl += 20.0f;
            if (petVar.Water_Bowl > petVar.Max_Water_Bowl)
            {
                petVar.Water_Bowl = petVar.Max_Water_Bowl;
            }
        }
        else // Bowl Full inform user
        {
            petVar.Water_Bowl = petVar.Max_Water_Bowl;
            std::cout << "Water Bowl Full" << std::endl;
        }
    }

}

// Drink Water if Thirsty and Water available
void PetMgr::Drinker()
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Water_Bowl > petVar.Min_Water_Bowl)
        {
            if (petVar.Thirst > petVar.Def_Thirst && (petVar.AWAKE == true)) 
            {
                if (petVar.Water_Stomach < petVar.Water_Stomach_Max)
                {
                    petVar.Water_Bowl -= 0.10f;
                    petVar.Water_Stomach += 0.10f; 
                }
                else
                {
                    std::cout << "Companion cannot eat any more" << std::endl;
                }
            }
        }
    }
}

// If has consumed water, reduced consumed water
void PetMgr::H2OProcessor()
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Water_Stomach > petVar.Water_Stomach_Min && petVar.Processed < petVar.Processed_Max)
        {
            petVar.Water_Stomach -= 0.10f;
            petVar.Processed += 0.10f;
            if (petVar.Water_Stomach < petVar.Water_Stomach_Min)
            {
                petVar.Water_Stomach = petVar.Water_Stomach_Min;
            }
            if (petVar.Thirst > petVar.Def_Thirst)
            {
                petVar.Thirst -= 0.010f;
                if (petVar.Thirst < petVar.Def_Thirst)
                {
                    petVar.Thirst = petVar.Def_Thirst;
                }
            }
        }
        if (petVar.Processed > petVar.Processed_Min) 
        {
            petVar.Processed -= 0.005f;

            if (petVar.Processed < petVar.Processed_Min)
            {
                petVar.Processed = petVar.Processed_Min;
            }
            if (petVar.Health < petVar.Max_Health)
            {
                petVar.Health += 0.01f;
            }
            if (petVar.Dehy > petVar.Dehy_Min && petVar.Processed > petVar.Processed_Min)
            {
                petVar.Dehy -= 0.06f;
            }
        }
        if (petVar.Processed <= petVar.Processed_Min)
        {
            petVar.Thirst += 0.07f;
        }
    }
    else
    {
        petVar.ALIVE = false;
    }
}

// If Thirst is Max increase Dehydration, if Dehydration is Max reduce health
void PetMgr::DehyManager()
{
    if (petVar.ALIVE == true)
    {
        // Thirstcheck if alive
        if (petVar.Health <= petVar.Min_Health)
        {
            petVar.ALIVE = false;
            std::cout << "Dehyation Death" << std::endl;
        }
        //Thirst & Dehy Cap 
        if (petVar.Thirst >= petVar.Max_Thirst)
        {
            petVar.Thirst = petVar.Max_Thirst;
            petVar.Dehy += 0.03f;
        }
        if (petVar.Dehy >= petVar.Dehy_Max)
        {
            petVar.Dehy = petVar.Dehy_Max;
            petVar.Health -= 0.025f;
        }
    }
}

//Age
void PetMgr::addAge()
{
    if (petVar.ALIVE == true)
    { petVar.Age += 0.01f; }
}


