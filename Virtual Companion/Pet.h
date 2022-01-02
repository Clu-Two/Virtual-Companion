#pragma once

class animator
{
public:
    int x1 = 0, y1 = 0, x2 = 137, y2 = 136;
    sf::IntRect food_s{ x1, y1, 137, 136 };
    void animation(sf::Texture* texture, sf::Vector2u imageCount, float timer);
    //~animator();

    // Pet
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

    sf::IntRect water_rect{ 1390,0,139,237 };

    sf::IntRect shop_button_rect{ 0,0, 211,75 };

    //sf::RectangleShape shop_button_rect; 
    int shop_button_pos_x = 7, shop_button_pos_y = 128, shop_button_pos_w = 211, shop_button_pos_h = 75;
    int shop_button_click_box_x2 = shop_button_pos_x + shop_button_pos_w;
    int shop_button_click_box_y2 = shop_button_pos_y + shop_button_pos_h;
    sf::IntRect shop_button_click_box{ shop_button_pos_x, shop_button_pos_y, shop_button_click_box_x2, shop_button_click_box_y2 };
    bool shop_open = false;
    sf::IntRect item_highlight_rect{ 0,0,173,61 };
    sf::IntRect pizza_click_box{ 23, 216,196,277 };
    sf::IntRect steak_click_box{ 23, 0,0,0 };
    sf::IntRect peas_click_box{ 23, 0,0,0 };
    sf::IntRect carrot_click_box{ 23, 0,0,0 };
    sf::IntRect kiwi_click_box{ 23, 0,0,0 };
    sf::IntRect mango_click_box{ 23,587,196, 648 };
    bool mango = false;
    int shop_item_highlight_x = 23, pizza_highlight_y = 216, mango_highlight_y = 587;

    // void open_shop( bool open); // Shop Open Slide Animation

    sf::IntRect add_water_click_box{ 1197,8, 1259,110 };
    sf::IntRect add_water_rect_default{ 0,0,62,102 };
    sf::IntRect add_water_rect{ 0,0,62,102 };
    sf::IntRect click_add_water_rect{ 62,0,62,102 };
    sf::IntRect Add_Water[2]{ add_water_rect ,click_add_water_rect };
    //bool isAdd_Water_clicked(sf::Sprite* addwater, sf::RenderWindow *render);
    //sf::IntRect pet_consume_1{ 1040,0,130,128 };
    //sf::IntRect pet_consume_2{ 1170,0,130,128 };
    //sf::IntRect pet_consume_3{ 1300,0,130,128 };
    //sf::IntRect pet_consume_4{ 1430,0,130,128 };
    //sf::IntRect pet_consume_5{ 1560,0,130,128 };
    //sf::IntRect pet_consume_6{ 1690,0,130,128 };
    //sf::IntRect pet_consume_7{ 1820,0,130,128 };
    //sf::IntRect pet_consume_8{ 1950,0,130,128 };

    //sf::IntRect Pet_Consumep[8] = {pet_consume_1}
    std::vector<sf::IntRect> ANIMATOR{ Pet_Idle[2],  Pet_Need[4] };
    sf::IntRect state_animation(sf::IntRect state, float Hunger, float Thirst);

    // Food
    sf::IntRect gui_Food(float Dish, sf::IntRect food_s);
    sf::IntRect food_100{ 0,0,137,136 };
    sf::IntRect food_90{ 0,0,137,136 };
    sf::IntRect food_80{ 137,0,137,136 };
    sf::IntRect food_60{ 411,0,137,136 };
    sf::IntRect food_40{ 548,0,137,136 };
    sf::IntRect food_20{ 685,0,137,136 };
    sf::IntRect food_0{ 822,0,137,136 };

    // Water
    int water_x1_min = 0;
    int water_x1_increment = 139;
    int water_x1_max = 1390;
    int water_x1_current = 1390;
    sf::IntRect water_s{ water_x1_current,0,139,237 };
    sf::IntRect gui_Water(float Water_Bowl, sf::IntRect water_s, int water_x1_current);
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

    sf::Texture habitat, pet, water, addWater, food, pet_tex, shop, shop_button, food_item_highlight;
    sf::Sprite foodp{ food }, pet_sprite{ pet }, waterp{ water }, addwaterp{ addWater }, food_item_highlightp{ food_item_highlight };
    //sf::Sprite gui_Health(float Health, sf::Sprite c_Health);
    sf::IntRect uvRect;
private:
    sf::Vector2u imageCount, currentImage;
    float timer, totalTime;
};


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
    float Add_Water = 10.0;
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


    enum class DB_Type
    {
        FILE,
        SQLITE
    };

    float dish_min = 0.0f;
    float dish_max = 100.0f;
    float dish_current = 100.0f;

    const char* food_empty = { "has no food!" };

    void addAge();

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






