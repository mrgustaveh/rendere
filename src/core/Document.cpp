#include "Document.hpp"
#include <algorithm>

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
        
        m_activeLayer = ptr;
        
        return ptr;
    }
    
    void Document::addLayer(std::unique_ptr<Layer> layer) {
        if (layer) {
            Layer* ptr = layer.get();
            m_layers.push_back(std::move(layer));
            m_activeLayer = ptr;
        }
    }
    
    const std::vector<std::unique_ptr<Layer>>& Document::getLayers() const {
        return m_layers;
    }
    
    Layer* Document::getActiveLayer() {
        return m_activeLayer;
    }

    const Layer* Document::getActiveLayer() const {
        return m_activeLayer;
    }

    void Document::setActiveLayer(Layer* layer) {
        // Verify layer belongs to us
        for (const auto& l : m_layers) {
            if (l.get() == layer) {
                m_activeLayer = layer;
                return;
            }
        }
    }

    void Document::setActiveLayerIndex(size_t index) {
        if (index < m_layers.size()) {
            m_activeLayer = m_layers[index].get();
        }
    }
    
    uint32_t Document::getWidth() const {
        return m_width;
    }
    
    uint32_t Document::getHeight() const {
        return m_height;
    }
    
} // namespace core
