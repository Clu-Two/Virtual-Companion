#include "imgui.h"

#include "Pet.h"
#include "food.h"

#include <iostream>

void Pet_Manager::Update()
{
    addAge();
    Eater();
    Digester();
    StarvManager();
    Drinker();
    H2OProcessor();
    DehyManager();

    logDB_CMD();
}


int food_menu::food_list()
{

    ImGui::Begin("Todays Menu");
    if (ImGui::Button("Pizza Slice"))
    {
        food_dish::dish_fill(pizza_slice)
    }
    if (ImGui::Button("Roast Potato"))
    {
        food_dish::dish_fill(roast_potato)
    }
    if (ImGui::Button("Carrot"))
    {
        food_dish::dish_fill(carrot)
    }
    ImGui::End();
    return 0;
}

void food_dish::dish_fill(food_menu)
{
    if (dish_current < dish_max && dish_current <= dish_min)
    {
        dish_current += food_menu;
    }
    if (dish_current >= dish_max)
    {
        dish_full();
    }
}

void food_dish::dish_full()
{
    ImGui::Begin();
    ImGui::Text("[Pet Name] still has food left");
    if (ImGui::Button("Ok"))
    {
        ImGui::CloseCurrentPopup();
    }
    ImGui::End();
}

// When button pressed make food avaiable
void Pet_Manager::Feeder()
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Plate < petVar.Max_Plate) // Add food to Plate if not Full
        {
            petVar.Plate += 20.00f;
            if (petVar.Plate > petVar.Max_Plate)
            {
                petVar.Plate = petVar.Max_Plate;
            }
        }
        else // Plate Full inform user
        {
            petVar.Plate = petVar.Max_Plate;
            std::cout << "Plate Full" << std::endl;
        }
    }
}

// If Plate has Food - Eat and fill Stomach
void Pet_Manager::Eater() // 
{
    if (petVar.ALIVE == true)
    {
        if (petVar.Plate > petVar.Min_Plate) // If Plate has food
        {
            if (petVar.Hunger > 0.05f && (petVar.AWAKE == true)) // If Hungry
            {
                if (petVar.Stomach < petVar.Stomach_Max) // Eat food if not full //          Must put limit on Times can be fed in one day // This I'll add later
                {
                    petVar.Plate -= 0.03f; // Reduce Food available to eat 3f max 0/3
                    petVar.Stomach += 0.3f; // Increase Ingested Calories // 
                }
                else
                {
                    std::cout << "Companion cannot eat any more" << std::endl;
                }
            }
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
            petVar.Digested -= 0.006f;

            if (petVar.Digested < petVar.Digested_Min)
            {
                petVar.Digested = petVar.Digested_Min;
            }
            if (petVar.Health < petVar.Max_Health)
            {
                petVar.Health += 0.01f;
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
    else
    {
        // cant feed an dead pet
        petVar.ALIVE = false;
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
                petVar.Thirst -= 0.010f;
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
                petVar.Health += 0.01f;
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
}

//Age
void Pet_Manager::addAge()
{
    if (petVar.ALIVE == true)
    {
        petVar.Age += 0.01f;
    }
}
