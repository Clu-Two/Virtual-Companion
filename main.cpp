
#include "imgui.h" // ImGui includes
#include "imgui-SFML.h" // SFML ImGui includes
#include "windows.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui_internal.h"

#include <fstream>
#include <iostream>

#include "Pet.h"
#include "food.h"
#include "formatting.h"



//void ThirstStats(ImGuiStyle* trst = NULL);
//void HungerStats(ImGuiStyle* hngr = NULL);

Pet_Manager::DB_Type SaveFormat = Pet_Manager::DB_Type::FILE;

//Class to get Variables from struct in Pet_Manager

void companionF()
{
    ImGui::Begin("Game Over");
    ImGui::Text("Sometimes, dead is better");
    ImGui::End();
}

int main(int argc, char** argv)
{
    std::unique_ptr<Pet_Manager[]> pet_manager_obj(new Pet_Manager[4]);

    formatting formatting_obj;

    

    // Start SFML Window
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Companion");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60); // Spped of display refresh and stats update

    //
    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    ImGui::SFML::Init(window, false);

    formatting_obj.lifestats(NULL);
    formatting_obj.loadfonts();
    //sf::CircleShape shape(300.f);
    //shape.setPosition(10, 30);
    //shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    sf::Clock Clock;

   // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoSavedSettings /*| ImGuiWindowFlags_NoResize*/ /*| ImGuiWindowFlags_NoMove*/ | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize;
  
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(600, 350));

    static int selItem = 0;
    static int dish = 0;
    static const char* items[] = { "Save 1","Save 2", "Save 3", "Save 4" };


    static bool save_file = true;
    static bool save_sql = false;

    static bool x = false;
    food_dish obj;
    // Main Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
       
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
        // SFML-IMGUI Window Menu
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("MainFile"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    window.close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::PopFont();


        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
        // Start IMGUI Window
        if (ImGui::Begin("Status", NULL, formatting_obj.main_window)) // begin window
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::BeginMenu("Save"))
                    {
                        if (ImGui::MenuItem(items[0]))
                        {
                            pet_manager_obj[0].Save_DB(items[0], SaveFormat);
                        }
                        if (ImGui::MenuItem(items[1]))
                        {
                            pet_manager_obj[1].Save_DB(items[1], SaveFormat);
                        }
                        if (ImGui::MenuItem(items[2]))
                        {
                            pet_manager_obj[2].Save_DB(items[2], SaveFormat);
                        }
                        if (ImGui::MenuItem(items[3]))
                        {
                            pet_manager_obj[3].Save_DB(items[3], SaveFormat);
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Load"))
                    {
                        if (ImGui::MenuItem(items[0]))
                        {
                            pet_manager_obj[0].Load_DB(items[0], SaveFormat);
                        }
                        if (ImGui::MenuItem(items[1]))
                        {
                            pet_manager_obj[1].Load_DB(items[1], SaveFormat);
                        }
                        if (ImGui::MenuItem(items[2]))
                        {
                            pet_manager_obj[2].Load_DB(items[2], SaveFormat);
                        }
                        if (ImGui::MenuItem(items[3]))
                        {
                            pet_manager_obj[3].Load_DB(items[3], SaveFormat);
                        }
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("opt"))
                {
                    if (ImGui::MenuItem("file", NULL, &save_file))
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
                ImGui::EndMenuBar();
            }

            // Age
            ImGui::Text("Age: %.1f", pet_manager_obj[selItem].petVar.Age);
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x * 10);
            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::Combo("Pet", &selItem, items, IM_ARRAYSIZE(items)))
            {
                // this code gets if user clicks on the button // but noting needed selItem linked to pet_manager_obj[selItem]
            }

             // Health
            char health_buf[64];
            sprintf_s(health_buf, "%.1f/%.1f%%", (pet_manager_obj[selItem].petVar.Health), pet_manager_obj[selItem].petVar.Max_Health);
            formatting_obj.ProgressBar_Alt((pet_manager_obj[selItem].petVar.Health / pet_manager_obj[selItem].petVar.Max_Health), ImVec2(250.0f, 0.0f), "Health", health_buf, pet_manager_obj[selItem].petVar.Health <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive));

            // Hunger
            char hunger_buf[64];
            sprintf_s(hunger_buf, "%.1f/%.1f%%", (pet_manager_obj[selItem].petVar.Hunger), pet_manager_obj[selItem].petVar.Max_Hunger);
            formatting_obj.ProgressBar_Alt((pet_manager_obj[selItem].petVar.Hunger / pet_manager_obj[selItem].petVar.Max_Hunger), ImVec2(250.0f, 0.0f), "Hunger", hunger_buf, pet_manager_obj[selItem].petVar.Hunger <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive));

            // Thirst
            char thirst_buf[64];
            sprintf_s(thirst_buf, "%.1f/%.1f%%", (pet_manager_obj[selItem].petVar.Thirst), pet_manager_obj[selItem].petVar.Max_Thirst);
            formatting_obj.ProgressBar_Alt((pet_manager_obj[selItem].petVar.Thirst / pet_manager_obj[selItem].petVar.Max_Thirst), ImVec2(250.0f, 0.0f), "Thirst", thirst_buf, pet_manager_obj[selItem].petVar.Thirst <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive));



            //// Food Bowl
            //char food_buf[64];
            //sprintf_s(food_buf, "%.1f/%.1f%%", (pet_manager_obj[selItem].petVar.Plate), pet_manager_obj[selItem].petVar.Max_Plate);
            //ImGui::ProgressBar3((pet_manager_obj[selItem].petVar.Plate / pet_manager_obj[selItem].petVar.Max_Plate), ImVec2(50.0f, 250.0f), food_buf);

            // New Food Dish
            char food_buf[64];
            sprintf_s(food_buf, "%.0f/%.0f%%", (obj.dish_current), obj.dish_max);
            formatting_obj.ProgressBar_Vertical((obj.dish_current / obj.dish_max), ImVec2(50.0f, 250.0f), food_buf);

            ImGui::SameLine();

            // Water Dish
            char water_bowl_buf[64];
            sprintf_s(water_bowl_buf, "%.0f/%.0f%%", (pet_manager_obj[selItem].petVar.Water_Bowl), pet_manager_obj[selItem].petVar.Max_Water_Bowl);
            formatting_obj.ProgressBar_Vertical((pet_manager_obj[selItem].petVar.Water_Bowl / pet_manager_obj[selItem].petVar.Max_Water_Bowl), ImVec2(50.0f, 250.0f), water_bowl_buf);

            // Button to make food available
            //if (ImGui::Button("Replenish Food"))
            //{
            //    // Add Food to Plate
            //    pet_manager_obj[selItem].Feeder();
            //}
            //ImGui::SameLine(); 
            

            if (obj.dish_current <= obj.dish_min)
            {
                ImGui::Text(*obj.food_empty);
            }



            if (ImGui::Button("Food Menu"))
            {

                x = !x;

            }
            if (x)
            {
                obj.food_list(x);

            }
            ImGui::SameLine();
            // Button to make water available
            if (ImGui::Button("Fill Water"))
            {
                // Add Water to plate ?
                pet_manager_obj[selItem].Hydrater();
            }
            

            //ImGui::ProgressBar2((pet_manager_obj[selItem].petVar.Water_Bowl / pet_manager_obj[selItem].petVar.Max_Water_Bowl), ImVec2(0.0f, 250.0f), water_bowl_buf);
}




        ImGui::PopFont();


        ImGui::End();

        formatting_obj.lifestats(NULL);

        // Timer
        if(Clock.getElapsedTime().asSeconds() >= 0.015) 
        {
            //DebugBreak();
           pet_manager_obj[0].Update();
           pet_manager_obj[1].Update();
           pet_manager_obj[2].Update();
           pet_manager_obj[3].Update();
           Clock.restart();
        }

        deltaClock.restart();
 
        window.clear();
        //window.draw(shape);

        ImGui::SFML::Render(window); // Call this to render the gui you defined in your update
        window.display();
    }

    ImGui::SFML::Shutdown(); // Call when you want to shutdown imgui

    pet_manager_obj.release();

    return 0;

}




