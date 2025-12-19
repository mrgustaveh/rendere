#include "Document.hpp"

namespace core {
    
Document::Document(uint32_t width, uint32_t height)
    : m_width(width)
    , m_height(height)
{
}

Layer* Document::createLayer(const std::string& name) {
    auto newLayer = std::make_unique<Layer>(m_width, m_height, name);
    Layer* ptr = newLayer.get();
    m_layers.push_back(std::move(newLayer));
    return ptr;
}

void Document::addLayer(std::unique_ptr<Layer> layer) {
    if (layer) {
        m_layers.push_back(std::move(layer));
    }
}

const std::vector<std::unique_ptr<Layer>>& Document::getLayers() const {
    return m_layers;
}

uint32_t Document::getWidth() const {
    return m_width;
}

uint32_t Document::getHeight() const {
    return m_height;
}

}

