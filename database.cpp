
#include "Pet.h"
#include "food.h"

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

// Pet Vars
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

// Food Menu
bool Save_sql3(const char* sz_filename, food_menu obj2)
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


// PetVars
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

    //rc = sqlite3_exec(master_db, "SELECT Stat FROM FoodTypes WHERE food_Name = 'Brownie';", callback, &obj, &dbl_error);

    // I gotta add the rest
    sqlite3_close(master_db);
    return (rc == SQLITE_OK);
}

// Food Menu
bool Load_sql3(const char* sz_filename, food_menu& obj2)
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

// Food Hunger Reduction
rc = sqlite3_exec(master_db, "SELECT hunger_reduction FROM FoodTypes WHERE food_Name = 'Roast_Potato';", callback, &obj2.potato.hunger_reduction, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT hunger_reduction FROM FoodTypes WHERE food_Name = 'Pizza_Slice';", callback, &obj2.pizza.hunger_reduction, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT hunger_reduction FROM FoodTypes WHERE food_Name = 'Carrot';", callback, &obj2.carrot.hunger_reduction, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT hunger_reduction FROM FoodTypes WHERE food_Name = 'Salad';", callback, &obj2.salad.hunger_reduction, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT hunger_reduction FROM FoodTypes WHERE food_Name = 'Doughnut';", callback, &obj2.doughnut.hunger_reduction, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT hunger_reduction FROM FoodTypes WHERE food_Name = 'Brownie';", callback, &obj2.brownie.hunger_reduction, &dbl_error);

// Food Health Restore
rc = sqlite3_exec(master_db, "SELECT health_restore FROM FoodTypes WHERE food_Name = 'Roast_Potato';", callback, &obj2.potato.health_restore, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT health_restore FROM FoodTypes WHERE food_Name = 'Pizza_Slice';", callback, &obj2.pizza.health_restore, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT health_restore FROM FoodTypes WHERE food_Name = 'Carrot';", callback, &obj2.carrot.health_restore, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT health_restore FROM FoodTypes WHERE food_Name = 'Salad';", callback, &obj2.salad.health_restore, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT health_restore FROM FoodTypes WHERE food_Name = 'Doughnut';", callback, &obj2.doughnut.health_restore, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT health_restore FROM FoodTypes WHERE food_Name = 'Brownie';", callback, &obj2.brownie.health_restore, &dbl_error);

// Food Health Restore
rc = sqlite3_exec(master_db, "SELECT dish_fill FROM FoodTypes WHERE food_Name = 'Roast_Potato';", callback, &obj2.potato.dish_fill, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT dish_fill FROM FoodTypes WHERE food_Name = 'Pizza_Slice';", callback, &obj2.pizza.dish_fill, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT dish_fill FROM FoodTypes WHERE food_Name = 'Carrot';", callback, &obj2.carrot.dish_fill, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT dish_fill FROM FoodTypes WHERE food_Name = 'Salad';", callback, &obj2.salad.dish_fill, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT dish_fill FROM FoodTypes WHERE food_Name = 'Doughnut';", callback, &obj2.doughnut.dish_fill, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT dish_fill FROM FoodTypes WHERE food_Name = 'Brownie';", callback, &obj2.brownie.dish_fill, &dbl_error);

// Food Digestion Time
rc = sqlite3_exec(master_db, "SELECT digestion_time FROM FoodTypes WHERE food_Name = 'Roast_Potato';", callback, &obj2.potato.digestion_time, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT digestion_time FROM FoodTypes WHERE food_Name = 'Pizza_Slice';", callback, &obj2.pizza.digestion_time, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT digestion_time FROM FoodTypes WHERE food_Name = 'Carrot';", callback, &obj2.carrot.digestion_time, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT digestion_time FROM FoodTypes WHERE food_Name = 'Salad';", callback, &obj2.salad.digestion_time, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT digestion_time FROM FoodTypes WHERE food_Name = 'Doughnut';", callback, &obj2.doughnut.digestion_time, &dbl_error);
rc = sqlite3_exec(master_db, "SELECT digestion_time FROM FoodTypes WHERE food_Name = 'Brownie';", callback, &obj2.brownie.digestion_time, &dbl_error);


//rc = sqlite3_exec(master_db, "SELECT Stat FROM FoodTypes WHERE food_Name = 'Brownie';", callback, &obj, &dbl_error);

// I gotta add the rest
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
        sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS FoodTypes(food_Name STRING, hunger_reduction DOUBLE, health_restore INTEGER, digestion_time INTEGER, fEmotion INTEGER); ", NULL, NULL, &cr_error);
        // Adding Food & Food Stats to Table - Name, Calories, Vitamins %, Carbs %, Sugar %, Emotion // This is unused, its part of a future more complex food system
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (food_Name, hunger_reduction, health_restore, digestion_time, dish_fill, fEmotion) values ('Roast_Potato', '24.75', '21', '165', '25', '2');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (food_Name, hunger_reduction, health_restore, digestion_time, dish_fill, fEmotion) values ('Pizza_Slice', '37.5', '25', '250', '15', '2');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (food_Name, hunger_reduction, health_restore, digestion_time, dish_fill, fEmotion) values ('Carrot', '15', '25', '100', '5', '1');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (food_Name, hunger_reduction, health_restore, digestion_time, dish_fill, fEmotion) values ('Salad', '28.5', '46', '190', '10', '1');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (food_Name, hunger_reduction, health_restore, digestion_time, dish_fill, fEmotion) values ('Doughnut', '30', '15', '225', '40', '3');", NULL, NULL, &cr_error);
        sqlite3_exec(master_db, "INSERT INTO FoodTypes (food_Name, hunger_reduction, health_restore, digestion_time, dish_fill, fEmotion) values ('Brownie', '30', '15', '225', '40','3');", NULL, NULL, &cr_error);
            //// Food Component Stats (Static / Global) // PER ONE CALORIE
            //sqlite3_exec(master_db, "PRAGMA foreign_keys = ON; CREATE TABLE IF NOT EXISTS fComponentStats(fCompStats_id INTEGER PRIMARY KEY AUTOINCREMENT, Component CHAR, hpReduction DOUBLE, hpRestore DOUBLE, DigestionTime DOUBLE); ", NULL, NULL, &cr_error);
            //// Adding Food Component Stats (Static / Global) // Try Not to Touch
            //sqlite3_exec(master_db, "INSERT INTO fComponentStats (Component, hpReduction, hpRestore, DigestionTime) values ('csVitamins', '0.3', '0.5', '120000');", NULL, NULL, &cr_error); // Digestion Time in ms
            //sqlite3_exec(master_db, "INSERT INTO fComponentStats (Component, hpReduction, hpRestore, DigestionTime) values ('csCarbs', '0.15', '0.1', '60000');", NULL, NULL, &cr_error);
            //sqlite3_exec(master_db, "INSERT INTO fComponentStats (Component, hpReduction, hpRestore, DigestionTime) values ('csSugar', '0.05', '0', '30000');", NULL, NULL, &cr_error);
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

bool Pet_Manager::Save_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/)
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

bool Pet_Manager::Load_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/)
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

bool food_manager::Save_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/)
{
    bool result = false;
    switch (db_type)
    {
    case DB_Type::FILE:
    {
        std::ofstream inFile{ sz_filename, std::ios::in | std::ios::binary };
        if (inFile.good())
        {
            inFile.write(reinterpret_cast<char*>(&food_menu_obj), sizeof(food_menu));
            result = true;
        }
        inFile.close();
    }break;

    case DB_Type::SQLITE:
    {
        // this can be changed to an more effective way
        if (!Save_sql3(sz_filename, food_menu_obj))
        {
            Make_sql3(sz_filename);
            if (!Save_sql3(sz_filename, food_menu_obj))
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

bool food_manager::Load_DB(const char* sz_filename, DB_Type db_type /*= DB_Type::FILE*/)
{
    bool result = false;
    switch (db_type)
    {
    case DB_Type::FILE:
    {
        std::ifstream inFile{ sz_filename, std::ios::in | std::ios::binary };
        if (inFile.good())
        {
            inFile.read(reinterpret_cast<char*>(&food_menu_obj), sizeof(food_menu));
            result = true;
        }
        inFile.close();
    }break;

    case DB_Type::SQLITE:
    {
        if (!Load_sql3(sz_filename, food_menu_obj))
        {
            Make_sql3(sz_filename);
            if (!Load_sql3(sz_filename, food_menu_obj))
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
void Pet_Manager::logDB_CMD()
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




