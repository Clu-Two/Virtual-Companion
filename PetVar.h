#pragma once


using PetVars = struct PetVars // How does this work, you've defined a new namespace?
{
    // Living
    float Age = 0.0;
    bool ALIVE = true;
    bool AWAKE = true;


    // Health
    float Health = 90.0;
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
    float Hunger = 0.0;
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
    float Digested_Max = 100.0;


    //// Water
    // Water Bowl
    float Water_Bowl = 0.0;
    float Min_Water_Bowl = 0.0;
    float Max_Water_Bowl = 150.0;
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
    float Water_Stomach_Max = 100.0;
    float Processed = 0.0;
    float Processed_Min = 0.0;
    float Processed_Max = 0.0;
};
// this will be saved to file , at any point u want ( in file raw method)
// and load wen u want it to... restoring the saved values that was be saved with save func 
