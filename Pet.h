#pragma once

class GUI
{
public: // Textures & Sprites
    static const int texture_count = 8;
    sf::Texture habitat, pet, water, food, food_button, water_button, close_button, life;
    sf::Texture TEXTURES[texture_count] = { habitat, pet, water, food, food_button, water_button, close_button, life };
    sf::Texture* pTEX = TEXTURES;

    sf::Sprite hab_spr, pet_spr, water_spr, food_spr, food_button_spr, water_button_spr, close_button_spr, life_spr;
    sf::Sprite SPRITES[texture_count] = { hab_spr, pet_spr, water_spr, food_spr, food_button_spr, water_button_spr, close_button_spr, life_spr };

    //sf::Sprite sprite_loader(sf::Sprite spr, sf::Texture* tex);
    //sf::Texture* texture_loader(sf::Texture* tex, const char* texture_files);

    const char* habitat_texture_file = "sprites\\Habitat.jpg";
    const char* pet_texture_file = "sprites\\pet_red.png";
    const char* water_texture_file = "sprites\\water.png";
    const char* food_texture_file = "sprites\\food.png";
    const char* food_tf = "sprites\\food_temp.png";
    const char* water_tf = "sprites\\water_temp.png";
    const char* close_button_tf = "sprites\\close_button.png";
    const char* life_tf = "sprites\\life_sheet.png";
    const char* texture_files[texture_count] = 
    { habitat_texture_file, pet_texture_file, water_texture_file, food_texture_file, food_tf, water_tf, close_button_tf, life_tf };


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
    sf::Vector2f water_bowl_xy = { 450,4 };
    sf::Vector2f food_xy = { 75, 264 };
    sf::Vector2f foodb_xy = { 75, 264 };
    sf::Vector2f waterb_xy = { 250, 4 };
    sf::Vector2f close_button_xy = { 0,0 };
    sf::Vector2f life_xy = { 50,0 };
    sf::Vector2f SPRITES_xy[texture_count] = {habitat_xy, pet_xy, water_bowl_xy, food_xy, foodb_xy, waterb_xy, close_button_xy, life_xy };

    bool sprites_inital_load = false;
};

class Animator : public GUI
{
public: // Mouse & GUI Button Interaction Regions
    sf::IntRect exit_application{ 0, 0, 50,50 };

public: // Default size of sprite rects - four coordinates x1y1x2y2
    sf::IntRect habitat_default_rect = { 0,0,1280, 720 };
    sf::IntRect pet_default_rect = { 0,0,130,128 };
    sf::IntRect water_bowl_default_rect{ 1390,0,139,237 };
    sf::IntRect food_default_rect{ 0,0,137,136 };
    sf::IntRect food_tmp_rect{ 0,0, 300, 300 };
    sf::IntRect water_tmp_rect{ 0,0, 300, 300 };
    sf::IntRect exit_idle_rect{ 0,0, 50, 50 };
    sf::IntRect exit_active_rect{ 50, 0, 50, 50 };
    sf::IntRect exit_state[2]{ exit_idle_rect ,exit_active_rect }; // Rework this I don't think its needed
    int exit_index = 0;
    sf::IntRect life_max_rect{ 0, 0, 300, 100 };
    sf::IntRect life_half_rect{ 0, 0, 200, 100 };
    sf::IntRect life_min_rect{ 0, 0, 100, 100 };
    sf::IntRect life_state[3]{ life_max_rect ,life_half_rect, life_min_rect };
    int life_index = 0;
    sf::IntRect Default_Sprite_Rects[texture_count] = { habitat_default_rect, pet_default_rect, water_bowl_default_rect, food_default_rect, food_tmp_rect, water_tmp_rect, exit_idle_rect };

public: // Food
    int x1 = 0, y1 = 0, x2 = 137, y2 = 136;
    //sf::IntRect food_default_rect{ x1, y1, 137, 136 };
    int gui_Food(float Dish);
    int food_increment = 137;
    sf::IntRect food_100{ 0,0,137,136 };
    sf::IntRect food_80{ 137,0,137,136 };
    sf::IntRect food_60{ 411,0,137,136 };
    sf::IntRect food_40{ 548,0,137,136 };
    sf::IntRect food_20{ 685,0,137,136 };
    sf::IntRect food_0{ 822,0,137,136 };
    sf::IntRect FOOD[6] = { food_100, food_80 ,food_60 ,food_40 ,food_20,food_0 };
    int food_sprite_index = 0;

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
    //bool isAdd_Water_clicked(sf::Sprite* addwater, sf::RenderWindow *render);

public: // Pet
    sf::IntRect pet_rect{ 0,0,130,128 };
    //sf::IntRect gui_Pet(float Hunger,float Thirst, sf::IntRect pet_state); // Delte

    sf::IntRect pet_idle_1{ 0,0,130,128 };
    sf::IntRect pet_idle_2{ 130,0,130,128 };
    sf::IntRect pet_idle_3{ 260,0,130,128 };
    sf::IntRect Pet_Idle[3] = { pet_idle_1 , pet_idle_2, pet_idle_3 };

    sf::IntRect pet_need_1{ 390,0,130,128 };
    sf::IntRect pet_need_2{ 520,0,130,128 };
    sf::IntRect pet_need_3{ 650,0,130,128 };
    sf::IntRect pet_need_4{ 780,0,130,128 };
    sf::IntRect pet_need_5{ 910,0,130,128 };
    sf::IntRect Pet_Need[5] = { pet_need_1 , pet_need_2, pet_need_3, pet_need_4, pet_need_5 };
    std::vector<sf::IntRect> ANIMATOR{ Pet_Idle[2],  Pet_Need[4] };
    sf::IntRect pet_state_animation(float Hunger, float Thirst);
    // Idle Animation
    float animation_time_array_idle[4] = { 0.3f, 0.9f, 1.2f, 1.3f };
    // Need Animation
    float animation_time_array_need[6] = { 0.3f, 0.6f, 0.9f, 1.2f, 1.5f, 1.6f };
};



//class Stats
//{
//public:
//    int currency_value = 1;
//    int bank = 10;
//};

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
    std::string cause_of_death = "error";

    // Living
    float Age = 0.0;
    float age_track = 0.0;
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

    //bool food_list(bool& show);

public:
    void Update();
public:

};


