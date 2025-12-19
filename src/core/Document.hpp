#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "Layer.hpp"
#include <vector>
#include <memory>
#include <string>

namespace core {

class Document {
    public:
        Document(uint32_t width, uint32_t height);

        Layer* createLayer(const std::string& name = "Layer");
        void addLayer(std::unique_ptr<Layer> layer);
        
        const std::vector<std::unique_ptr<Layer>>& getLayers() const;
        
        uint32_t getWidth() const;
        uint32_t getHeight() const;

    private:
        uint32_t m_width;
        uint32_t m_height;
        std::vector<std::unique_ptr<Layer>> m_layers;
};
} // namespace core

#endif // DOCUMENT_HPP