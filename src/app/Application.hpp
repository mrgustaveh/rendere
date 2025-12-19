#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdint>
#include <memory>
#include "../core/Document.hpp"
#include "../core/Renderer.hpp"
#include "../tools/Tool.hpp"
#include "../gui/GuiManager.hpp"

class Application {
    public:
        Application(uint32_t width, uint32_t height);
        void run();

    private:
        sf::RenderWindow window;
        sf::Clock deltaClock;
        
        std::unique_ptr<core::Document> m_document;
        core::Renderer m_renderer;
        std::unique_ptr<tools::Tool> m_activeTool;
        
        std::unique_ptr<gui::GuiManager> m_guiManager;

        void handleEvents();
        void initDocument();
};

#endif // APPLICATION_HPP