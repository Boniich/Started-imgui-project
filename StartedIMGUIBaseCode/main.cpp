#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

bool my_tool_active = true;

int main()
{

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

    ImGui::SFML::Shutdown();

    return 0;
}