#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include <memory>
#include "../tools/Tool.hpp"

namespace gui {

class Toolbar {
public:
    static void render(std::unique_ptr<tools::Tool>& activeTool);
};

} // namespace gui

#endif // TOOLBAR_HPP