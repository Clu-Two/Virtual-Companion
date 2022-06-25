#pragma once

class GUI
{
public: // Textures & Sprites
    static const int texture_count = 7;

    sf::Texture habitat, pet, food, water, feed, life, close_button;
    sf::Texture TEXTURES[texture_count] = { habitat, pet, food, water, feed, life, close_button };
    sf::Texture* pTEX = TEXTURES;

    sf::Sprite hab_spr, pet_spr, food_spr, water_spr, feed_spr, life_spr, close_button_spr;
    sf::Sprite SPRITES[texture_count] = { hab_spr, pet_spr, food_spr, water_spr, feed_spr, life_spr, close_button_spr };

    const char* habitat_tf = "sprites\\Habitat.jpg";
    const char* pet_tf = "sprites\\pet_red.png";
    const char* food_tf = "sprites\\food.png";
    const char* water_tf = "sprites\\water.png";
    const char* feed_tf = "sprites\\feed.png";
    const char* life_tf = "sprites\\life_sheet.png";
    const char* close_button_tf = "sprites\\close_button.png";
    const char* texture_files[texture_count] = 
    { habitat_tf, pet_tf, food_tf, water_tf, feed_tf, life_tf, close_button_tf };

    void texture_loader(sf::Texture& tex, const char* texture_files)
    {
        if(tex.loadFromFile(texture_files))
        {std::cout << "// loaded OK from - " << texture_files << std::endl; }
    }

    void sprite_loader(sf::Sprite& spr, sf::Texture& tex)
    {
        spr.setTexture(tex);
        std::cout << "// texture set at - " << &tex << std::endl;
    }

public: // Coordinates
    int window_x = 600, window_y = 400;
    sf::Vector2f habitat_xy = { 0,0 };
    sf::Vector2f pet_xy = { 300, 272 };
    sf::Vector2f food_xy = { 100, 250 };
    sf::Vector2f water_xy = { 450,4 };
    sf::Vector2f feed_xy = { 25, 300 };
    sf::Vector2f life_xy = { 50,0 };
    sf::Vector2f close_button_xy = { 0,0 };
    sf::Vector2f SPRITES_xy[texture_count] = {habitat_xy, pet_xy, food_xy, water_xy, feed_xy, life_xy, close_button_xy};

    bool sprites_inital_load = false;
};

class Animator : public GUI
{
public: // Mouse & GUI Button Interaction Regions
    sf::IntRect exit_application{ 0, 0, 50,50 };

public: // Default size of sprite rects - four coordinates x1y1x2y2
    sf::IntRect habitat_defRect = { 0,0,1280, 720 };
    sf::IntRect pet_defRec = { 0,0,130,128 };
    sf::IntRect food_defRect{ 0,0, 150, 150 };
    sf::IntRect water_defRec{ 1390,0,139,237 };
    sf::IntRect feed_default_defRec{ 0,0, 50, 50 };
    sf::IntRect feed_idle_defRec{ 0,0, 50, 50 };
    sf::IntRect feed_active_defRec{ 50, 0, 50, 50 };
    sf::IntRect feed_state[2]{ feed_idle_defRec, feed_active_defRec };
    int feed_index = 0;
    sf::IntRect exit_default_defRec{ 0,0, 50, 50 };
    sf::IntRect exit_idle_defRec{ 0,0, 50, 50 };
    sf::IntRect exit_active_defRec{ 50, 0, 50, 50 };
    sf::IntRect exit_state[2]{ exit_idle_defRec, exit_active_defRec }; // Rework this I don't think its needed
    int exit_index = 0;
    sf::IntRect life_max_defRect{ 0, 0, 300, 100 };
    sf::IntRect life_half_defRect{ 0, 0, 200, 100 };
    sf::IntRect life_min_defRect{ 0, 0, 100, 100 };
    sf::IntRect life_state[3]{ life_max_defRect ,life_half_defRect, life_min_defRect };
    int life_index = 0;
    sf::IntRect Default_Sprite_Rects[texture_count] = { habitat_defRect, pet_defRec, food_defRect, water_defRec, feed_idle_defRec, life_max_defRect, exit_idle_defRec };

    enum Sprite_Index
    {
        HABITAT,
        PET,
        FOOD,
        WATER,
        FEED,
        LIFE,
        EXIT
    };

public: // Food
    int x1 = 0, y1 = 0, x2 = 300, y2 = 300;
    //sf::IntRect food_default_rect{ x1, y1, 137, 136 };
    int gui_Food(float Dish);
    int food_increment = 300;
    sf::IntRect food_100{ 0,0,150,150 };
    sf::IntRect food_75{ 150,0,150,150 };
    sf::IntRect food_50{ 300,0,150,150 };
    sf::IntRect food_25{ 450,0,150,150 };
    sf::IntRect food_0{ 600,0,150,150 };
    sf::IntRect food_states[5] = { food_100, food_75 ,food_50 ,food_25 ,food_0};
    int food_sprite_index = 0;
    sf::IntRect feed_cb{ 25,300,50,50 };

public: // Water
    sf::IntRect water_click_box{ 450, 4, 600,200 };
    sf::IntRect water_rect_default{ 0,0,62,102 };
    sf::IntRect water_rect{ 0,0,62,102 };
    sf::IntRect click_water_rect{ 62,0,62,102 };
    //sf::IntRect Water[2]{ water_rect ,click_water_rect };

    int water_x1_min = 0;
    int water_x1_increment = 139;
    int water_x1_max = 1390; 
    int water_x1_current = 1390;
    sf::IntRect water_s{ water_x1_current,0,139,237 };
    int gui_Water(float Water_Bowl);
 
    sf::IntRect water_status_0{ 0,0,139,237 };
    sf::IntRect water_status_10{ 139,0,139,237 };
    sf::IntRect water_status_20{ 278,0,139,237 };
    sf::IntRect water_status_30{ 417,0,139,237 };
    sf::IntRect water_status_40{ 556,0,139,237 };
    sf::IntRect water_status_50{ 695,0,139,237 };
    sf::IntRect water_status_60{ 834,0,139,237 };
    sf::IntRect water_status_70{ 973,0,139,237 };
    sf::IntRect water_status_80{ 1112,0,139,237 };
    sf::IntRect water_status_90{ 1251,0,139,237 };
    sf::IntRect water_status_100{ 1390,0,139,237 };
    sf::IntRect Water_Status[11]{ water_status_0, water_status_10 ,water_status_20 ,water_status_30 ,water_status_40 ,water_status_50 ,water_status_60 ,water_status_70 ,water_status_80 ,water_status_90 ,water_status_100 };
    int water_sprite_index = 0;

public: // Pet
    
    sf::IntRect pet_rect{ 0,0,130,128 };
    
    // Idle Animation
    float animation_time_array_idle[3] = { 0.3f, 0.6f, 0.9f };
    sf::IntRect pet_idle_1{ 0,0,130,128 };
    sf::IntRect pet_idle_2{ 130,0,130,128 };
    sf::IntRect pet_idle_3{ 260,0,130,128 };
    sf::IntRect Pet_Idle[3] = { pet_idle_1 , pet_idle_2, pet_idle_3 };

    // Need Animation
    float animation_time_array_need[6] = { 0.3f, 0.6f, 0.9f, 1.2f, 1.5f, 1.6f };
    sf::IntRect pet_need_1{ 390,0,130,128 };
    sf::IntRect pet_need_2{ 520,0,130,128 };
    sf::IntRect pet_need_3{ 650,0,130,128 };
    sf::IntRect pet_need_4{ 780,0,130,128 };
    sf::IntRect pet_need_5{ 910,0,130,128 };
    sf::IntRect Pet_Need[5] = { pet_need_1 , pet_need_2, pet_need_3, pet_need_4, pet_need_5 };
    int pet_state_index = 0;
    enum pet_state
    {
        IDLE = 0,
        NEED
    };
    int pet_state_animation(float Hunger, float Thirst);
};

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
    std::string cause_of_death = "error";

    // Living
    float Age = 0.0;
    float age_track = 0.0;
    sf::Font font;
    sf::Text age_text;
    void display_age(float age);
    bool ALIVE = true;
    bool AWAKE = true;

    // Health
    float Health = 100.0;
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
    float Hunger = 50.0;
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
    float Add_Water = 20.0;
    float Water_Bowl = 0.0;
    float Water_Last_Change = 0.0;
    float Water_Change = 0.0;
    //float Water_Diffrence;
    float water_current = 0.0f;
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
    float dish_filler[6] = { 30,60,20,40,50,50 };
    // Rework Food Items.

    float dish_min = 0.0f;
    float dish_max = 100.0f;
    float dish_current = 100.0f;

    const char* food_empty = { "has no food!" };

    void addAge();
    int health_tracker();

    void Digester();
    void StarvManager();

    void Hydrater();
    void Drinker();
    void H2OProcessor();
    void DehyManager();
    //bool pet_death(bool& show, std::string cause_of_death);

    void Eater();

    int dish_fill(int dish_fill, int digestion_time);

public:
    void Update();
public:

};


