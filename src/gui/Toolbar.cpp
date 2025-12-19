#include "Toolbar.hpp"
#include "../tools/BrushTool.hpp"
#include <imgui.h>

namespace gui {

void Toolbar::render(std::unique_ptr<tools::Tool>& activeTool) {
    if (ImGui::Begin("Tools")) {
        if (ImGui::Button("Brush")) {
             if (!dynamic_cast<tools::BrushTool*>(activeTool.get())) {
                 activeTool = std::make_unique<tools::BrushTool>();
             }
        }
        ImGui::SameLine();
        if (ImGui::Button("Eraser")) {
             if (auto* brush = dynamic_cast<tools::BrushTool*>(activeTool.get())) {
                 brush->setColor(sf::Color::Transparent);
             }
        }

        ImGui::Separator();

        if (auto* brush = dynamic_cast<tools::BrushTool*>(activeTool.get())) {
            ImGui::Text("Brush Settings");
            
            int size = brush->getSize();
            if (ImGui::SliderInt("Size", &size, 1, 100)) {
                brush->setSize(size);
            }

            sf::Color c = brush->getColor();
            float color[4] = { c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f };
            if (ImGui::ColorEdit4("Color", color)) {
                brush->setColor(sf::Color(
                    static_cast<uint8_t>(color[0] * 255),
                    static_cast<uint8_t>(color[1] * 255),
                    static_cast<uint8_t>(color[2] * 255),
                    static_cast<uint8_t>(color[3] * 255)
                ));
            }
        } else {
            ImGui::Text("No active tool settings");
        }
    }
    ImGui::End();
}

} // namespace gui

