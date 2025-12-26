#ifndef TOOLBAR_HPP
#define TOOLBAR_HPP

#include <memory>
#include <string>
#include "../tools/Tool.hpp"
#include "../core/Document.hpp"

namespace gui {

class Toolbar {
public:
    static void render(std::unique_ptr<tools::Tool>& activeTool, core::Document* document = nullptr);

private:
    static std::string s_lastExportStatus;
    static float s_exportStatusTime;
};

} // namespace gui

#endif // TOOLBAR_HPP