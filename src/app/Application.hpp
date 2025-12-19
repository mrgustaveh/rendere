#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>
#include <memory>
#include "../core/Document.hpp"
#include "../core/Renderer.hpp"
#include "../tools/Tool.hpp"

class Application {
    public:
        Application(uint32_t width, uint32_t height);
        void run();

    private:
        sf::RenderWindow window;
        std::unique_ptr<core::Document> m_document;
        core::Renderer m_renderer;
        std::unique_ptr<tools::Tool> m_activeTool;

        void handleEvents();
        void initDocument();
};

#endif // APPLICATION_HPP