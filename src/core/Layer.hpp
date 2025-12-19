#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <cstdint>

namespace core {

class Layer {
    public:
        Layer(uint32_t width, uint32_t height, const std::string& name = "Layer");

        void setPixel(uint32_t x, uint32_t y, sf::Color color);
        sf::Color getPixel(uint32_t x, uint32_t y) const;
        
        void updateTexture();

        const sf::Texture& getTexture() const;
        const sf::Image& getImage() const;
        const std::string& getName() const;
        bool isVisible() const;
        uint8_t getOpacity() const;

        void setName(const std::string& name);
        void setVisible(bool visible);
        void setOpacity(uint8_t opacity);

    private:
        std::string m_name;
        uint32_t m_width;
        uint32_t m_height;
        
        sf::Image m_image;
        sf::Texture m_texture;
        
        bool m_visible;
        uint8_t m_opacity;
};

} // namespace core

#endif // LAYER_HPP