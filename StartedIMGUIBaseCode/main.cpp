#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "Icons/IconsFontAwesome5.h"
#include <SFML/Graphics.hpp>

bool my_tool_active = true;

int main()
{
    ImGui::CreateContext();

    bool circleExists = true;
    float circleRadius = 200.f;
    int circleSegments = 100;
    float circleColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    ImGui::SFML::Init(window);
    sf::CircleShape shape(circleRadius, circleSegments);
    shape.setFillColor(sf::Color(
        (int)(circleColor[0] * 255),
        (int)(circleColor[1] * 255),
        (int)(circleColor[2] * 255)
    ));
    shape.setOrigin(circleRadius, circleRadius);                        
    shape.setPosition(400, 400);
   // shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;

    //fonts and icons

    ImGuiIO& io = ImGui::GetIO();

    float baseFontSize = 32.0f; // 13.0f is the size of the default font. Change to the font size you use.
    float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = iconFontSize;

    io.Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)
    io.Fonts->AddFontFromFileTTF("Fonts\\Roboto-Regular.ttf", 15.f);
    io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, iconFontSize, &icons_config, icons_ranges);
    ImFont* robotoFont12px = io.Fonts->AddFontFromFileTTF("Fonts\\Roboto-Regular.ttf", 12.f);
    ImFont* robotoFont18px = io.Fonts->AddFontFromFileTTF("Fonts\\Roboto-Regular.ttf", 18.f);

    ImGui::SFML::UpdateFontTexture(); // important call: updates font texture


    ImGui::NewFrame();
    ImGui::Render();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window Title", &my_tool_active, ImGuiWindowFlags_MenuBar);
        ImGui::Text("Window Text!");
        ImGui::Checkbox("Circle", &circleExists);
        ImGui::SliderFloat("Radius", &circleRadius, 100.0f, 300.0f);
        ImGui::SliderInt("Slides", &circleSegments, 3, 150);
        ImGui::ColorEdit3("Color Circle", circleColor);
        ImGui::End();

        

        shape.setFillColor(sf::Color(
            (int)(circleColor[0] * 255),
            (int)(circleColor[1] * 255),
            (int)(circleColor[2] * 255)
        ));

        shape.setRadius(circleRadius);
        shape.setPointCount(circleSegments);
        window.clear();

        if (circleExists)
        {
            window.draw(shape);
        }
        
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::EndFrame();
    ImGui::SFML::Shutdown();
    ImGui::DestroyContext();

    return 0;
}