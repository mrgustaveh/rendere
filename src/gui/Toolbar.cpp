#include "Toolbar.hpp"
#include "../tools/BrushTool.hpp"
#include "../tools/SelectionTool.hpp"
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
             } else {
                 // If not brush, switch to brush first then set to transparent
                 // Or we could have a dedicated EraserTool, but configuring brush works
                 auto newBrush = std::make_unique<tools::BrushTool>();
                 newBrush->setColor(sf::Color::Transparent);
                 activeTool = std::move(newBrush);
             }
        }
        ImGui::SameLine();
        if (ImGui::Button("Selection")) {
            if (!dynamic_cast<tools::SelectionTool*>(activeTool.get())) {
                activeTool = std::make_unique<tools::SelectionTool>();
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
        } else if (dynamic_cast<tools::SelectionTool*>(activeTool.get())) {
            ImGui::Text("Selection Settings");
            ImGui::TextWrapped("Click and drag to select an area. Painting will be restricted to this area.");
        } else {
            ImGui::Text("No active tool settings");
        }
    }
    ImGui::End();
}

} // namespace gui
