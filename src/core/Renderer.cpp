#include "Renderer.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace core {

Renderer::Renderer() {
}

void Renderer::render(const Document& document, sf::RenderTarget& target) {
    const auto& layers = document.getLayers();
    
    for (const auto& layer : layers) {
        if (!layer->isVisible()) {
            continue;
        }

        const sf::Texture& texture = layer->getTexture();
        sf::Sprite sprite(texture);
        
        sf::Color color = sf::Color::White;
        color.a = layer->getOpacity();
        sprite.setColor(color);

        target.draw(sprite);
    }
}

}

