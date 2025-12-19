#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace gui {

class GuiManager {
public:
    GuiManager(sf::RenderWindow& window);
    ~GuiManager();

    void processEvent(const sf::RenderWindow& window, const sf::Event& event);
    void update(sf::RenderWindow& window, float deltaTime);
    void render(sf::RenderWindow& window);

private:
    void setupStyle();
};

} // namespace gui

#endif // GUI_MANAGER_HPP