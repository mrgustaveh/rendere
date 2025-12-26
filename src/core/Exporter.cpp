#include "Exporter.hpp"
#include <SFML/Graphics/Image.hpp>

namespace core {

Exporter::Exporter() {
}

sf::Color Exporter::alphaBlend(sf::Color dst, sf::Color src) const {
    if (src.a == 0) {
        return dst;
    }
    if (src.a == 255) {
        return src;
    }
    
    float srcAlpha = src.a / 255.0f;
    float dstAlpha = dst.a / 255.0f;
    float outAlpha = srcAlpha + dstAlpha * (1.0f - srcAlpha);
    
    if (outAlpha < 0.001f) {
        return sf::Color::Transparent;
    }
    
    // Properly blend each channel with high precision
    float outR = (src.r * srcAlpha + dst.r * dstAlpha * (1.0f - srcAlpha)) / outAlpha;
    float outG = (src.g * srcAlpha + dst.g * dstAlpha * (1.0f - srcAlpha)) / outAlpha;
    float outB = (src.b * srcAlpha + dst.b * dstAlpha * (1.0f - srcAlpha)) / outAlpha;
    
    return sf::Color(
        static_cast<uint8_t>(outR + 0.5f),
        static_cast<uint8_t>(outG + 0.5f),
        static_cast<uint8_t>(outB + 0.5f),
        static_cast<uint8_t>(outAlpha * 255.0f + 0.5f)
    );
}

sf::Image Exporter::composite(const Document& document) {
    uint32_t width = document.getWidth();
    uint32_t height = document.getHeight();
    
    // Validate dimensions
    if (width == 0 || height == 0) {
        return sf::Image(sf::Vector2u(1, 1));
    }
    
    // Create transparent background (sf::Image initializes to transparent by default)
    sf::Image output(sf::Vector2u(width, height));
    
    // Composite each visible layer from bottom to top
    const auto& layers = document.getLayers();
    for (const auto& layer : layers) {
        if (!layer->isVisible()) continue;
        
        const auto& layerImage = layer->getImage();
        uint8_t layerOpacity = layer->getOpacity();
        
        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {
                sf::Color layerPixel = layerImage.getPixel(sf::Vector2u(x, y));
                
                // Apply layer opacity
                layerPixel.a = static_cast<uint8_t>((layerPixel.a * layerOpacity) / 255);
                
                // Skip fully transparent pixels
                if (layerPixel.a == 0) continue;
                
                // Blend onto output
                sf::Color outPixel = output.getPixel(sf::Vector2u(x, y));
                output.setPixel(sf::Vector2u(x, y), alphaBlend(outPixel, layerPixel));
            }
        }
    }
    
    return output;
}

bool Exporter::savePNG(const Document& document, const std::string& filepath) {
    sf::Image output = composite(document);
    return output.saveToFile(filepath);
}

bool Exporter::saveJPG(const Document& document, const std::string& filepath) {
    sf::Image output = composite(document);
    
    // JPG doesn't support alpha, composite onto white background
    sf::Image jpgOutput(output.getSize());
    for (uint32_t y = 0; y < output.getSize().y; ++y) {
        for (uint32_t x = 0; x < output.getSize().x; ++x) {
            sf::Color pixel = output.getPixel(sf::Vector2u(x, y));
            
            // Composite onto white with alpha
            float alpha = pixel.a / 255.0f;
            uint8_t r = static_cast<uint8_t>(pixel.r * alpha + 255 * (1.0f - alpha));
            uint8_t g = static_cast<uint8_t>(pixel.g * alpha + 255 * (1.0f - alpha));
            uint8_t b = static_cast<uint8_t>(pixel.b * alpha + 255 * (1.0f - alpha));
            
            jpgOutput.setPixel(sf::Vector2u(x, y), sf::Color(r, g, b, 255));
        }
    }
    
    return jpgOutput.saveToFile(filepath);
}

bool Exporter::saveBMP(const Document& document, const std::string& filepath) {
    sf::Image output = composite(document);
    return output.saveToFile(filepath);
}

} // namespace core

