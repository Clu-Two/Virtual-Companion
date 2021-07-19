#pragma once

#include "imgui.h"

// Text
    extern void loadfonts();

// Colour Styles
    extern void lifestats(ImGuiStyle* life_stats);
    extern void Companion(ImGuiStyle* dst);

// Elements
    // Mu's Vertical Progress Bar
    extern void ProgressBar_Vertical(float fraction, const ImVec2& size_arg, const char* overlay = nullptr, ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = ImGui::GetColorU32(ImGuiCol_FrameBg));
    extern         void ProgressBar_Alt(float fraction, const ImVec2& size_arg, const char* left_overlay = nullptr, const char* right_overlay = nullptr, ImU32 fill_color = ImGui::GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = ImGui::GetColorU32(ImGuiCol_FrameBg));



