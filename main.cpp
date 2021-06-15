
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
#include "formatting.h"



//void ThirstStats(ImGuiStyle* trst = NULL);
//void HungerStats(ImGuiStyle* hngr = NULL);

Pet_Manager::DB_Type SaveFormat = Pet_Manager::DB_Type::FILE;

//Class to get Variables from struct in Pet_Manager


    ImGuiWindowFlags main_window_style = /*ImGuiWindowFlags_NoTitleBar*/ ImGuiWindowFlags_NoCollapse /*| ImGuiWindowFlags_NoSavedSettings*/ /*| ImGuiWindowFlags_NoResize*/ | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize;
    ImGuiWindowFlags secondary_window = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
    ImGuiWindowFlags notification_popup = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;

    std::unique_ptr<Pet_Manager[]> pet_manager(new Pet_Manager[4]);

    Pet_Manager* pet_manager_obj = &pet_manager[0]; // MyRawPointer 

int main(int argc, char** argv)
{


    // Start SFML Window
    sf::RenderWindow main_window;
    main_window.create(sf::VideoMode(315, 568), "Companion", sf::Style::None);
    main_window.setVerticalSyncEnabled(true);
    main_window.setFramerateLimit(60); // Spped of display refresh and stats update
    sf::Color Transparent;
    //
    main_window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    ImGui::SFML::Init(main_window, false);

    lifestats(NULL);
    loadfonts();
    //sf::CircleShape shape(300.f);
    //shape.setPosition(10, 30);
    //shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    sf::Clock Clock;

   // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoSavedSettings /*| ImGuiWindowFlags_NoResize*/ /*| ImGuiWindowFlags_NoMove*/ | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize;
  


    static int selItem = 0;
    static const char* items[] = { "Pet 1","Pet 2", "Pet 3", "Pet 4" };


    static bool save_file = true;
    static bool save_sql = false;

    static bool x = false;

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
                    if (ImGui::BeginMenu("Select"))
                    {
                        if (ImGui::MenuItem(items[0]))
                        {
                            pet_manager_obj = &pet_manager[0];
                        }
                        if (ImGui::MenuItem(items[1]))
                        {
                            pet_manager_obj = &pet_manager[1];
                        }
                        if (ImGui::MenuItem(items[2]))
                        {
                            pet_manager_obj = &pet_manager[2];
                        }
                        if (ImGui::MenuItem(items[3]))
                        {
                            pet_manager_obj = &pet_manager[3];
                        }
                        ImGui::EndMenu();
                    }
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
                            pet_manager_obj->Save_DB(items[selItem], SaveFormat);
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Load"))
                    {
                        pet_manager_obj->Load_DB(items[selItem], SaveFormat);
                    }
                    if (ImGui::MenuItem("Exit"))
                    {
                        main_window.close();
                    }
                ImGui::EndMenu();
                }
            ImGui::EndMenuBar();
            }




            ImGui::Text("isAlive: %s", (pet_manager_obj->petVar.ALIVE ? "True" : "False"));
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x * 20);
            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::Combo("Pet", &selItem, items, IM_ARRAYSIZE(items)))
            {
                pet_manager_obj = &pet_manager[selItem];
                // this code gets if user clicks on the button 
            }

            // Age
            ImGui::Text("Age: %.1f", pet_manager_obj->petVar.Age);
            if (pet_manager_obj->petVar.ALIVE == false)
            {
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x * 10);
                if (ImGui::Button("Revive"))
                {
                    // Cool, althought wasn't planned, tamagotchi style, no revive, 
                }
            }
            // ok u can change it topet_manager_obj->"   or create pointer and assign the pointer u chouse ,what will be ur choice ? // oook pointer u will learn xd i thinking best way for n0ww its raw poiter 
             // Health
            char health_buf[64];
            sprintf_s(health_buf, "%.1f/%.1f%%", (pet_manager_obj->petVar.Health), pet_manager_obj->petVar.Max_Health);
            pet_manager_obj->petVar.Health <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive);
            ProgressBar_Alt((pet_manager_obj->petVar.Health / pet_manager_obj->petVar.Max_Health), ImVec2(250.0f, 0.0f), "Health", health_buf, pet_manager_obj->petVar.Health);

            // Hunger
            char hunger_buf[64];
            sprintf_s(hunger_buf, "%.1f/%.1f%%", (pet_manager_obj->petVar.Hunger), pet_manager_obj->petVar.Max_Hunger);
            ProgressBar_Alt((pet_manager_obj->petVar.Hunger / pet_manager_obj->petVar.Max_Hunger), ImVec2(250.0f, 0.0f), "Hunger", hunger_buf, pet_manager_obj->petVar.Hunger);

            // Thirst
            char thirst_buf[64];
            sprintf_s(thirst_buf, "%.1f/%.1f%%", (pet_manager_obj->petVar.Thirst), pet_manager_obj->petVar.Max_Thirst);
            ProgressBar_Alt((pet_manager_obj->petVar.Thirst / pet_manager_obj->petVar.Max_Thirst), ImVec2(250.0f, 0.0f), "Thirst", thirst_buf, pet_manager_obj->petVar.Thirst);



            //// Food Bowl
            //char food_buf[64];
            //sprintf_s(food_buf, "%.1f/%.1f%%", (pet_manager_obj->petVar.Plate), pet_manager_obj->petVar.Max_Plate);
            //ImGui::ProgressBar3((pet_manager_obj->petVar.Plate / pet_manager_obj->petVar.Max_Plate), ImVec2(50.0f, 250.0f), food_buf);

            // New Food Dish
            char food_buf[64];
            sprintf_s(food_buf, "%.0f/%.0f%%", (pet_manager_obj->food_dish_obj.dish_current), pet_manager_obj->food_dish_obj.dish_max);
            ProgressBar_Vertical((pet_manager_obj->food_dish_obj.dish_current / pet_manager_obj->food_dish_obj.dish_max), ImVec2(50.0f, 250.0f), food_buf);

            ImGui::SameLine();

            // Water Dish
            char water_bowl_buf[64];
            sprintf_s(water_bowl_buf, "%.0f/%.0f%%", (pet_manager_obj->petVar.Water_Bowl), pet_manager_obj->petVar.Max_Water_Bowl);
            ProgressBar_Vertical((pet_manager_obj->petVar.Water_Bowl / pet_manager_obj->petVar.Max_Water_Bowl), ImVec2(50.0f, 250.0f), water_bowl_buf);

            // Button to make food available
            //if (ImGui::Button("Replenish Food"))
            //{
            //    // Add Food to Plate
            //    pet_manager_obj->Feeder();
            //}
            //ImGui::SameLine(); 
            

            if (pet_manager_obj->food_dish_obj.dish_current <= pet_manager_obj->food_dish_obj.dish_min) //?
            {
                ImGui::Text(pet_manager_obj->food_dish_obj.food_empty);
            }



            if (ImGui::Button("Food Menu"))
            {

                x = !x;

            }
            if (x)
            {
                pet_manager_obj->food_dish_obj.food_list(x);

            }
            ImGui::SameLine();
            // Button to make water available
            if (ImGui::Button("Fill Water"))
            {
                // Add Water to plate ?
                pet_manager_obj->Hydrater();
            }
            

            //ImGui::ProgressBar2((pet_manager_obj->petVar.Water_Bowl / pet_manager_obj->petVar.Max_Water_Bowl), ImVec2(0.0f, 250.0f), water_bowl_buf);
}




        ImGui::PopFont();


        ImGui::End();

        lifestats(NULL);

        // Timer
        if(Clock.getElapsedTime().asSeconds() >= 0.015f) 
        {
            //DebugBreak();
           pet_manager[0].Update();
           pet_manager[1].Update();
           pet_manager[2].Update();
           pet_manager[3].Update();
           Clock.restart();
        }

        deltaClock.restart();
 
        main_window.clear();
        //window.draw(shape);

        ImGui::SFML::Render(main_window); // Call this to render the gui you defined in your update
        main_window.display();
    }

    ImGui::SFML::Shutdown(); // Call when you want to shutdown imgui

    pet_manager.release();

    return 0;

}




