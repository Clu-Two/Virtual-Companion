#include <iostream>

#include "imgui.h"

#include "Pet.h"
#include "food.h"
#include "living.h"


extern ImGuiWindowFlags main_window;
extern ImGuiWindowFlags secondary_window;
extern ImGuiWindowFlags notification_popup;

extern Pet_Manager* pet_manager_obj; // MyRawPointer 

void Pet_Manager::Update()
{
    addAge();
    //food_dish_obj.Eater(food_dish_obj);
    Digester();
    StarvManager();
    Drinker();
    H2OProcessor();
    DehyManager();

    logDB_CMD();
}




bool food_dish::food_list(bool& show)
{
    //food_menu food_menu_obj;
    //food_menu_obj.carrot.digestion_time = 80;
    //food_menu_obj.banana.digestion_time = 50;
    //food_menu_obj.carrot.dish_fill = 20;
    //food_menu_obj.banana.dish_fill = 20;
    static bool x = false;

    ImGui::Begin("Todays Menu", NULL, secondary_window);
    if (ImGui::Button("Roast Potato"))
    {
        if (dish_current < dish_max)
        {
            dish_fill(food_menu_obj.potato);
        }
        if (dish_current >= dish_max)
        {
            x = !x;
        }
    }
    if (ImGui::Button("Pizza Slice"))
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
    }
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

int food_dish::dish_fill( food_data& food_dish_obj)
{
        dish_current += food_dish_obj.dish_fill;
        food_dish_obj.digestion_time += food_dish_obj.digestion_time;
        return food_dish_obj.digestion_time;
}

bool food_dish::dish_full(bool& show) // u can move this 2 functions to petmanager
{
    //ImGui::BeginChild("Uh Oh!");
    //ImGuiWindowFlags localflags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    ImGui::Begin("Dish Full", NULL, notification_popup);
    ImGui::Text(pet_manager_obj->petVar.pet_name); // acessing main obj here its a pain xd
    ImGui::SameLine();
    ImGui::Text(pet_manager_obj->petVar.dish_full_error);
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
void food_dish::Eater( food_dish& dobj) // 
{
    if (pet_manager_obj->petVar.ALIVE == true)
    {
    if (dobj.dish_current > dobj.dish_min && pet_manager_obj->petVar.Hunger > pet_manager_obj->petVar.Def_Hunger && pet_manager_obj->petVar.Stomach < pet_manager_obj->petVar.Stomach_Max)
        {
            dobj.dish_current -= 0.03f; // Reduce Food available to eat 3f max 0/3
            pet_manager_obj->petVar.Stomach += 0.3f; // Increase Ingested Calories // 
        }
        else
        {
            std::cout << "Companion cannot eat any more" << std::endl;
        }
    }
}


// If has consumed food, digest food
void Pet_Manager::Digester()
{
    if (petVar.ALIVE == true) //Alive Check
    {
        if (petVar.Stomach > petVar.Stomach_Min && petVar.Digested < petVar.Digested_Max) // If ingested calories > 0 some not good here
        {
            //std::clamp(petVar.Stomach, petVar.Stomach_Min, petVar.Stomach_Max);

            petVar.Stomach -= 0.025f;
            petVar.Digested += 0.025f;
            if (petVar.Stomach < petVar.Stomach_Min)
            {
                petVar.Stomach = petVar.Stomach_Min;
            }
            if (petVar.Hunger > petVar.Def_Hunger) // Reduce Hunger and Starvation when Digesting
            {
                petVar.Hunger -= 0.02f;
                if (petVar.Hunger < petVar.Def_Hunger)
                {
                    petVar.Hunger = petVar.Def_Hunger;
                }

            }
        }
        if (petVar.Digested > petVar.Digested_Min)
        {
            petVar.Digested -= 0.01f;

            if (petVar.Digested < petVar.Digested_Min)
            {
                petVar.Digested = petVar.Digested_Min;
            }
            if (petVar.Health < petVar.Max_Health)
            {
                petVar.Health += 0.02f;
            }
            if (petVar.Starv > petVar.Def_Starv && petVar.Digested > petVar.Digested_Min)
            {
                petVar.Starv -= 0.04f;
            }
        }
        if (petVar.Digested <= petVar.Digested_Min)
        {
            petVar.Hunger += 0.025f;
        }
    }

}

void Pet_Manager::StarvManager() // Starv Manager
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Health <= petVar.Min_Health)
        {
            petVar.ALIVE = false;
            std::cout << "Starvation Death" << std::endl;
        }
        //Hunger & Starv Cap 
        if (petVar.Hunger >= petVar.Max_Hunger)
        {
            petVar.Hunger = petVar.Max_Hunger;
            petVar.Starv += 0.01f;
        }
        if (petVar.Starv >= petVar.Max_Starv)
        {
            petVar.Starv = petVar.Max_Starv;
            petVar.Health -= 0.0025f;
        }
    }
    if (!petVar.ALIVE)
    {
        pet_death(petVar.ALIVE, *petVar.starv_death);
    }
}


//// Water Stat Loops

// Fill Water Bowl with Button Press
void Pet_Manager::Hydrater()
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Water_Bowl < petVar.Max_Water_Bowl) // Add Water to Bowl if not Full // Want to add 1% until its 100 animation
        {
            petVar.Water_Bowl += 20.0f;
            if (petVar.Water_Bowl > petVar.Max_Water_Bowl)
            {
                petVar.Water_Bowl = petVar.Max_Water_Bowl;
            }
        }
        else // Bowl Full inform user
        {
            petVar.Water_Bowl = petVar.Max_Water_Bowl;
            std::cout << "Water Bowl Full" << std::endl;
        }
    }

}

// Drink Water if Thirsty and Water available
void Pet_Manager::Drinker()
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Water_Bowl > petVar.Min_Water_Bowl)
        {
            if (petVar.Thirst > petVar.Def_Thirst && (petVar.AWAKE == true))
            {
                if (petVar.Water_Stomach < petVar.Water_Stomach_Max)
                {
                    petVar.Water_Bowl -= 0.10f;
                    petVar.Water_Stomach += 0.10f;
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
    if (petVar.ALIVE == true)
    {
        if (petVar.Water_Stomach > petVar.Water_Stomach_Min && petVar.Processed < petVar.Processed_Max)
        {
            petVar.Water_Stomach -= 0.10f;
            petVar.Processed += 0.10f;
            if (petVar.Water_Stomach < petVar.Water_Stomach_Min)
            {
                petVar.Water_Stomach = petVar.Water_Stomach_Min;
            }
            if (petVar.Thirst > petVar.Def_Thirst)
            {
                petVar.Thirst -= 0.10f;
                if (petVar.Thirst < petVar.Def_Thirst)
                {
                    petVar.Thirst = petVar.Def_Thirst;
                }
            }
        }
        if (petVar.Processed > petVar.Processed_Min)
        {
            petVar.Processed -= 0.005f;

            if (petVar.Processed < petVar.Processed_Min)
            {
                petVar.Processed = petVar.Processed_Min;
            }
            if (petVar.Health < petVar.Max_Health)
            {
                petVar.Health += 0.10f;
            }
            if (petVar.Dehy > petVar.Dehy_Min && petVar.Processed > petVar.Processed_Min)
            {
                petVar.Dehy -= 0.06f;
            }
        }
        if (petVar.Processed <= petVar.Processed_Min)
        {
            petVar.Thirst += 0.07f;
        }
    }
    else
    {
        petVar.ALIVE = false;
    }
}

// If Thirst is Max increase Dehydration, if Dehydration is Max reduce health
void Pet_Manager::DehyManager()
{
    if (petVar.ALIVE == true)
    {
        // Thirstcheck if alive
        if (petVar.Health <= petVar.Min_Health)
        {
            petVar.ALIVE = false;
            std::cout << "Dehyation Death" << std::endl;
        }
        //Thirst & Dehy Cap 
        if (petVar.Thirst >= petVar.Max_Thirst)
        {
            petVar.Thirst = petVar.Max_Thirst;
            petVar.Dehy += 0.03f;
        }
        if (petVar.Dehy >= petVar.Dehy_Max)
        {
            petVar.Dehy = petVar.Dehy_Max;
            petVar.Health -= 0.025f;
        }
    }
    if (!petVar.ALIVE)
    {
        pet_death(petVar.ALIVE, *petVar.thirst_death);
    }
}

//Age
void Pet_Manager::addAge()
{
    if (petVar.ALIVE == true)
    {
        petVar.Age += 0.01f;
    }
}

bool Pet_Manager::pet_death(bool& show, const char cause_of_death) // add remove text after a few seconds
{
    ImGui::Begin("Report");
    ImGui::Text(petVar.pet_name);
    ImGui::SameLine(27.7f, NULL);
    ImGui::Text(petVar.cause_of_death);
    ImGui::End();
    return !show;
}