#include "Layer.hpp"

namespace core {
Layer::Layer(uint32_t width, uint32_t height, const std::string& name)
    : m_name(name)
    , m_width(width)
    , m_height(height)
    , m_visible(true)
    , m_opacity(255)
{
    m_image = sf::Image(sf::Vector2u(width, height));
    // Initialize to transparent
    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            m_image.setPixel(sf::Vector2u(x, y), sf::Color::Transparent);
        }
    }
    
    m_texture.create(sf::Vector2u(width, height));
    updateTexture();
}

void Layer::setPixel(uint32_t x, uint32_t y, sf::Color color) {
    if (x < m_width && y < m_height) {
        m_image.setPixel({x, y}, color);
    }
}

sf::Color Layer::getPixel(uint32_t x, uint32_t y) const {
    if (x < m_width && y < m_height) {
        return m_image.getPixel({x, y});
    }
    return sf::Color::Transparent;
}

void Layer::updateTexture() {
    m_texture.update(m_image);
}

const sf::Texture& Layer::getTexture() const {
    return m_texture;
}

const sf::Image& Layer::getImage() const {
    return m_image;
}

const std::string& Layer::getName() const {
    return m_name;
}

bool Layer::isVisible() const {
    return m_visible;
}

uint8_t Layer::getOpacity() const {
    return m_opacity;
}

void Layer::setName(const std::string& name) {
    m_name = name;
}

void Layer::setVisible(bool visible) {
    m_visible = visible;
}

void Layer::setOpacity(uint8_t opacity) {
    m_opacity = opacity;
}

}
