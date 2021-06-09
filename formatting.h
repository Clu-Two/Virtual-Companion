#pragma once

#include "imgui.h"

class formatting
{
    // Windows
public:
    ImGuiWindowFlags main_window = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings /*| ImGuiWindowFlags_NoResize*/ /*| ImGuiWindowFlags_NoMove*/ | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize;
    ImGuiWindowFlags secondary_window = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse;
    ImGuiWindowFlags notification_popup = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration;


    // Text
public:
    void loadfonts();
    //ImGuiInputTextFlags main =
    //ImGuiInputTextFlags popup =

// Colour Styles
public:
    void lifestats(ImGuiStyle* life_stats);
    void Companion(ImGuiStyle* dst);

// Elements
public:
    // Mu's Vertical Progress Bar
    //I removed the Imgui namespace and now getting a redefinition error
    void ProgressBar_Vertical(float fraction, const ImVec2& size_arg, const char* overlay = nullptr, ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = ImGui::GetColorU32(ImGuiCol_FrameBg));
    void ProgressBar_Alt(float fraction, const ImVec2& size_arg, const char* left_overlay = nullptr, const char* right_overlay = nullptr, ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = ImGui::GetColorU32(ImGuiCol_FrameBg));
};

class custom_progress_bars
{


};