
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "windows.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Pet.h"





int selected = 0;


int main(int argc, char** argv)
{
    std::unique_ptr<Pet_Manager[]> Pet(new Pet_Manager[4]);
    std::unique_ptr<animator[]> anim(new animator[4]);
    // Start SFML Window
    sf::RenderWindow main_window;
    main_window.create(sf::VideoMode(1280, 720), "Companion"/*, sf::Style::None*/); // Style None creates borderless window
    main_window.setVerticalSyncEnabled(true);

    main_window.resetGLStates();
 



    sf::Clock deltaClock, Clock, animation_state;

    sf::Color Transparent = { 0,0,0,100 };
    //sf::Texture idle, hungry, eating, starving, f, minushp, *currentTex1, *currentTex2, *currentTex3, *currentTex4, *selected_sprite;

    // Create and Load Sprites/Assets
    //sf::Texture habitat, pet, water, addWater, food;



    if (!anim[selected].habitat.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\Habitat.jpg")) { std::cout << "HABITAT Sprite Load Error!" << std::endl; }
    sf::Sprite hab(anim[selected].habitat);
    if (!anim[selected].pet.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\pet_red.png")) { std::cout << "PET Sprite Load Error!" << std::endl; }
    if (!anim[selected].water.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\water.png")) { std::cout << "WATER Sprite Load Error!" << std::endl; }
    if (!anim[selected].addWater.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\add_water.png")) { std::cout << "ADD WATER BUTTON Sprite Load Error!" << std::endl; };
    if (!anim[selected].food.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\food.png")) { std::cout << "FOOD Sprite Load Error!" << std::endl; };
    if (!anim[selected].shop.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\Shop.png")) { std::cout << "SHOP Sprite Load Error!" << std::endl; };
    sf::Sprite shopp(anim[selected].shop);
    if (!anim[selected].shop_button.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\Shop_Button.png")) { std::cout << "SHOP BUTTON Sprite Load Error!" << std::endl; };
    sf::Sprite shop_buttonp(anim[selected].shop_button);
    if (!anim[selected].food_item_highlight.loadFromFile("..\\..\\Virtual Companion\\assets\\sprites\\Food_Item_Highlight.png")) { std::cout << "SHOP ITEM HIGHLIGHT Sprite Load Error!" << std::endl; };
    sf::Sprite food_item_highlightp(anim[selected].food_item_highlight);
    //Old Assets
    //hungry.loadFromFile("..\\..\\Virtual Companion\\assets\\images\\hungry.png");
    //eating.loadFromFile("..\\..\\Virtual Companion\\assets\\images\\eating.png");
    //minushp.loadFromFile("..\\..\\Virtual Companion\\assets\\images\\starving.png");
    //f.loadFromFile("..\\..\\Virtual Companion\\assets\\images\\f.png");
    //idle.loadFromFile("..\\..\\Virtual Companion\\assets\\images\\idle.png");
    //starving.loadFromFile("..\\..\\Virtual Companion\\assets\\images\\minushp.png");
    //currentTex1 = &idle;
    //currentTex2 = &idle;
    //currentTex3 = &idle;
    //currentTex4 = &idle;

    static int selItem = 0;
    static const char* items[] = { "Pet 1","Pet 2", "Pet 3", "Pet 4" };

    static bool save_file = true;
    static bool save_sql = false;

    static bool x = false;

    Pet[0].pet_name = "Titus";
    Pet[1].pet_name = "Glycon";
    Pet[2].pet_name = "Brutas";
    Pet[3].pet_name = "Demetrius";

    //std::vector<sf::Texture*> SPRITE{ currentTex1, currentTex2, currentTex3, currentTex4 }; selected_sprite = SPRITE[0];
    std::vector <float> BARS{ Pet[0].Health, Pet[0].Hunger, Pet[0].Thirst };
    std::vector <const char*> LABELS{ "Health","Hunger","Thirst" };
    // Main Window



    while (main_window.isOpen())
    {
        sf::Event main_window_open;

        while (main_window.pollEvent(main_window_open))
        {
       

            if (main_window_open.type == sf::Event::Closed)
            {
                main_window.close();
            }
        }
     

        // Set Object Positions & Draw
        main_window.draw(hab);
        shop_buttonp.setTextureRect(anim[selected].shop_button_rect);
        shop_buttonp.setPosition(anim[selected].shop_button_pos_x, anim[selected].shop_button_pos_y);
        food_item_highlightp.setTextureRect(anim[selected].item_highlight_rect);
        main_window.draw(shop_buttonp);
        shopp.setPosition(0, 121);


        anim[selected].waterp.setPosition(1082, 8);
        anim[selected].addwaterp.setPosition(1197, 8);
        anim[selected].foodp.setPosition(287, 504);
        anim[selected].pet_sprite.setPosition(585, 528);

        // Gui Updating
        anim[selected].food_s = anim[selected].gui_Food(Pet[selected].dish_current, anim[selected].food_s);
        anim[selected].foodp.setTextureRect(anim[selected].food_s);
        main_window.draw(anim[selected].foodp);

        anim[selected].pet_sprite.setTextureRect(anim[selected].pet_rect);
        main_window.draw(anim[selected].pet_sprite);

        anim[selected].water_s = anim[selected].gui_Water(Pet[selected].Water_Bowl, anim[selected].water_s, anim[selected].water_x1_current);
        anim[selected].waterp.setTextureRect(anim[selected].water_s);
        main_window.draw(anim[selected].waterp);

        anim[selected].add_water_rect = anim[selected].add_water_rect;
        anim[selected].addwaterp.setTextureRect(anim[selected].add_water_rect);
        main_window.draw(anim[selected].addwaterp);




        sf::Event left_mouse_pressed;

        /*if (anim[selected].shop_button_click_box.contains(sf::Mouse::getPosition(main_window).x, sf::Mouse::getPosition(main_window).y))
        {
            std::cout << "Shop HOVER" << std::endl;
        }*/
        int shop_state = 0;
        if (main_window.pollEvent(left_mouse_pressed))
        {
            if (left_mouse_pressed.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!anim[selected].shop_open && anim[selected].shop_button_click_box.contains(left_mouse_pressed.mouseButton.x, left_mouse_pressed.mouseButton.y))
                {
                    shop_state = 2;
                }
                else if (anim[selected].shop_open && anim[selected].shop_button_click_box.contains(left_mouse_pressed.mouseButton.x, left_mouse_pressed.mouseButton.y))
                {
                    shop_state = 1;
                }
                if (anim[selected].add_water_click_box.contains(left_mouse_pressed.mouseButton.x, left_mouse_pressed.mouseButton.y))
                {
                    std::cout << "Add Water Button Pressed" << std::endl;
                    anim[selected].add_water_rect = anim[selected].click_add_water_rect;
                    Pet[selected].Hydrater();
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    std::cout << "Mouse L Pressed" << std::endl;
                }
                if (left_mouse_pressed.type == sf::Event::MouseButtonReleased)
                {
                    std::cout << "Mouse L Released" << std::endl;
                    anim[selected].add_water_rect = anim[selected].add_water_rect_default;
                }
            }

            switch (left_mouse_pressed.MouseButtonPressed)
            {
            case 1:
                anim[selected].shop_open = false;
                std::cout << "Shop CLOSED" << std::endl;
                break;
            case 2:
                std::cout << "Shop OPENED" << std::endl;
                anim[selected].shop_open = true;
                main_window.draw(shopp);

                break;
            }

        }

        /*      case 1:
                  std::cout << "Pizza Selected" << std::endl;
                  anim[selected].food_item_highlightp.setPosition(anim[selected].shop_item_highlight_x, anim[selected].pizza_highlight_y);
                  main_window.draw(anim[selected].food_item_highlightp);
                  break;
              case 2:
                  std::cout << "Mango Selected" << std::endl;
                  anim[selected].food_item_highlightp.setPosition(anim[selected].shop_item_highlight_x, anim[selected].mango_highlight_y);
                  main_window.draw(anim[selected].food_item_highlightp);
                  break;
        */

// Timer
        if (Clock.getElapsedTime().asSeconds() >= 0.005f)
        {
            for (int i = 0; i < 4; i++)
            {
                Pet[i].Update();
                //FOOD[i].food_updater();
            }
            Clock.restart();
        }

        // Idle Animation
        float animation_time_array_idle[4] = { 0.3f, 0.9f, 1.2f, 1.3f };

        if (Pet[selected].Hunger < 60.0f || Pet[selected].Thirst < 60.0f)
        {
            for (int i = 0; i < 3; i++)
            {
                if (animation_state.getElapsedTime().asSeconds() >= animation_time_array_idle[i])
                {
                    anim[selected].pet_rect = anim[selected].Pet_Idle[i];
                }
                if (animation_state.getElapsedTime().asSeconds() >= animation_time_array_idle[3])
                {
                    animation_state.restart();
                }
            }
            //if (animation_state.getElapsedTime().asSeconds() >= 0.3f)
            //{
            //        anim[selected].pet_rect = anim[selected].Pet_Idle[0];
            //}
            //if (animation_state.getElapsedTime().asSeconds() >= 0.9f)
            //{
            //    anim[selected].pet_rect = anim[selected].Pet_Idle[1];
            //}
            //if (animation_state.getElapsedTime().asSeconds() >= 1.2f)
            //{
            //    anim[selected].pet_rect = anim[selected].Pet_Idle[2];
            //}
            //if (animation_state.getElapsedTime().asSeconds() >= 1.3f)
            //{
            //    animation_state.restart();
            //}
        }

        // Need Animation
        float animation_time_array_need[6] = { 0.3f, 0.6f, 0.9f, 1.2f, 1.5f, 1.6f };

        if (Pet[selected].Hunger > 60.0f || Pet[selected].Thirst > 60.0f)
        {
            for (int i = 0; i < 6; i++)
            {

                if (animation_state.getElapsedTime().asSeconds() >= animation_time_array_need[i])
                {
                    anim[selected].pet_rect = anim[selected].Pet_Need[i];
                }
                if (animation_state.getElapsedTime().asSeconds() >= animation_time_array_need[5])
                {
                    animation_state.restart();
                }
            }

            /*if (animation_state.getElapsedTime().asSeconds() >= 0.3f)
            {
                anim[selected].pet_rect = anim[selected].Pet_Need[0];
            }
            if (animation_state.getElapsedTime().asSeconds() >= 0.6f)
            {
                anim[selected].pet_rect = anim[selected].Pet_Need[1];
            }
            if (animation_state.getElapsedTime().asSeconds() >= 0.9f)
            {
                anim[selected].pet_rect = anim[selected].Pet_Need[2];
            }
            if (animation_state.getElapsedTime().asSeconds() >= 1.2f)
            {
                anim[selected].pet_rect = anim[selected].Pet_Need[3];
            }
            if (animation_state.getElapsedTime().asSeconds() >= 1.5f)
            {
                anim[selected].pet_rect = anim[selected].Pet_Need[4];
            }
            if (animation_state.getElapsedTime().asSeconds() >= 1.6f)
            {
                animation_state.restart();
            }*/
        }

        deltaClock.restart();

        //main_window.clear();

        main_window.display();
    }

    //selected_pet.release();

    return 0;

}


void Pet_Manager::Update()
{
    addAge();
    Digester();
    StarvManager();
    Drinker();
    H2OProcessor();
    DehyManager();
    Eater();
}

void animator::animation(sf::Texture* texture, sf::Vector2u imageCount, float timer)
{
    this->imageCount = imageCount; this->timer = timer;
    totalTime = 0.0f;
    currentImage.x = 0;
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);

}

//animator::~animator()
//{
//}


sf::IntRect animator::state_animation(sf::IntRect state, float Hunger, float Thirst)
{
    if (Hunger < 50 || Thirst < 50)
    {
        for (int i = 0; i < 5; i++) // bad remove
        {
            pet_rect = Pet_Need[i];
        }
    }
    if (Hunger > 70 && Thirst > 70)
    {
        for (int i = 0; i < 3; i++)
        {
            pet_rect = Pet_Idle[i];
        }
    }
    return pet_rect;
}


// gross, need to refactor
sf::IntRect animator::gui_Food(float Dish, sf::IntRect food_s)
{
    if (Dish <= 100.0f && Dish >= 90.0f)
    {
        food_s = food_100;
    }
    if (Dish <= 90.0f && Dish >= 80.0f)
    {
        food_s = food_90;
    }
    if (Dish <= 80.0f && Dish >= 60.0f)
    {
        food_s = food_80;
    }
    if (Dish <= 60.0f && Dish >= 40.0f)
    {
        food_s = food_60;
    }
    if (Dish <= 40.0f && Dish >= 20.0f)
    {
        food_s = food_40;
    }
    if (Dish <= 20.0f && Dish >= 0.0f)
    {
        food_s = food_20;
    }
    if (Dish <= 0.0f || Dish == 0.0f)
    {
        food_s = food_0;
    }

    return food_s;
}

sf::IntRect animator::gui_Water(float Water_Bowl, sf::IntRect water_s, int water_x1_current)
{
    if (Water_Bowl <= 100.0f && Water_Bowl >= 90.0f)
    {
        water_x1_current - water_x1_increment;
        water_s = water_status_100;
    }
    if (Water_Bowl <= 90.0f && Water_Bowl >= 80.0f)
    {
        water_s = water_status_90;
    }
    if (Water_Bowl <= 80.0f && Water_Bowl >= 60.0f)
    {
        water_s = water_status_80;
    }
    if (Water_Bowl <= 60.0f && Water_Bowl >= 40.0f)
    {
        water_s = water_status_60;
    }
    if (Water_Bowl <= 40.0f && Water_Bowl >= 20.0f)
    {
        water_s = water_status_40;
    }
    if (Water_Bowl <= 20.0f && Water_Bowl >= 0.0f)
    {
        water_s = water_status_20;
    }
    if (Water_Bowl <= 0.0f || Water_Bowl == 0.0f)
    {
        water_s = water_status_0;
    }
    return water_s;
}

//sf::Sprite Pet_Manager::gui_Health(float Health, sf::Sprite c_Health)
//{
//    if (Health <= 100 && Health >= 65)
//    {
//        c_Health = 
//    }
//    
//    
//    return sf::Sprite();
//}


int Pet_Manager::dish_fill(int dish_fill, int digestion_time)
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


 //If Plate has Food - Eat and fill Stomach
void Pet_Manager::Eater() // 
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


// If has consumed food, digest food
void Pet_Manager::Digester()
{
    if (ALIVE == true) //Alive Check
    {
        if (Stomach > Stomach_Min && Digested < Digested_Max) // If ingested calories > 0 some not good here
        {
            Stomach -= 0.01f;
            Digested += 0.01f;
            if (Stomach < Stomach_Min)
            {
                Stomach = Stomach_Min;
            }
            if (Hunger > Def_Hunger) // Reduce Hunger and Starvation when Digesting
            {
                if (Hunger <= 0.0)
                {
                    Hunger = 0.0;
                }
                else Hunger -= 0.05f;
            }
        }
        if (Digested > Digested_Min)
        {
            Digested -= 0.005f;

            if (Digested < Digested_Min)
            {
                Digested = Digested_Min;
            }
            if (Health != Max_Health && Health < Max_Health)
            {
                Health += 0.005f;
            }
            if (Starv > Def_Starv && Digested > Digested_Min)
            {
                Starv -= 0.05f;
            }
        }
        if (Digested <= Digested_Min)
        {
            Hunger += 0.025f;
        }
    }

}

void Pet_Manager::StarvManager() // Starv Manager
{
    if (ALIVE == true)
    {
        if (Health <= Min_Health)
        {
            ALIVE = false;
            std::cout << "Starvation Death" << std::endl;
        }
        //Hunger & Starv Cap 
        if (Hunger >= Max_Hunger)
        {
            Hunger = Max_Hunger;
            Starv += 0.1f;
        }
        if (Starv >= Max_Starv)
        {
            //Starv = Max_Starv;
            Health -= 0.0025f;
        }
    }
    if (!ALIVE)
    {
        //pet_death(ALIVE, starv_death);
    }
}

// Fill Water Bowl with Button Press
void Pet_Manager::Hydrater()
{
    if (ALIVE == true)
    {
        float water_space = Max_Water_Bowl - Water_Bowl;
        if (water_space >= Add_Water) // Add Water to Bowl if not Full
        {
            Water_Bowl += Add_Water;
        }
        else // Bowl Full inform user
        {
            std::cout << "Water Bowl Full" << std::endl;
        }
    }
}

// Drink Water if Thirsty and Water available
void Pet_Manager::Drinker()
{
    if (ALIVE == true)
    {
        int water_stomach_space = Water_Stomach_Max - Water_Stomach;
        if (water_stomach_space >= Water_Stomach && Water_Bowl > Min_Water_Bowl && Thirst > 20.0f && Water_Stomach < Water_Stomach_Max)
        {
            if (Thirst > 30.0f)
            {
                Water_Bowl -= 0.03f;
                Water_Stomach += 0.03f;
            }
            if (Thirst > 60.0f)
            {
                Water_Bowl -= 0.04f;
                Water_Stomach += 0.04f;;
            }
            if (Thirst > 90.0f)
            {
                Water_Bowl -= 0.04f;;
                Water_Stomach += 0.04f;
            }
            Water_Bowl -= 0.02f;
            Water_Stomach += 0.02f;
        }
        else if (Water_Stomach >= Water_Stomach_Max && Water_Bowl > Min_Water_Bowl)
        {
            std::cout << "Companion cannot drink any more" << std::endl;
        }
    }
}

// If has consumed water, reduced consumed water
void Pet_Manager::H2OProcessor()
{
    if (ALIVE == true)
    {
        if (Water_Stomach > Water_Stomach_Min && Processed < Processed_Max)
        {
            Water_Stomach -= 0.01f;
            Processed += 0.01f;
            if (Water_Stomach < Water_Stomach_Min)
            {
                Water_Stomach = Water_Stomach_Min;
            }
            if (Thirst > Def_Thirst)
            {
                if (Thirst <= Def_Thirst)
                {
                    Thirst = Def_Thirst;
                }
                else Thirst -= 0.07f;
            }
        }
        if (Processed > Processed_Min)
        {
            Processed -= 0.005f;

            if (Processed < Processed_Min)
            {
                Processed = Processed_Min;
            }
            if (Health < Max_Health)
            {
                Health += 0.1f;
            }
            if (Dehy > Dehy_Min && Processed > Processed_Min)
            {
                Dehy -= 0.6f;
            }
        }
        if (Processed <= Processed_Min)
        {
            Thirst += 0.35f;
        }
    }
    else
    {
        ALIVE = false;
    }
}

// If Thirst is Max increase Dehydration, if Dehydration is Max reduce health
void Pet_Manager::DehyManager()
{
    if (ALIVE == true)
    {
        // Thirstcheck if alive
        if (Health <= Min_Health)
        {
            ALIVE = false;
            std::cout << "Dehyation Death" << std::endl;
        }
        //Thirst & Dehy Cap 
        if (Thirst >= Max_Thirst)
        {
            Thirst = Max_Thirst;
            Dehy += 0.3f;
        }
        if (Dehy >= Dehy_Max)
        {
            Dehy = Dehy_Max;
            Health -= 0.025f;
        }
    }
    if (!ALIVE)
    {
        //pet_death(ALIVE, thirst_death);
    }
}

//Age
void Pet_Manager::addAge()
{
    if (ALIVE == true)
    {
        age_track += 0.0001;
        if (age_track >= 1.0)
        {
            Age += 1.0;
            age_track = 0.0;
        }
    }
}

//bool Pet_Manager::pet_death(bool& show, std::string cause_of_death) // add remove text after a few seconds
//{

//}


