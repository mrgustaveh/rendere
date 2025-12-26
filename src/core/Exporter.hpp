#ifndef EXPORTER_HPP
#define EXPORTER_HPP

#include "Document.hpp"
#include <string>

namespace core {

class Exporter {
public:
    Exporter();
    
    // Export to PNG (supports transparency)
    bool savePNG(const Document& document, const std::string& filepath);
    
    // Export to JPG (no transparency, will composite to white background)
    bool saveJPG(const Document& document, const std::string& filepath);
    
    // Export to BMP
    bool saveBMP(const Document& document, const std::string& filepath);
    
private:
    // Composite all visible layers into a single image
    sf::Image composite(const Document& document);
    
    // Alpha blend src pixel onto dst pixel
    sf::Color alphaBlend(sf::Color dst, sf::Color src) const;
};

} // namespace core

#endif // EXPORTER_HPP
