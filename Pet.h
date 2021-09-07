#pragma once

#include <SFML/Graphics/Texture.hpp>

class Pet_Manager
{

// Pet Variables
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
    float age_track = 0.0;
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
    float Digested_Max = 300.0;

    //// Water
    // Water Bowl
    float Add_Water = 25.0;
    float Water_Bowl = 0.0;
    float Min_Water_Bowl = 0.0;
    float Max_Water_Bowl = 100.0;
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
    float Water_Stomach_Max = 200.0;
    float Processed = 0.0;
    float Processed_Min = 0.0;
    float Processed_Max = 100.0;


// Food
public:
    const char* food_label_arr[6] = { "Potato", "Pizza","Carrot", "Salad", "Doughnut", "Brownie" };
    float hunger_reduction[6] = { 24.75,37.5,15,28.5,30,30 };
    int health_restore[6] = { 21,25,25,46,15,15 };
    int digestion_time[6] = { 165,250,100,190,225,225 };
    int dish_filler[6] = { 30,60,20,40,50,50 };

    enum class DB_Type
    {
        FILE,
        SQLITE
    };

    float dish_min = 0.0f;
    float dish_max = 100.0f;
    float dish_current = 0.0f;

    const char* food_empty = { "has no food!" };

    void addAge();

    void Digester();
    void StarvManager();

    void Hydrater();
    void Drinker();
    void H2OProcessor();
    void DehyManager();
    bool pet_death(bool& show, std::string cause_of_death);

    void Eater()
    {
        if (ALIVE == true)
        {
            float stomach_space = Stomach_Max - Stomach;
            if (dish_current > dish_min && Hunger > 15.0f && Stomach < Stomach_Max)
            {
                if (Hunger > 30.0f)
                {
                    dish_current -= 0.2f;
                    Stomach += 0.2f;
                }
                if (Hunger > 60.0f)
                {
                    dish_current -= 0.3f;
                    Stomach += 0.3f;
                }
                if (Hunger > 90.0f)
                {
                    dish_current -= 0.4f;
                    Stomach += 0.4f;
                }
                dish_current -= 0.1f; // Reduce Food available to eat 3f max 0/3
                Stomach += 0.1f; // Increase Ingested Calories
            }
            if (Stomach >= Stomach_Max)
            {
                std::cout << "Companion cannot eat any more" << std::endl;
            }
        }
    }

    int dish_fill(int dish_fill, int digestion_time)
    {
        float dish_space = dish_max - dish_current;
        static bool show = false;
        if (dish_space >= dish_fill)
        {
            dish_current += dish_fill;
            digestion_time += digestion_time;
        }
        //ImGui::Text("Can't add any more food!");
        return digestion_time;
    }

    bool food_list(bool& show);

    //void logDB_CMD();
public:
    void Update();
public:

    //bool Save_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
    //bool Load_DB(const char* sz_filename, DB_Type db_type = DB_Type::FILE);
    //bool Make_sql3(const char* sz_filename);
    //bool Load_sql3(const char* sz_filename, Pet_Manager& pobj, food_manager& food_manager_obj);
};
//extern food_manager *selected_food;

extern const char* sqlstatement(const char* format, ...);




