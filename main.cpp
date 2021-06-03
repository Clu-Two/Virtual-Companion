
//


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


void LifeStats(ImGuiStyle* lif = NULL);
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



void LoadFonts()
{
    ImGui::GetIO().Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)
    ImGui::GetIO().Fonts->AddFontDefault(); // this will load default font as well
    ImGui::GetIO().Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\ARLRDBD.TTF)", 16.0f);
    ImGui::GetIO().Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\ARLRDBD.TTF)", 12.0f);
//     ImGui::GetIO().Fonts->AddFontFromFileTTF("font2.ttf", 12.f);

    ImGui::SFML::UpdateFontTexture(); // important call: updates font texture

}

namespace ImGui
{

    static inline float ImAcos01(float x)
    {
        if (x <= 0.0f) return IM_PI * 0.5f;
        if (x >= 1.0f) return 0.0f;
        return ImAcos(x);
        //return (-0.69813170079773212f * x * x - 0.87266462599716477f) * x + 1.5707963267948966f; // Cheap approximation, may be enough for what we do.
    }

    void RenderRectFilledRangeV(ImDrawList* draw_list, const ImRect& rect, ImU32 col, float y_start_norm, float y_end_norm, float rounding)
    {
        if (y_end_norm == y_start_norm)
            return;
        if (y_start_norm > y_end_norm)
            ImSwap(y_start_norm, y_end_norm);

//         ImVec2 p0 = ImVec2(ImLerp(rect.Min.x, rect.Max.x, y_start_norm), rect.Min.y);
//         ImVec2 p1 = ImVec2(ImLerp(rect.Min.x, rect.Max.x, y_end_norm), rect.Max.y);
//
        ImVec2 p0 = ImVec2(ImLerp(rect.Min.x, rect.Max.x, y_start_norm), rect.Min.y);
        ImVec2 p1 = ImVec2( rect.Max.x, ImLerp(rect.Min.y, rect.Max.y, y_end_norm));


        if (rounding == 0.0f)
        {
            draw_list->AddRectFilled(p0, p1, col, 0.0f);
            return;
        }

        rounding = ImClamp(ImMin((rect.Max.x - rect.Min.x) * 0.5f, (rect.Max.y - rect.Min.y) * 0.5f) - 1.0f, 0.0f, rounding);
        const float inv_rounding = 1.0f / rounding;
        const float arc0_b = ImAcos01(1.0f - (p0.x - rect.Min.x) * inv_rounding);
        const float arc0_e = ImAcos01(1.0f - (p1.x - rect.Min.x) * inv_rounding);
        const float half_pi = IM_PI * 0.5f; // We will == compare to this because we know this is the exact value ImAcos01 can return.
        const float x0 = ImMax(p0.x, rect.Min.x + rounding);
        if (arc0_b == arc0_e)
        {
            draw_list->PathLineTo(ImVec2(x0, p1.y));
            draw_list->PathLineTo(ImVec2(x0, p0.y));
        }
        else if (arc0_b == 0.0f && arc0_e == half_pi)
        {
            draw_list->PathArcToFast(ImVec2(x0, p1.y - rounding), rounding, 3, 6); // BL
            draw_list->PathArcToFast(ImVec2(x0, p0.y + rounding), rounding, 6, 9); // TR
        }
        else
        {
            draw_list->PathArcTo(ImVec2(x0, p1.y - rounding), rounding, IM_PI - arc0_e, IM_PI - arc0_b, 3); // BL
            draw_list->PathArcTo(ImVec2(x0, p0.y + rounding), rounding, IM_PI + arc0_b, IM_PI + arc0_e, 3); // TR
        }
        if (p1.x > rect.Min.x + rounding)
        {
            const float arc1_b = ImAcos01(1.0f - (rect.Max.x - p1.x) * inv_rounding);
            const float arc1_e = ImAcos01(1.0f - (rect.Max.x - p0.x) * inv_rounding);
            const float x1 = ImMin(p1.x, rect.Max.x - rounding);
            if (arc1_b == arc1_e)
            {
                draw_list->PathLineTo(ImVec2(x1, p0.y));
                draw_list->PathLineTo(ImVec2(x1, p1.y));
            }
            else if (arc1_b == 0.0f && arc1_e == half_pi)
            {
                draw_list->PathArcToFast(ImVec2(x1, p0.y + rounding), rounding, 9, 12); // TR
                draw_list->PathArcToFast(ImVec2(x1, p1.y - rounding), rounding, 0, 3);  // BR
            }
            else
            {
                draw_list->PathArcTo(ImVec2(x1, p0.y + rounding), rounding, -arc1_e, -arc1_b, 3); // TR
                draw_list->PathArcTo(ImVec2(x1, p1.y - rounding), rounding, +arc1_b, +arc1_e, 3); // BR
            }
        }
        draw_list->PathFillConvex(col);
    }


    void ProgressBar2( float fraction, const ImVec2& size_arg, const char* left_overlay = nullptr, const char* right_overlay = nullptr, ImU32 fill_color = GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = GetColorU32(ImGuiCol_FrameBg))
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImGuiContext& g = *GImGui;
        ImGuiStyle& style = g.Style;

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = CalcItemSize(size_arg, CalcItemWidth(), g.FontSize + style.FramePadding.y * 1.0f);
        ImRect bb(pos, pos + size);
        ItemSize(size, style.FramePadding.y);
        if (!ItemAdd(bb, 0))
            return;

        // Render
        fraction = ImSaturate(fraction);
        RenderFrame(bb.Min, bb.Max, bk_color, false, style.FrameRounding);

        bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));
        //const ImVec2 fill_br = ImVec2(ImLerp(bb.Min.x, bb.Max.x, fraction), bb.Max.y);

        RenderRectFilledRangeH(window->DrawList, bb, fill_color, 0.0f, fraction, style.FrameRounding);
        // Default displaying the fraction as percentage string, but user can override it
        char overlay_buf[32];
        if (!(left_overlay || right_overlay))
        {
            ImFormatString(overlay_buf, IM_ARRAYSIZE(overlay_buf), "%.0f%%", fraction * 100 + 0.01f);
            left_overlay = overlay_buf;
        }

        ImVec2 l_overlay_size = CalcTextSize(left_overlay, NULL);
        ImVec2 r_overlay_size = CalcTextSize(right_overlay, NULL);

        if (l_overlay_size.x > 0.0f || r_overlay_size.x > 0.0f)
        {
            if (left_overlay)
                RenderTextClipped(bb.Min, bb.Max, left_overlay, NULL, &l_overlay_size, ImVec2(0.0f, 0.0f), &bb);
            if (right_overlay)
                RenderTextClipped(ImVec2( ( bb.Max.x - r_overlay_size.x - style.ItemInnerSpacing.x), bb.Min.y), bb.Max, right_overlay, NULL, &r_overlay_size, ImVec2(0.0f, 0.5f), &bb);
        }
    }

    void ProgressBar3(float fraction, const ImVec2& size_arg, const char* overlay = nullptr, ImU32 fill_color = GetColorU32(ImGuiCol_PlotHistogram), ImU32 bk_color = GetColorU32(ImGuiCol_FrameBg))
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImGuiContext& g = *GImGui;
        ImGuiStyle& style = g.Style;

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = CalcItemSize(size_arg,  g.FontSize + style.FramePadding.y * 1.0f, CalcItemWidth());
        ImRect bb( pos + size, pos);
        ItemSize(size, style.FramePadding.y);
        if (!ItemAdd(bb, 0))
            return;

        // Render
        fraction = ImSaturate(fraction);
        RenderFrame(bb.Min, bb.Max, bk_color, false, style.FrameRounding);
        bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));
        //const ImVec2 fill_br = ImVec2(ImLerp(bb.Min.x, bb.Max.x, fraction), bb.Max.y);

        RenderRectFilledRangeV(window->DrawList, bb, fill_color, 0.0f, fraction, style.FrameRounding);
        // Default displaying the fraction as percentage string, but user can override it

        char overlay_buf[32];
        if (!overlay)
        {
            ImFormatString(overlay_buf, IM_ARRAYSIZE(overlay_buf), "%.0f%%", fraction * 100 + 0.01f);
            overlay = overlay_buf;
        }

        ImVec2 overlay_size = CalcTextSize(overlay, NULL);
        if (overlay_size.x > 0.0f)
            RenderTextWrapped(bb.Max, overlay, NULL, 50); 
            //RenderTextClipped(bb.Max, bb.Min, overlay, NULL, &overlay_size, ImVec2(0.0f, 0.0f), &bb);
    }

}


int main(int argc, char** argv)
{
    std::unique_ptr<Pet_Manager[]> pet_manager_obj(new Pet_Manager[4]);
    //std::unique_ptr<food_dish[]> food_dish_obj(new food_dish[4]);

    // Start SFML Window
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Companion");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60); // Spped of display refresh and stats update

    //
    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    ImGui::SFML::Init(window, false);

    LoadFonts();

    //sf::CircleShape shape(300.f);
    //shape.setPosition(10, 30);
    //shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    sf::Clock Clock;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoSavedSettings /*| ImGuiWindowFlags_NoResize*/ /*| ImGuiWindowFlags_NoMove*/ | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize;
  
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
        if (ImGui::Begin("Status", NULL, window_flags)) // begin window
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
            ImGui::ProgressBar2((pet_manager_obj[selItem].petVar.Health / pet_manager_obj[selItem].petVar.Max_Health), ImVec2(250.0f, 0.0f), "Health", health_buf, pet_manager_obj[selItem].petVar.Health <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive));

            // Hunger
            char hunger_buf[64];
            sprintf_s(hunger_buf, "%.1f/%.1f%%", (pet_manager_obj[selItem].petVar.Hunger), pet_manager_obj[selItem].petVar.Max_Hunger);
            ImGui::ProgressBar2((pet_manager_obj[selItem].petVar.Hunger / pet_manager_obj[selItem].petVar.Max_Hunger), ImVec2(250.0f, 0.0f), "Hunger", hunger_buf, pet_manager_obj[selItem].petVar.Hunger <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive));

            // Thirst
            char thirst_buf[64];
            sprintf_s(thirst_buf, "%.1f/%.1f%%", (pet_manager_obj[selItem].petVar.Thirst), pet_manager_obj[selItem].petVar.Max_Thirst);
            ImGui::ProgressBar2((pet_manager_obj[selItem].petVar.Thirst / pet_manager_obj[selItem].petVar.Max_Thirst), ImVec2(250.0f, 0.0f), "Thirst", thirst_buf, pet_manager_obj[selItem].petVar.Thirst <= 50.0f ? ImGui::GetColorU32(ImGuiCol_TextSelectedBg) : ImGui::GetColorU32(ImGuiCol_TitleBgActive));



            //// Food Bowl
            //char food_buf[64];
            //sprintf_s(food_buf, "%.1f/%.1f%%", (pet_manager_obj[selItem].petVar.Plate), pet_manager_obj[selItem].petVar.Max_Plate);
            //ImGui::ProgressBar3((pet_manager_obj[selItem].petVar.Plate / pet_manager_obj[selItem].petVar.Max_Plate), ImVec2(50.0f, 250.0f), food_buf);

            // New Food Dish
            char food_buf[64];
            sprintf_s(food_buf, "%.0f/%.0f%%", (obj.dish_current), obj.dish_max);
            ImGui::ProgressBar3((obj.dish_current / obj.dish_max), ImVec2(50.0f, 250.0f), food_buf);

            ImGui::SameLine();

            // Water Dish
            char water_bowl_buf[64];
            sprintf_s(water_bowl_buf, "%.0f/%.0f%%", (pet_manager_obj[selItem].petVar.Water_Bowl), pet_manager_obj[selItem].petVar.Max_Water_Bowl);
            ImGui::ProgressBar3((pet_manager_obj[selItem].petVar.Water_Bowl / pet_manager_obj[selItem].petVar.Max_Water_Bowl), ImVec2(50.0f, 250.0f), water_bowl_buf);

            // Button to make food available
            //if (ImGui::Button("Replenish Food"))
            //{
            //    // Add Food to Plate
            //    pet_manager_obj[selItem].Feeder();
            //}
            //ImGui::SameLine(); 

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

        //
        LifeStats();

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

//// Custom Colour Scheme for ImGui
void Companion(ImGuiStyle* dst)
{
    ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.60f); // Inside Frame Background

    //colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.99f, 0.71f, 0.03f, 1.00f); // Frame Border

    //colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.80f, 0.07f, 0.20f);; // Background of elements e.g. Empty section of Progress Bars

    //colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.73f, 0.99f, 0.35f);
    //colors[ImGuiCol_FrameBgActive] = ImVec4(0.19f, 0.73f, 0.99f, 0.20f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.99f, 0.71f, 0.03f, 0.70f);// Top Bar of Window
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.99f, 0.71f, 0.03f, 0.80f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.99f, 0.71f, 0.03f, 0.30f);

    //colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    //colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);
    //colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);
    //colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);
    //colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    //colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    //colors[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);

    colors[ImGuiCol_Button] = ImVec4(0.00f, 0.18f, 0.55f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.28f, 0.65f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.38f, 0.75f, 1.00f);

    //colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.73f, 0.99f, 0.35f);
    //colors[ImGuiCol_HeaderActive] = ImVec4(0.19f, 0.73f, 0.99f, 0.10f);
    //colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
    //colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
    //colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
    //colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);
    //colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);
    //colors[ImGuiCol_ResizeGripActive] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);
    //colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.90f);
    //colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
    //colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
    //colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
    //colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
    //colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.19f, 0.73f, 0.99f, 0.35f);

    colors[ImGuiCol_PlotHistogram] = ImVec4(0.24f, 0.80f, 0.07f, 1.00f);

    //colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.30f, 1.00f, 0.00f, 0.35f);
    //colors[ImGuiCol_TableHeaderBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_TableBorderStrong] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);   // Prefer using Alpha=1.0 here
    //colors[ImGuiCol_TableBorderLight] = ImVec4(0.19f, 0.73f, 0.99f, 1.00f);   // Prefer using Alpha=1.0 here
    //colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
    //colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
    //colors[ImGuiCol_DragDropTarget] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    //colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
    //colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    //colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
}

void LifeStats(ImGuiStyle* lif)
{
    ImGuiStyle* style = lif ? lif : &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.10f); // Inside Frame Background

    colors[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // Frame Border

    colors[ImGuiCol_FrameBg] = ImVec4(0.89f, 0.0f, 0.0f, 0.40f);// Background of elements e.g. Empty section of Progress Bars

    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.59f, 0.0f, 0.50f);// Top Bar of Window
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.59f, 0.0f, 0.70f);

    colors[ImGuiCol_Button] = ImVec4(0.10f, 0.59f, 0.0f, 0.50f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.10f, 0.59f, 0.0f, 0.80f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.59f, 0.0f, 0.70f);

    colors[ImGuiCol_PlotHistogram] = ImVec4(0.89f, 0.0f, 0.0f, 1.00f);

}

