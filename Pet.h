#pragma once

#include <SFML/Graphics/Texture.hpp>

class food_data
{
public:

    char food_name[100] = "void \0";
    float hunger_reduction = 0;
    int health_restore = 0;
    int digestion_time = 0;
    int dish_fill = 0;
};

class potato : public food_data
{
public:

    char food_name[100] = "Potato";
    float hunger_reduction = 40.0f;
    int health_restore = 40.0f;
    int digestion_time = 20.0f;
    int fill = 2.0f;
};

class food_menu
{

public:

    food_data potato, pizza, carrot, salad, doughnut, brownie;
};


class food_manager
{
public:
    food_menu food_menu_obj;

    enum class DB_Type
    {
        FILE,
        SQLITE
    };

    void Eater();
    bool food_list(bool& show);
    float dish_min = 0.0f;
    float dish_max = 100.0f;
    float dish_current = 0.0f;
    int dish_fill(int fill, int digestion_time);

    bool dish_full(bool& show);

    const char* food_empty = { "has no food!" };

   void food_updater();
};
extern const char* sqlstatement(const char* format, ...);

class Pet_Manager
{
public:
    std::string pet_name = "N/A";

    std::string status = "N/A";
    std::string status_hungry = "Hungry";
    std::string status_thirsty = "Thirsty";
    std::string status_dead = "Deceased";
    std::string dish_full_error = "hasn't finished eating!";
    std::string thirst_death = "died of dehydration.";
    std::string starv_death = "died of stavation.";
    std::string cause_of_death= "error";


    // Living
    float Age = 0.0;
    bool ALIVE = true;
    bool AWAKE = true;

    // Health
    float Health = 90.0;
    float Def_Health = 0.0;
    float Max_Health = 100.0;
    float Min_Health = 0.0;

    //// Food
    // Feeding
    float Plate = 0.0;
    float Min_Plate = 0.0;
    float Max_Plate = 150.0;
    // Food
    float Food = 0.0;
    float Max_Food = 100.0;
    // Hunger
    float Hunger = 0.0;
    float Def_Hunger = 0.0;
    float Max_Hunger = 100.0;
    float Def_Hunger_Rate = 0.0;
    // Starvation
    float Starv = 0.0;
    float Def_Starv = 0.0;
    float Max_Starv = 100.0;
    float Def_Starv_Rate = 0.0;
    // Digestion
    float Stomach = 0.0;
    float Stomach_Min = 0.0;
    float Stomach_Max = 100.0;
    float Digested = 0.0;
    float Digested_Min = 0.0;
    float Digested_Max = 100.0;

    //// Water
    // Water Bowl
    float Water_Bowl = 0.0;
    float Min_Water_Bowl = 0.0;
    float Max_Water_Bowl = 150.0;
    // Thirst
    float Thirst = 0.0;
    float Def_Thirst = 0.0;
    float Max_Thirst = 100.0;
    float Def_Thirst_Rate = 0.0;
    // Dehydration
    float Dehy = 0.0;
    float Dehy_Min = 0.0;
    float Dehy_Max = 0.0;
    float Def_Dehy_Rate = 0.0;
    // Water Processing
    float Water_Stomach = 0.0;
    float Water_Stomach_Min = 0.0;
    float Water_Stomach_Max = 100.0;
    float Processed = 0.0;
    float Processed_Min = 0.0;
    float Processed_Max = 100.0;

public:
    enum class DB_Type
    {
        FILE,
        SQLITE
    };


    void addAge();

    void Digester();
    void StarvManager();

    void Hydrater();
    void Drinker();
    void H2OProcessor();
    void DehyManager();
    bool pet_death(bool& show, std::string cause_of_death);

    //void logDB_CMD();
public:
    void Update();
public:

    bool Save_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
    bool Load_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
    bool Make_sql3(const char* sz_filename);
    bool Load_sql3(const char* sz_filename, Pet_Manager& pobj, food_manager& food_manager_obj);
};
extern food_manager *selected_food;






