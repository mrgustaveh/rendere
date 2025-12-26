#include "LayerPanel.hpp"
#include <imgui.h>
#include <string>

namespace gui {

void LayerPanel::render(core::Document& document) {
    if (ImGui::Begin("Layers")) {
        const auto& layers = document.getLayers();
        
        // Buttons
        if (ImGui::Button("New Layer")) {
            document.createLayer("Layer " + std::to_string(layers.size() + 1));
        }

        ImGui::Separator();

        // Layer List (Reverse order so top layer is at top of list)
        for (size_t i = layers.size(); i > 0; --i) {
            auto& layer = layers[i - 1];
            ImGui::PushID(i);
            
            // Visibility Toggle
            bool visible = layer->isVisible();
            if (ImGui::Checkbox("##vis", &visible)) {
                layer->setVisible(visible);
            }
            ImGui::SameLine();

            // Selectable Layer Name
            bool isSelected = (document.getActiveLayer() == layer.get());
            if (ImGui::Selectable(layer->getName().c_str(), isSelected)) {
                document.setActiveLayer(layer.get());
            }

            // Opacity slider for selected layer
            if (isSelected) {
                int opacity = layer->getOpacity();
                if (ImGui::SliderInt("Opacity", &opacity, 0, 255)) {
                    layer->setOpacity(static_cast<uint8_t>(opacity));
                }
            }

            ImGui::PopID();
        }
    }
    ImGui::End();
}

} // namespace gui

