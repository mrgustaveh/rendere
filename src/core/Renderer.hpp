#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Document.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace core {

class Renderer {
    public:
        Renderer();
        
        void render(const Document& document, sf::RenderTarget& target);
};

} // namespace core

#endif // RENDERER_HPP