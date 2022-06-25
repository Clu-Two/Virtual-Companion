
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

#include "windows.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Pet.h"


int main(int argc, char** argv)
{
    GUI* gui = new GUI();
    Animator* animator = new Animator();
    Pet_Manager* Pet = new Pet_Manager();

    // Start SFML Window
    sf::RenderWindow main_window;
    main_window.create(sf::VideoMode(gui->window_x, gui->window_y), "Companion", sf::Style::Default); // sf::Style::None creates borderless window
    main_window.setVerticalSyncEnabled(true);
    main_window.resetGLStates();


    sf::Clock deltaClock, Clock, animation_state;
    sf::Color Transparent { 0,0,0,100 };
    sf::Event event;

    // Create and Load Sprites/Assets
    for (int i = 0; i < gui->texture_count; i++)
    {
        gui->texture_loader(gui->pTEX[i], gui->texture_files[i]);
        gui->sprite_loader(gui->SPRITES[i], gui->pTEX[i]);
    }

    // Event / Flags
    sf::Event main_window_open;
    // Main Window
    while (main_window.isOpen())
    {
        // Load & Set sprite positions
        // To display an image it must be, (1) Defined as a Texture, linked to a file. (2) Assigned to a Sprite. (3) Sprite Rects Defined. (4) Set coordinates to draw. (5) Draw the sprites.
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

        if (!Pet->font.loadFromFile("arial.ttf"))
        {
            std::cout << "Font Load Failed" << std::endl;
        }
        Pet->display_age(Pet->Age);
        main_window.draw(Pet->age_text);

        //// Gui Updating
        animator->food_sprite_index = animator->gui_Food(Pet->dish_current);
        animator->Default_Sprite_Rects[Animator::Sprite_Index::FOOD] = animator->food_states[animator->food_sprite_index];
        animator->Default_Sprite_Rects[Animator::Sprite_Index::FEED] = animator->feed_state[animator->feed_index];
        animator->water_sprite_index = animator->gui_Water(Pet->Water_Bowl);
        animator->Default_Sprite_Rects[Animator::Sprite_Index::WATER] = animator->Water_Status[animator->water_sprite_index];

        animator->Default_Sprite_Rects[Animator::Sprite_Index::EXIT] = animator->exit_state[animator->exit_index];
        animator->Default_Sprite_Rects[Animator::Sprite_Index::LIFE] = animator->life_state[animator->life_index];
        animator->Default_Sprite_Rects[Animator::Sprite_Index::PET] = animator->pet_rect;
        animator->life_index = Pet->health_tracker(); // Modular

        animator->pet_state_index = animator->pet_state_animation(Pet->Hunger, Pet->Thirst);


        bool lock_click = false;
        // Left Mouse Button Press Events
        while (main_window.pollEvent(event)) // this is broken, was working
        {
            // Title Bar Close Window Button
            if (event.type == sf::Event::Closed)
            {
                main_window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !lock_click)
            {
                lock_click = true;
                std::cout << lock_click << std::endl;
                if (animator->exit_application.contains(event.mouseButton.x, event.mouseButton.y))
                {
                    std::cout << "Exit Button Pressed" << std::endl;
                    animator->exit_index = 1;
                    break;
                }
                if (animator->water_click_box.contains(event.mouseButton.x, event.mouseButton.y))
                {
                    std::cout << "Add Water Button Pressed" << std::endl;
                    animator->water_rect = animator->click_water_rect;
                }
                if (animator->feed_cb.contains(event.mouseButton.x, event.mouseButton.y))
                {
                    std::cout << "Add Food Pressed" << std::endl;
                    animator->feed_index = 1;
                    break;
                }
            }
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    if (animator->exit_application.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        std::cout << "Exit Button Released" << std::endl;
                     
                        event.type = sf::Event::Closed;
                    }
                    if (animator->feed_cb.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        std::cout << "Add Food Released" << std::endl;
                        Pet->dish_fill(20, 30);
                    }
                    if (animator->water_click_box.contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        std::cout << "Add Water Button Released" << std::endl;
                        animator->water_rect = animator->water_rect_default;
                        Pet->Hydrater();
                        break;
                    }
                    lock_click = false;
                    animator->exit_index = 0;
                    animator->feed_index = 0;
                    std::cout << lock_click << std::endl;
                }
            
            switch (event.type)
            {
            case sf::Event::Closed:
                //delete pointers
                delete gui;
                delete animator;
                delete Pet;
                main_window.close();
                return 0;
                break;
            case sf::Event::KeyPressed:
                std::cout << "Key Pressed" << std::endl;
                break;
            default:
                break;
            }
        }

        // Timer
        if (Clock.getElapsedTime().asSeconds() >= 0.02500f)
        {

            Pet->Update();
            Clock.restart();
        }


        if (animator->pet_state_index == Animator::pet_state::IDLE)
        {
            for (int i = 0; i < 2; i++)
            {
                if (animation_state.getElapsedTime().asSeconds() >= animator->animation_time_array_idle[i])
                {
                    animator->pet_rect = animator->Pet_Idle[i];
                }
                if (animation_state.getElapsedTime().asSeconds() > animator->animation_time_array_idle[2])
                {
                    animation_state.restart();
                    std::cout << "Idle Restart" << std::endl;
                }

            }
        }

        if (animator->pet_state_index == Animator::pet_state::NEED)
        {
            for (int i = 0; i < 5; i++)
            {
                if (animation_state.getElapsedTime().asSeconds() >= animator->animation_time_array_need[i])
                {
                    animator->pet_rect = animator->Pet_Need[i];
                }
                if (animation_state.getElapsedTime().asSeconds() > animator->animation_time_array_need[5])
                {
                    animation_state.restart();
                    std::cout << "Need Restart" << std::endl;
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
    health_tracker();
}

int Animator::pet_state_animation(float Hunger, float Thirst)
{
    if (Hunger >= 50.0f && Thirst >= 50.0f)
    {
       
        pet_state_index = pet_state::NEED;
    }
    if (Hunger < 50.0f || Thirst < 50.0f)
    {
        pet_state_index = pet_state::IDLE;
    }
    return pet_state_index;
}

// gross, need to refactor
int Animator::gui_Food(float Dish)
{
    int index = 0;
    if (Dish <= 100.0f && Dish >= 75.0f) {index = 0;}
    if (Dish <= 75.0f && Dish >= 50.0f){index = 1; }
    if (Dish <= 50.0f && Dish >= 25.0f) { index = 2; }
    if (Dish <= 25.0f && Dish >= 0.0f) { index = 3; }
    if (Dish <= 0.0f || Dish == 0.0f) { index = 4; }

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
            //std::cout << dish_current << std::endl;
        }
        if (Stomach >= Stomach_Max)
        {
            // Pet Full Animation State // Eventually
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
            Digested -= 0.05f;

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
        if(water_space < Add_Water)
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

int Pet_Manager::health_tracker()
{
    int health_index = 0;
    if (Health > 65)
    {
        health_index = 0;
    }
    if (Health <= 65)
    {
        health_index = 1;
    }
    if (Health <= 33)
    {
        health_index = 2;
    }
    if (Health <= 0)
    {
        // Come up with something
    }

    return health_index;
}

//Age
void Pet_Manager::addAge()
{
    if (ALIVE == true)
    {
        age_track += 0.01;
        if (age_track >= 1.0)
        {
            Age += 1.0;
            age_track = 0.0;
        }
    }
}

void Pet_Manager::display_age(float age)
{
    age_text.setFont(font); // font is a sf::Font
    int iage = age;
    // set the string to display
    age_text.setString(std::to_string(iage));

    // set the character size
    age_text.setCharacterSize(30); // in pixels, not points!

    // set the color
    age_text.setFillColor(sf::Color::White);

    // set the text style
    age_text.setStyle(sf::Text::Bold);       
}

//bool Pet_Manager::pet_death(bool& show, std::string cause_of_death)
//{

//}

