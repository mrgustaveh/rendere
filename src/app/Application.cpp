#include "Application.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <cstdint>

Application::Application(uint32_t width, uint32_t height)
    : window(sf::VideoMode({width, height}), "RenderER") {};

void Application::run() {
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
