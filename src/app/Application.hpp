#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>

class Application {
    public:
        Application(uint32_t width, uint32_t height);
        void run();

    private:
        sf::RenderWindow window;
        void handleEvents();
};
