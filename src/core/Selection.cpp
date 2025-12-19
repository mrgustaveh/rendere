#include "Selection.hpp"

namespace core {

Selection::Selection()
    : m_rect({0, 0}, {0, 0})
    , m_active(false)
{
}

bool Selection::contains(int x, int y) const {
    if (!m_active) return true; // If no selection, everything is "selected" (editable)
                                // Alternatively, if we want strict masking: return false;
                                // Usually in paint apps: No selection = Draw everywhere. 
                                // Specific Selection = Draw only inside.
                                // BUT for "contains", let's be strict: it contains if inside rect.
                                // The caller (Tool) decides policy: "If active && !contains -> skip"
    return m_rect.contains({x, y});
}

void Selection::setRect(const sf::IntRect& rect) {
    m_rect = rect;
    // Normalize rect just in case (width/height positive)
    if (m_rect.size.x < 0) {
        m_rect.position.x += m_rect.size.x;
        m_rect.size.x = -m_rect.size.x;
    }
    if (m_rect.size.y < 0) {
        m_rect.position.y += m_rect.size.y;
        m_rect.size.y = -m_rect.size.y;
    }
    m_active = true;
}

const sf::IntRect& Selection::getRect() const {
    return m_rect;
}

bool Selection::isEmpty() const {
    return !m_active;
}

void Selection::clear() {
    m_active = false;
    m_rect = {{0, 0}, {0, 0}};
}

} // namespace core

