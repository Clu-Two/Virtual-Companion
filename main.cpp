
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

/*
void GUI::texture_loader(sf::Texture& tex, const char* texture_files)
{
    tex->loadFromFile(texture_files);
    std::cout << texture_files << std::endl;
    return tex;
}


sf::Sprite GUI::sprite_loader(sf::Sprite spr, sf::Texture* tex)
{
    spr.setTexture(*tex); 
    std::cout << tex << std::endl;
    return spr;
}
*/

int main(int argc, char** argv)
{
    GUI* gui = new GUI();
    Animator* animator = new Animator();
    Pet_Manager* Pet = new Pet_Manager();

    // Start SFML Window
    sf::RenderWindow main_window;
    main_window.create(sf::VideoMode(1280, 720), "Companion", sf::Style::Default); // sf::Style::None creates borderless window
    main_window.setVerticalSyncEnabled(true);
    main_window.resetGLStates();


    sf::Clock deltaClock, Clock, animation_state;
    sf::Color Transparent { 0,0,0,100 };
 

    // Create and Load Sprites/Assets
    for (int i = 0; i < gui->texture_count; i++)
    {
        //*&gui->pTEX[i] = *gui->texture_loader(&gui->pTEX[i], gui->texture_files[i]);
        gui->texture_loader(gui->pTEX[i], gui->texture_files[i]);

       // gui->SPRITES[i] = gui->sprite_loader(gui->SPRITES[i], &gui->pTEX[i]);
        gui->sprite_loader(gui->SPRITES[i], gui->pTEX[i]);
    }
    
    // Main Window
    while (main_window.isOpen())
    {
        sf::Event main_window_open;
        while (main_window.pollEvent(main_window_open))
        {
            if (main_window_open.type == sf::Event::Closed)
            {
                //delete pointers
                delete gui;
                delete animator;
                delete Pet;
                main_window.close();

                return 0;
            }
        }


        // Load & Set sprite positions
        do {
            for (int i = 0; i < gui->texture_count; i++)
                {
                    if (i >= gui->texture_count - 1){gui->sprites_inital_load = true;}
                    gui->SPRITES[i].setTextureRect(animator->Default_Sprite_Rects[i]);
                    gui->SPRITES[i].setPosition(gui->SPRITES_xy[i]);
                    gui->SPRITES[i].setScale(1.0f, 1.0f);
                }
            } while (!gui->sprites_inital_load);

        // Draw Gui Assets
        for (int i = 0; i < gui->texture_count; i++){main_window.draw(gui->SPRITES[i]);}

        //shop_buttonp.setTextureRect(anim[selected].shop_button_rect);
        //shop_buttonp.setPosition(anim[selected].shop_button_pos_x, anim[selected].shop_button_pos_y);
        //food_item_highlightp.setTextureRect(anim[selected].item_highlight_rect);
        //main_window.draw(shop_buttonp);
        //shopp.setPosition(0, 121);

        //// Gui Updating
        animator->food_sprite_index = animator->gui_Food(Pet->dish_current);
        animator->Default_Sprite_Rects[4] = animator->FOOD[animator->food_sprite_index];

        animator->water_sprite_index = animator->gui_Water(Pet->Water_Bowl);
        animator->Default_Sprite_Rects[2] = animator->Water_Status[animator->water_sprite_index];

        //int pet_sprite_index = 0;
        animator->pet_rect = animator->pet_state_animation(Pet->Hunger, Pet->Thirst);

        sf::Event left_mouse_pressed;
        /*if (anim->shop_button_click_box.contains(sf::Mouse::getPosition(main_window).x, sf::Mouse::getPosition(main_window).y))
        {
            std::cout << "Shop HOVER" << std::endl;
        }*/
        int shop_state = 0;
        while (main_window.pollEvent(left_mouse_pressed)) // this is broken, was working
        {
            if (left_mouse_pressed.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!animator->shop_open && animator->shop_button_area.contains(left_mouse_pressed.mouseButton.x, left_mouse_pressed.mouseButton.y))
                {
                    *&animator->shop_state = animator->shop_opened_rect;
                    std::cout << "Shop OPENED" << std::endl;
                    animator->shop_open = true;
                }
                else if (animator->shop_open && animator->shop_button_area.contains(left_mouse_pressed.mouseButton.x, left_mouse_pressed.mouseButton.y))
                {
                    animator->shop_default_rect = { 7,7,211,75 };
                    std::cout << "Shop CLOSED" << std::endl;
                    animator->shop_open = false;
                }
                if (animator->add_water_click_box.contains(left_mouse_pressed.mouseButton.x, left_mouse_pressed.mouseButton.y))
                {
                    std::cout << "Add Water Button Pressed" << std::endl;
                    animator->add_water_rect = animator->click_add_water_rect;
                    Pet->Hydrater();
                }
                if (left_mouse_pressed.type == sf::Event::MouseButtonReleased)
                {
                    std::cout << "Mouse L Released" << std::endl;
                    animator->add_water_rect = animator->add_water_rect_default;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    std::cout << "Mouse L Pressed" << std::endl;
                }
            }

            //switch (left_mouse_pressed.MouseButtonPressed)
            //{
            //case 1:
            //    animator->shop_open = false;
            //    std::cout << "Shop CLOSED" << std::endl;
            //    break;
            //case 2:
            //    std::cout << "Shop OPENED" << std::endl;
            //    animator->shop_open = true;
            //    //main_window.draw(shopp);
            //    break;
            //default:
            //    break;
            //}

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

            Pet->Update();
            Clock.restart();
        }


        if (Pet->Hunger < 60.0f || Pet->Thirst < 60.0f)
        {
            for (int i = 0; i < 3; i++)
            {
                if (animation_state.getElapsedTime().asSeconds() >= animator->animation_time_array_idle[i])
                {
                    animator->pet_rect = animator->Pet_Idle[i];
                }
                if (animation_state.getElapsedTime().asSeconds() >= animator->animation_time_array_idle[3])
                {
                    animation_state.restart();
                }
            }
        }

        if (Pet->Hunger > 60.0f || Pet->Thirst > 60.0f)
        {
            for (int i = 0; i < 6; i++)
            {

                if (animation_state.getElapsedTime().asSeconds() >= animator->animation_time_array_need[i])
                {
                    animator->pet_rect = animator->Pet_Need[i];
                }
                if (animation_state.getElapsedTime().asSeconds() >= animator->animation_time_array_need[5])
                {
                    animation_state.restart();
                }
            }
        }

        deltaClock.restart();

        main_window.display();
    }

    //gui.release();
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


//void animator::animation(sf::Texture* texture, sf::Vector2u imageCount, float timer)
//{
//    this->imageCount = imageCount; this->timer = timer;
//    totalTime = 0.0f;
//    currentImage.x = 0;
//    uvRect.width = texture->getSize().x / float(imageCount.x);
//    uvRect.height = texture->getSize().y / float(imageCount.y);
//
//}

//animator::~animator()
//{
//}


sf::IntRect Animator::pet_state_animation(float Hunger, float Thirst)
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
int Animator::gui_Food(float Dish)
{
    int index = 0;
    if (Dish <= 100.0f && Dish >= 90.0f) {index = 0;}
    if (Dish <= 80.0f && Dish >= 60.0f){index = 1; }
    if (Dish <= 60.0f && Dish >= 40.0f) { index = 2; }
    if (Dish <= 40.0f && Dish >= 20.0f) { index = 3; }
    if (Dish <= 20.0f && Dish >= 0.0f) { index = 4; }
    if (Dish <= 0.0f || Dish == 0.0f) { index = 5; }

    return index;
}

int Animator::gui_Water(float Water_Bowl) 
{
    int index = 0;
    if (Water_Bowl <= 100.0f && Water_Bowl >= 90.0f){index = 10; }
    if (Water_Bowl <= 90.0f && Water_Bowl >= 80.0f) { index = 9; }
    if (Water_Bowl <= 80.0f && Water_Bowl >= 70.0f) { index = 8; }
    if (Water_Bowl <= 70.0f && Water_Bowl == 60.0f) { index = 7; }
    if (Water_Bowl <= 60.0f && Water_Bowl >= 50.0f) { index = 6; }
    if (Water_Bowl <= 50.0f && Water_Bowl == 40.0f) { index = 5; }
    if (Water_Bowl <= 40.0f && Water_Bowl >= 30.0f) { index = 4; }
    if (Water_Bowl <= 30.0f && Water_Bowl == 20.0f) { index = 3; }
    if (Water_Bowl <= 20.0f && Water_Bowl >= 10.0f) { index = 2; }
    if (Water_Bowl <= 10.0f && Water_Bowl == 5.0f) { index = 1; }
    if (Water_Bowl <= 0.0f || Water_Bowl == 0.0f) { index = 0; }

    return index;
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
    //If Full("Can't add any more food!");
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
        if (Water_Bowl + Add_Water >= Max_Water_Bowl)
        {
            Water_Bowl = Max_Water_Bowl;
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

//bool Pet_Manager::pet_death(bool& show, std::string cause_of_death)
//{

//}

