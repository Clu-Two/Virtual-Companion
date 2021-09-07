#pragma once

#include "imgui.h"

// Text
    extern void loadfonts();

// Colour Styles
    extern void lifestats(ImGuiStyle* life_stats);
    extern void Companion(ImGuiStyle* dst);

// Custom Colours
    struct CustomColours
    {
        ImColor water[6] =
        {
            // Water Bowl
            ImColor(51,255,255),
            // Water Bowl Background
            ImColor(0,153,153),
            // Water Consumed
            ImColor(184,184,184),
            // Water Consumed Background
            ImColor(51,51,51),
            // Water Bladder
            ImColor(184,184,184),
            // Water Bladder Background
            ImColor(51,51,51),
        };
        ImColor food[6] =
        {
            // Food Bowl
            ImColor(255,153,51),
            // Food Bowl Background
            ImColor(199,119,40),
            // Food Consumed 
            ImColor(184,184,184),
            // Food Consumed Background
            ImColor(51,51,51),
            // Food Digestion 
            ImColor(184,184,184),
            // Food Digestion Background
            ImColor(51,51,51),
        };
        //ImColor life_stats[6] =
        //{
        //    // Health Bar
        //    ImColor(255,153,51),
        //    // Health Background
        //    ImColor(199,119,40),
        //    // Hunger Bar 
        //    ImColor(184,184,184),
        //    // HungerThirst Background
        //    ImColor(51,51,51),
        //    // Thirst Bar 
        //    ImColor(184,184,184),
        //    // Thirst Background
        //    ImColor(51,51,51),
        //};
    };


// Elements
    // Mu's Vertical Progress Bar
    extern void ProgressBar_Vertical(float fraction, const ImVec2& size_arg, const char* overlay = nullptr, ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = ImGui::GetColorU32(ImGuiCol_FrameBg));
    extern      void ProgressBar_Alt(float fraction, const ImVec2& size_arg, const char* left_overlay = nullptr, const char* right_overlay = nullptr, ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = ImGui::GetColorU32(ImGuiCol_FrameBg));
    extern void ProgressBar_Vertical_NoLabel(float fraction, const ImVec2& size_arg, ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = ImGui::GetColorU32(ImGuiCol_FrameBg));

    


