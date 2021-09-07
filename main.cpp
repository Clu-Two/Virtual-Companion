
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

    //Pet_Manager* Pet = new Pet_Manager[4], *selected_pet;
    //food_manager food1, food2, food3, food4, *selected_food;
    CustomColours colours_obj;

int main(int argc, char** argv)
{
    std::unique_ptr<Pet_Manager[]> Pet(new Pet_Manager[4]);

    // Start SFML Window
    sf::RenderWindow main_window;
    main_window.create(sf::VideoMode(315, 568), "Companion", sf::Style::None);
    main_window.setVerticalSyncEnabled(true);

    main_window.resetGLStates();
    ImGui::SFML::Init(main_window, false);

    loadfonts();

    sf::Clock deltaClock, Clock;

    sf::Color Transparent = { 0,0,0,100 };
    sf::Texture idle, hungry, eating, starving, f, minushp, *currentTex1, *currentTex2, *currentTex3, *currentTex4, *selected_sprite;
 
    hungry.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\hungry.png");
    eating.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\eating.png");
    minushp.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\starving.png");
    f.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\f.png");
    idle.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\idle.png");
    starving.loadFromFile("D:\\Clu 2\\Desktop\\Work\\Programming Projects\\vP\\vs project files\\IMGui_Companion_mu_v0.1\\assets\\images\\minushp.png");

    currentTex1 = &idle;
    currentTex2 = &idle;
    currentTex3 = &idle;
    currentTex4 = &idle;

    static int selItem = 0;
    static const char* items[] = { "Pet 1","Pet 2", "Pet 3", "Pet 4" };
   
    static bool save_file = true;
    static bool save_sql = false;

    static bool x = false;

    Pet[0].pet_name = "Titus";
    Pet[1].pet_name = "Jor El";
    Pet[2].pet_name = "Zoidberg";
    Pet[3].pet_name = "Mr. Bigglesworth";

    std::vector<sf::Texture*> SPRITE{ currentTex1, currentTex2, currentTex3, currentTex4 }; selected_sprite = SPRITE[0];
    std::vector <float> BARS{ Pet[0].Health, Pet[0].Hunger, Pet[0].Thirst};
    std::vector <const char*> LABELS{ "Health","Hunger","Thirst" };
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
                            //Pet[selected].Save_DB(items[selItem], SaveFormat);
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Load"))
                    {
                        //Pet[selected].Load_DB(items[selItem], SaveFormat);
                    }
                    if (ImGui::MenuItem("Exit"))
                    {
                        main_window.close();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Pets"))
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (ImGui::MenuItem(Pet[i].pet_name.c_str()))
                        {
                            selected = i;
                            //selected_pet = &Pet[i];
                            //selected_food = &FOOD[i];
                            selected_sprite = SPRITE[i];
                        }
                    }
                    ImGui::EndMenu();
                }
               
                ImGui::EndMenuBar();
            }

            ImGui::Text(Pet[selected].pet_name.c_str());
            ImGui::Text("Status: %s", (Pet[selected].status.c_str()));
            //ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x * 20);
            //ImGui::SetNextItemWidth(100.0f);
            //if (ImGui::Combo("Pet", &selItem, items, IM_ARRAYSIZE(items)))
            //{
            //    selected_pet = &PET[selItem];
            //}

            // Age
            ImGui::Text("Age: %.0f", Pet[selected].Age);

            // Revive
            //if (Pet[selected].ALIVE == false)
            //{
            //    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x * 10);
            //    if (ImGui::Button("Revive"))
            //    {
            //        //newPet();
            //    }
            //}

            /*char health_buf[64];
            char hunger_buf[64];
            char thirst_buf[64];
            char BUFFS[3]{ health_buf, hunger_buf, thirst_buf };
            for (int i = 0; i < 3; i++)
            {
                sprintf_s(BUFFS[i], "%.0f/%.0f%%", BARS[i], Pet[selected].Max_Health);
                BARS[i] <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive);
                ProgressBar_Alt((BARS[i] / Pet[selected].Max_Health), ImVec2(250.0f, 0.0f), LABELS[i], BUFFS[i], BARS[i]);
            }*/

            // Health
            char health_buf[64];
            sprintf_s(health_buf, "%.0f/%.0f%%", (Pet[selected].Health), Pet[selected].Max_Health);
            Pet[selected].Health <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive);
            ProgressBar_Alt((Pet[selected].Health / Pet[selected].Max_Health), ImVec2(250.0f, 0.0f), "Health", health_buf, Pet[selected].Health);

            // Hunger
            char hunger_buf[64];
            sprintf_s(hunger_buf, "%.0f/%.0f%%", (Pet[selected].Hunger), Pet[selected].Max_Hunger);
            ProgressBar_Alt((Pet[selected].Hunger / Pet[selected].Max_Hunger), ImVec2(250.0f, 0.0f), "Hunger", hunger_buf, Pet[selected].Hunger);

            // Thirst
            char thirst_buf[64];
            sprintf_s(thirst_buf, "%.0f/%.0f%%", (Pet[selected].Thirst), Pet[selected].Max_Thirst);
            ProgressBar_Alt((Pet[selected].Thirst / Pet[selected].Max_Thirst), ImVec2(250.0f, 0.0f), "Thirst", thirst_buf, Pet[selected].Thirst);

            // Food Dish
            char food_buf[64];
            sprintf_s(food_buf, "%.0f%%", (Pet[selected].dish_current));
            ProgressBar_Vertical((Pet[selected].dish_current / Pet[selected].dish_max), ImVec2(50.0f, 250.0f), food_buf, colours_obj.food[0], colours_obj.food[1]);
            ImGui::SameLine();
            // Stomach Bar
            ProgressBar_Vertical_NoLabel((Pet[selected].Stomach / Pet[selected].Stomach_Max), ImVec2(5.0f, 250.0f), colours_obj.food[2], colours_obj.food[3]);
            ImGui::SameLine();
            // Digestion Bar
            ProgressBar_Vertical_NoLabel((Pet[selected].Digested / Pet[selected].Digested_Max), ImVec2(5.0f, 250.0f), colours_obj.food[4], colours_obj.food[5]);
            ImGui::SameLine();

            // Water Dish
            char water_bowl_buf[64];
            sprintf_s(water_bowl_buf, "%.0f%%", (Pet[selected].Water_Bowl));
            ProgressBar_Vertical((Pet[selected].Water_Bowl / Pet[selected].Max_Water_Bowl), ImVec2(50.0f, 250.0f), water_bowl_buf, colours_obj.water[0], colours_obj.water[1]);
            ImGui::SameLine();
            ProgressBar_Vertical_NoLabel((Pet[selected].Water_Stomach / Pet[selected].Water_Stomach_Max), ImVec2(5.0f, 250.0f), colours_obj.water[2], colours_obj.water[3]);
            ImGui::SameLine();
            ProgressBar_Vertical_NoLabel((Pet[selected].Processed / Pet[selected].Processed_Max), ImVec2(5.0f, 250.0f),colours_obj.water[4], colours_obj.water[5]);
            
            if (Pet[selected].ALIVE)
            {
                if (Pet[selected].Hunger <= 10.0) 
                {
                    selected_sprite = &idle;
                }
                if (Pet[selected].Thirst <= 10.0)
                {
                    selected_sprite = &idle;
                }
                if (Pet[selected].Stomach == Pet[selected].Stomach_Max)
                {
                    selected_sprite = &eating;
                }
                if (Pet[selected].Hunger > 30.0 || Pet[selected].Thirst > 25.0)
                {
                    selected_sprite = &hungry;
                }
                if (Pet[selected].Starv > 0.0 || Pet[selected].Dehy > 0.0)
                {
                    selected_sprite = &starving;
                }
                if (Pet[selected].Health <= 50.0)
                {
                    selected_sprite = &minushp;
                }
            }
            if (!Pet[selected].ALIVE)
            {
                selected_sprite = &f;
            }
            ImGui::SameLine();
            ImGui::Image(*selected_sprite, sf::Vector2f(150, 150));
            //ImGui::Text("IMAGE LOAD ERROR");

            if (Pet[selected].dish_current <= Pet[selected].dish_min) //?
            {
                ImGui::Text(Pet[selected].food_empty);
            }
            if (ImGui::Button("Food Menu"))
            {
                x = !x;
            }
            if (x)
            {
                Pet[selected].food_list(x);
            }
            ImGui::SameLine();
            if (ImGui::Button("Fill Water"))
            {
                Pet[selected].Hydrater();
            }
}
        Pet[selected].Eater();
        ImGui::PopFont();

        ImGui::End();

        // Timer
        if(Clock.getElapsedTime().asSeconds() >= 0.005f) 
        {
           for (int i = 0; i < 4; i++)
           {
               Pet[i].Update();
               //FOOD[i].food_updater();
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
    Eater();
    //logDB_CMD();
}

//void food_manager::food_updater()
//{
//   Eater();
//}

bool Pet_Manager::food_list(bool& show)
{
    static bool x = false;
    ImGui::Begin("Todays Menu", NULL, secondary_window);
    for (int i = 0; i < 6; i++)
    {
        if (ImGui::Button(food_label_arr[i]))
        {
                dish_fill(dish_filler[i], digestion_time[i]);
        }
    }
    if (ImGui::Button("Close"))
    {
        show = !show;
    } 
    /*if (x)
    {
        dish_full(x);
    }}*/
    ImGui::End();
    return !show;
}

//int food_manager::dish_fill(int dish_fill, int digestion_time)
//{
//    float dish_space = dish_max - dish_current;
//    static bool show = false;
//    if (dish_space >= dish_fill)
//    {
//        selected_food->dish_current += dish_fill;
//        digestion_time += digestion_time;
//    }
//    //ImGui::Text("Can't add any more food!");
//    return digestion_time;
//}

//bool food_manager::dish_full(bool& show)
//{
//    //ImGui::BeginChild("Uh Oh!");
//    //ImGuiWindowFlags localflags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
//    ImGui::Begin("Dish Full", NULL, notification_popup);
//    ImGui::Text(pet_name.c_str());
//    ImGui::SameLine();
//    ImGui::Text(dish_full_error.c_str());
//    ImGui::SameLine();
//    if (ImGui::Button("Ok"))
//    {
//        show = !show;
//    }
//    ImGui::End();
//    //ImGui::EndChild();
//    return !show;
//}


// If Plate has Food - Eat and fill Stomach
//void food_manager::Eater() // 
//{
//    if (ALIVE == true)
//    {
//        float stomach_space = Stomach_Max - Stomach;
//        if (selected_food->dish_current > dish_min && Hunger > 15.0f && Stomach < Stomach_Max)
//        {
//            if (Hunger > 30.0f)
//            {
//                selected_food->dish_current -= 0.2f;
//                Stomach += 0.2f; 
//            }
//            if (Hunger > 60.0f)
//            {
//                selected_food->dish_current -= 0.3f;
//                Stomach += 0.3f;
//            }
//            if (Hunger > 90.0f)
//            {
//                selected_food->dish_current -= 0.4f;
//                Stomach += 0.4f;
//            }
//            selected_food->dish_current -= 0.1f; // Reduce Food available to eat 3f max 0/3
//            Stomach += 0.1f; // Increase Ingested Calories
//        }
//        if (Stomach >= Stomach_Max)
//        {
//            std::cout << "Companion cannot eat any more" << std::endl;
//        }
//    }
//}


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
        pet_death(ALIVE, starv_death);
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
        pet_death(ALIVE, thirst_death);
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

bool Pet_Manager::pet_death(bool& show, std::string cause_of_death) // add remove text after a few seconds
{
    ImGui::Begin("Report", NULL, notification_popup);
    ImGui::Text(pet_name.c_str());
    ImGui::SameLine();
    ImGui::Text(cause_of_death.c_str());
    ImGui::End();
    bool x = false;
    if (ImGui::Button("Close"))
    {
        x = !x;
    } if (x)
    {
        show = !show;
        return show;
    }
}


