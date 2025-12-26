#include "GuiManager.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

namespace gui {

GuiManager::GuiManager(sf::RenderWindow& window) {
    if (!ImGui::SFML::Init(window)) {
        // Initialization failed - log or handle error if needed
    }
    setupStyle();
}

GuiManager::~GuiManager() {
    ImGui::SFML::Shutdown();
}

void GuiManager::processEvent(const sf::RenderWindow& window, const sf::Event& event) {
    ImGui::SFML::ProcessEvent(window, event);
}

void GuiManager::update(sf::RenderWindow& window, float deltaTime) {
    ImGui::SFML::Update(window, sf::Time(sf::seconds(deltaTime)));
}

void GuiManager::render(sf::RenderWindow& window) {
    ImGui::SFML::Render(window);
}

void GuiManager::setupStyle() {
    ImGui::StyleColorsDark();
}

} // namespace gui

