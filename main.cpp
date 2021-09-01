
#include "imgui.h" // ImGui includes
#include "imgui-SFML.h" // SFML ImGui includes
#include "windows.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui_internal.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Pet.h"
#include "formatting.h"


//void ThirstStats(ImGuiStyle* trst = NULL);
//void HungerStats(ImGuiStyle* hngr = NULL);

Pet_Manager::DB_Type SaveFormat = Pet_Manager::DB_Type::FILE;

    ImGuiWindowFlags main_window_style = /*ImGuiWindowFlags_NoTitleBar*/ ImGuiWindowFlags_NoCollapse /*| ImGuiWindowFlags_NoSavedSettings*/ | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize;
    ImGuiWindowFlags secondary_window = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
    ImGuiWindowFlags notification_popup = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;

    int selected = 0;
    Pet_Manager pet1, pet2, pet3, pet4, *selected_pet;
    food_manager food1, food2, food3, food4, *selected_food;
    potato potato_obj;  

int main(int argc, char** argv)
{
    // Start SFML Window
    sf::RenderWindow main_window;
    main_window.create(sf::VideoMode(315, 568), "Companion", sf::Style::None);
    main_window.setVerticalSyncEnabled(true);

    main_window.resetGLStates();
    ImGui::SFML::Init(main_window, false);

    loadfonts();

    sf::Clock deltaClock, Clock;

    sf::Color Transparent = { 0,0,0,100 };
    sf::Texture idle, hungry, eating, starving, f;
    sf::Texture* currentTex = NULL;
 
    hungry.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\hungry.png");
    eating.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\eating.png");
    starving.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\starving.png");
    f.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\f.png");
    idle.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\idle.png");
    currentTex = &idle;

    static int selItem = 0;
    static const char* items[] = { "Pet 1","Pet 2", "Pet 3", "Pet 4" };
   
    static bool save_file = true;
    static bool save_sql = false;

    static bool x = false;

    pet1.pet_name = "Titus";
    pet2.pet_name = "Jor El";
    pet3.pet_name = "Zoidberg";
    pet4.pet_name = "Mr. Bigglesworth";

    std::vector <Pet_Manager> PET{ pet1, pet2, pet3, pet4 }; selected_pet = &PET[0];
    std::vector<food_manager> FOOD{ food1, food2, food3, food4 }; selected_food = &FOOD[0];

    // Main Loop
    while (main_window.isOpen())
    {
        sf::Event event;
        while (main_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                main_window.close();
            }
        }
       
        ImGui::SFML::Update(main_window, deltaClock.restart());

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        // SFML-IMGUI Window Menu
  
        ImGui::PopFont();

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(315, 568));
        if (ImGui::Begin("Virtual Companion", NULL, main_window_style)) // begin window
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::BeginMenu("Save Format"))
                    {
                        if (ImGui::MenuItem("File/Txt", NULL, &save_file))
                        {
                            save_sql = !save_sql;
                            SaveFormat = Pet_Manager::DB_Type::FILE;
                        }
                        if (ImGui::MenuItem("sql", NULL, &save_sql))
                        {
                            save_file = !save_file;
                            SaveFormat = Pet_Manager::DB_Type::SQLITE;
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Save"))
                    {
                        if (ImGui::MenuItem("Save"))
                        {
                            selected_pet->Save_DB(items[selItem], SaveFormat);
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Load"))
                    {
                        selected_pet->Load_DB(items[selItem], SaveFormat);
                    }
                    if (ImGui::MenuItem("Exit"))
                    {
                        main_window.close();
                    }
                ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Pets"))
                {
                        if (ImGui::MenuItem(PET[0].pet_name.c_str()))
                        {
                            selected = 0;
                            selected_pet = &PET[0];
                            selected_food = &FOOD[0];

                        }
                        if (ImGui::MenuItem(PET[1].pet_name.c_str()))
                        {
                            selected = 1;
                            selected_pet = &PET[1];
                            selected_food = &FOOD[1];
                        }
                        if (ImGui::MenuItem(PET[2].pet_name.c_str()))
                        {
                            selected = 2;
                            selected_pet = &PET[2];
                            selected_food = &FOOD[2];
                        }
                        if (ImGui::MenuItem(PET[3].pet_name.c_str()))
                        {
                            selected = 3;
                            selected_pet = &PET[3];
                            selected_food = &FOOD[3];
                        }
                    ImGui::EndMenu();
                }
               
            ImGui::EndMenuBar();
            }

            ImGui::Text(PET[selected].pet_name.c_str());
            ImGui::Text("Status: %s", (selected_pet->status.c_str()));
            //ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x * 20);
            //ImGui::SetNextItemWidth(100.0f);
            //if (ImGui::Combo("Pet", &selItem, items, IM_ARRAYSIZE(items)))
            //{
            //    selected_pet = &PET[selItem];
            //}

            // Age
            ImGui::Text("Age: %.1f", selected_pet->Age);
            if (selected_pet->ALIVE == false)
            {
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x * 10);
                if (ImGui::Button("Revive"))
                {
                }
            }
           
             // Health
            char health_buf[64];
            sprintf_s(health_buf, "%.1f/%.1f%%", (selected_pet->Health), selected_pet->Max_Health);
            selected_pet->Health <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive);
            ProgressBar_Alt((selected_pet->Health / selected_pet->Max_Health), ImVec2(250.0f, 0.0f), "Health", health_buf, selected_pet->Health);

            // Hunger
            char hunger_buf[64];
            sprintf_s(hunger_buf, "%.1f/%.1f%%", (selected_pet->Hunger), selected_pet->Max_Hunger);
            ProgressBar_Alt((selected_pet->Hunger / selected_pet->Max_Hunger), ImVec2(250.0f, 0.0f), "Hunger", hunger_buf, selected_pet->Hunger);

            // Thirst
            char thirst_buf[64];
            sprintf_s(thirst_buf, "%.1f/%.1f%%", (selected_pet->Thirst), selected_pet->Max_Thirst);
            ProgressBar_Alt((selected_pet->Thirst / selected_pet->Max_Thirst), ImVec2(250.0f, 0.0f), "Thirst", thirst_buf, selected_pet->Thirst);

            //// Food Bowl
            //char food_buf[64];
            //sprintf_s(food_buf, "%.1f/%.1f%%", (selected_pet.Plate), selected_pet.Max_Plate);
            //ImGui::ProgressBar3((selected_pet.Plate / selected_pet.Max_Plate), ImVec2(50.0f, 250.0f), food_buf);

            // New Food Dish
            char food_buf[64];
            sprintf_s(food_buf, "%.0f/%.0f%%", (selected_food->dish_current), selected_food->dish_max);
            ProgressBar_Vertical((selected_food->dish_current / selected_food->dish_max), ImVec2(50.0f, 250.0f), food_buf);

            ImGui::SameLine();

            // Water Dish
            char water_bowl_buf[64];
            sprintf_s(water_bowl_buf, "%.0f/%.0f%%", (selected_pet->Water_Bowl), selected_pet->Max_Water_Bowl);
            ProgressBar_Vertical((selected_pet->Water_Bowl / selected_pet->Max_Water_Bowl), ImVec2(50.0f, 250.0f), water_bowl_buf);
            
            if (selected_pet->ALIVE)
            {
                if (selected_pet->Hunger <= 10.0) 
                {
                    currentTex = &idle;
                }
                if (selected_pet->Thirst <= 10.0)
                {
                    currentTex = &idle;
                }
                if (selected_pet->Stomach == selected_pet->Stomach_Max)
                {
                    currentTex = &eating;
                }
                if (selected_pet->Hunger > 30.0 || selected_pet->Thirst > 25.0)
                {
                    currentTex = &hungry;
                }
                if (selected_pet->Starv > 0.0 || selected_pet->Dehy > 0.0)
                {
                    *currentTex = starving;
                }
            }
            if (!selected_pet->ALIVE)
            {
                *currentTex = f;
            }
            ImGui::SameLine();
            ImGui::Image(*currentTex, sf::Vector2f(150, 150));
            //ImGui::Text("IMAGE LOAD ERROR");

            if (selected_food->dish_current <= selected_food->dish_min) //?
            {
                ImGui::Text(selected_food->food_empty);
            }

            if (ImGui::Button("Food Menu"))
            {
                x = !x;
            }
            if (x)
            {
                selected_food->food_list(x);
            }
            ImGui::SameLine();
            if (ImGui::Button("Fill Water"))
            {
                selected_pet->Hydrater();
            }
}

        ImGui::PopFont();

        ImGui::End();

        // Timer
        if(Clock.getElapsedTime().asSeconds() >= 0.015f) 
        {
           for (int i = 0; i < 4; i++)
           {
               PET[i].Update();
               FOOD[i].food_updater();
           }
           Clock.restart();
        }

        deltaClock.restart();
 
        main_window.clear();

        ImGui::SFML::Render(main_window); // Call this to render the gui you defined in your update
        main_window.display();
    }

    ImGui::SFML::Shutdown(); // Call when you want to shutdown imgui

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
    //logDB_CMD();
}

void food_manager::food_updater()
{
   Eater();
}

bool food_manager::food_list(bool& show)
{
    static bool x = false;
    std::vector<food_data> {potato_obj};
    ImGui::Begin("Todays Menu", NULL, secondary_window);
    for (int i = 0; i < 6; i++)
    {


    }
    if (ImGui::Button(potato_obj.food_name))
    {
        if (dish_current < dish_max)
        {
            dish_fill(potato_obj.fill, potato_obj.digestion_time);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }
    if (ImGui::Button(potato_obj.food_name))
    {
        if (dish_current < dish_max)
        {
            dish_fill(potato_obj.fill, potato_obj.digestion_time);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }
    //ImGui::Text("%d", potato_obj.digestion_time);
    //ImGui::Text("%d", potato_obj.health_restore);
    //ImGui::Text("%d", potato_obj.hunger_reduction);
    //ImGui::Text("%d", potato_obj.dish_fill);
    //ImGui::Text("%d", potato_obj.food_name);
 /*   if (ImGui::Button("Pizza Slice"))
    {
        if (dish_current < dish_max)
        {
            dish_fill(food_menu_obj.pizza);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }
    if (ImGui::Button("Carrot"))
    {
        if (dish_current < dish_max)
        {
            dish_fill(food_menu_obj.carrot);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }
    if (ImGui::Button("Salad"))
    {
        if (dish_current < dish_max)
        {
            dish_fill(food_menu_obj.salad);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }
    if (ImGui::Button("Doughnut"))
    {
        if (dish_current < dish_max)
        {
            dish_fill(food_menu_obj.doughnut);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }
    if (ImGui::Button("Brownie"))
    {
        if (dish_current < dish_max)
        {
            dish_fill(food_menu_obj.brownie);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }*/
    if (x)
    {
        dish_full(x);
    }
    if (ImGui::Button("Close"))
    {
        show = !show;
    }
    ImGui::End();
    return !show;
}

int food_manager::dish_fill(int dish_fill, int digestion_time)
{
    selected_food->dish_current += dish_fill;
    digestion_time += digestion_time;
    return digestion_time;
}

bool food_manager::dish_full(bool& show)
{
    //ImGui::BeginChild("Uh Oh!");
    //ImGuiWindowFlags localflags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Dish Full", NULL, notification_popup);
    ImGui::Text(selected_pet->pet_name.c_str());
    ImGui::SameLine();
    ImGui::Text(selected_pet->dish_full_error.c_str());
    ImGui::SameLine();
    if (ImGui::Button("Ok"))
    {
        show = !show;
    }
    ImGui::End();
    //ImGui::EndChild();
    return !show;
}


// If Plate has Food - Eat and fill Stomach
void food_manager::Eater() // 
{
    if (selected_pet->ALIVE == true)
    {
        if (dish_current > dish_min && selected_pet->Hunger > selected_pet->Def_Hunger && selected_pet->Stomach < selected_pet->Stomach_Max)
        {
            dish_current -= 0.03f; // Reduce Food available to eat 3f max 0/3
            selected_pet->Stomach += 0.3f; // Increase Ingested Calories
        }
        if (selected_pet->Stomach >= selected_pet->Stomach_Max)
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
            Stomach -= 0.025f;
            Digested += 0.025f;
            if (Stomach < Stomach_Min)
            {
                Stomach = Stomach_Min;
            }
            if (Hunger > Def_Hunger) // Reduce Hunger and Starvation when Digesting
            {
                Hunger -= 0.02f;
                if (Hunger < Def_Hunger)
                {
                    Hunger = Def_Hunger;
                }
            }
        }
        if (Digested > Digested_Min)
        {
            Digested -= 0.01f;

            if (Digested < Digested_Min)
            {
                Digested = Digested_Min;
            }
            if (Health < Max_Health)
            {
                Health += 0.02f;
            }
            if (Starv > Def_Starv && Digested > Digested_Min)
            {
                Starv -= 0.04f;
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
            Starv += 0.01f;
        }
        if (Starv >= Max_Starv)
        {
            //Starv = Max_Starv;
            Health -= 0.0025f;
        }
    }
    if (!ALIVE)
    {
        pet_death(ALIVE, starv_death);
    }
}

// Fill Water Bowl with Button Press
void Pet_Manager::Hydrater()
{
    if (ALIVE == true)
    {
        if (Water_Bowl < Max_Water_Bowl) // Add Water to Bowl if not Full
        {
            Water_Bowl += 20.0f;
            if (Water_Bowl > Max_Water_Bowl)
            {
                Water_Bowl = Max_Water_Bowl;
            }
        }
        else // Bowl Full inform user
        {
            Water_Bowl = Max_Water_Bowl;
            std::cout << "Water Bowl Full" << std::endl;
        }
    }

}

// Drink Water if Thirsty and Water available
void Pet_Manager::Drinker()
{
    if (ALIVE == true)
    {
        if (Water_Bowl > Min_Water_Bowl)
        {
            if (Thirst > Def_Thirst && (AWAKE == true))
            {
                if (Water_Stomach < Water_Stomach_Max)
                {
                    Water_Bowl -= 0.10f;
                    Water_Stomach += 0.10f;
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
void Pet_Manager::H2OProcessor()
{
    if (ALIVE == true)
    {
        if (Water_Stomach > Water_Stomach_Min && Processed < Processed_Max)
        {
            Water_Stomach -= 0.10f;
            Processed += 0.10f;
            if (Water_Stomach < Water_Stomach_Min)
            {
                Water_Stomach = Water_Stomach_Min;
            }
            if (Thirst > Def_Thirst)
            {
                Thirst -= 0.10f;
                if (Thirst < Def_Thirst)
                {
                    Thirst = Def_Thirst;
                }
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
                Health += 0.10f;
            }
            if (Dehy > Dehy_Min && Processed > Processed_Min)
            {
                Dehy -= 0.06f;
            }
        }
        if (Processed <= Processed_Min)
        {
            Thirst += 0.07f;
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
            Dehy += 0.03f;
        }
        if (Dehy >= Dehy_Max)
        {
            Dehy = Dehy_Max;
            Health -= 0.025f;
        }
    }
    if (!ALIVE)
    {
        pet_death(ALIVE, thirst_death);
    }
}

//Age
void Pet_Manager::addAge()
{
    if (ALIVE == true)
    {
        Age += 0.01f;
    }
}

bool Pet_Manager::pet_death(bool& show, std::string cause_of_death) // add remove text after a few seconds
{
    ImGui::Begin("Report");
    ImGui::Text(pet_name.c_str());
    ImGui::SameLine(27.7f, NULL);
    ImGui::Text(cause_of_death.c_str());
    ImGui::End();
    return !show;
}


