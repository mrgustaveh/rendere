#include "Renderer.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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

    const auto& selection = document.getSelection();
    if (!selection.isEmpty()) {
        const auto& rect = selection.getRect();
        
        sf::RectangleShape shape;
        shape.setPosition({static_cast<float>(rect.position.x), static_cast<float>(rect.position.y)});
        shape.setSize({static_cast<float>(rect.size.x), static_cast<float>(rect.size.y)});
        
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1.0f);
        
        target.draw(shape);
        
        sf::RectangleShape shape2 = shape;
        shape2.setOutlineColor(sf::Color::Black);
        shape2.setOutlineThickness(1.0f);
        shape2.setPosition({shape.getPosition().x - 1, shape.getPosition().y - 1});
        shape2.setSize({shape.getSize().x + 2, shape.getSize().y + 2});
    }
}

}
