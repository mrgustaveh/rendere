#include "Application.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>

Application::Application(uint32_t width, uint32_t height)
    : window(sf::VideoMode({width, height}), "RenderER")
{
    m_document = std::make_unique<core::Document>(width, height);
    initDocument();
}

void Application::initDocument() {
    auto* bgLayer = m_document->createLayer("Background");
    
    for (uint32_t y = 0; y < m_document->getHeight(); ++y) {
        for (uint32_t x = 0; x < m_document->getWidth(); ++x) {
            bgLayer->setPixel(x, y, sf::Color::White);
        }
    }
    bgLayer->updateTexture();

    auto* drawLayer = m_document->createLayer("Drawing");
    for (uint32_t i = 0; i < std::min(m_document->getWidth(), m_document->getHeight()); ++i) {
        drawLayer->setPixel(i, i, sf::Color::Red);
        if (i + 10 < m_document->getWidth())
             drawLayer->setPixel(i + 10, i, sf::Color::Red);
    }
    drawLayer->updateTexture();
}

void Application::run() {
    while (window.isOpen()) {
        handleEvents();

        window.clear(sf::Color(50, 50, 50));
        
        if (m_document) {
            m_renderer.render(*m_document, window);
        }

        window.display();
    }
}

void Application::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::V) {
                const auto& layers = m_document->getLayers();
                if (!layers.empty()) {
                    bool current = layers.back()->isVisible();
                    layers.back()->setVisible(!current);
                }
            }
        }
    }
}
