#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>
#include <memory>
#include "../core/Document.hpp"
#include "../core/Renderer.hpp"

class Application {
    public:
        Application(uint32_t width, uint32_t height);
        void run();

    private:
        sf::RenderWindow window;
        std::unique_ptr<core::Document> m_document;
        core::Renderer m_renderer;

        void handleEvents();
        void initDocument();
};
