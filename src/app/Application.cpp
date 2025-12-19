#include "Application.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../tools/BrushTool.hpp"
#include "../gui/Toolbar.hpp"
#include "../gui/LayerPanel.hpp"
#include <cstdint>
#include <algorithm>
#include <imgui.h>

Application::Application(uint32_t width, uint32_t height)
    : window(sf::VideoMode({width, height}), "RenderER")
{
    m_guiManager = std::make_unique<gui::GuiManager>(window);

    m_document = std::make_unique<core::Document>(width, height);
    initDocument();
    
    auto brush = std::make_unique<tools::BrushTool>();
    brush->setColor(sf::Color::Blue);
    brush->setSize(5);
    m_activeTool = std::move(brush);
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
    }
    drawLayer->updateTexture();
}

void Application::run() {
    while (window.isOpen()) {
        handleEvents();
        
        m_guiManager->update(window, deltaClock.restart().asSeconds());

        if (m_document) {
            gui::LayerPanel::render(*m_document);
        }
        gui::Toolbar::render(m_activeTool);

        window.clear(sf::Color(50, 50, 50));
        
        if (m_document) {
            m_renderer.render(*m_document, window);
        }

        m_guiManager->render(window);

        window.display();
    }
}

void Application::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        m_guiManager->processEvent(window, *event);
        
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        
        if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard) {
             continue;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
        }
        else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (m_activeTool && m_document) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                     m_activeTool->onPress({mousePressed->position.x, mousePressed->position.y}, *m_document);
                }
            }
        }
        else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (m_activeTool && m_document) {
                if (mouseReleased->button == sf::Mouse::Button::Left) {
                    m_activeTool->onRelease({mouseReleased->position.x, mouseReleased->position.y}, *m_document);
                }
            }
        }
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            if (m_activeTool && m_document) {
                m_activeTool->onDrag({mouseMoved->position.x, mouseMoved->position.y}, *m_document);
            }
        }
    }
}
