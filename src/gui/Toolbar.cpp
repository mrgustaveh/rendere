#include "Toolbar.hpp"
#include "../tools/BrushTool.hpp"
#include "../tools/SelectionTool.hpp"
#include "../core/Exporter.hpp"
#include <imgui.h>
#include <tinyfiledialogs.h>

namespace gui {

// Static members for export status feedback
std::string Toolbar::s_lastExportStatus = "";
float Toolbar::s_exportStatusTime = 0.0f;

void Toolbar::render(std::unique_ptr<tools::Tool>& activeTool, core::Document* document) {
    if (ImGui::Begin("Tools")) {
        if (ImGui::Button("Brush")) {
             if (!dynamic_cast<tools::BrushTool*>(activeTool.get())) {
                 if (activeTool) {
                     activeTool->onDeactivate();
                 }
                 auto newTool = std::make_unique<tools::BrushTool>();
                 newTool->onActivate();
                 activeTool = std::move(newTool);
             }
        }
        ImGui::SameLine();
        if (ImGui::Button("Eraser")) {
             if (auto* brush = dynamic_cast<tools::BrushTool*>(activeTool.get())) {
                 brush->setColor(sf::Color::Transparent);
             } else {
                 if (activeTool) {
                     activeTool->onDeactivate();
                 }
                 auto newBrush = std::make_unique<tools::BrushTool>();
                 newBrush->setColor(sf::Color::Transparent);
                 newBrush->onActivate();
                 activeTool = std::move(newBrush);
             }
        }
        ImGui::SameLine();
        if (ImGui::Button("Selection")) {
            if (!dynamic_cast<tools::SelectionTool*>(activeTool.get())) {
                if (activeTool) {
                    activeTool->onDeactivate();
                }
                auto newTool = std::make_unique<tools::SelectionTool>();
                newTool->onActivate();
                activeTool = std::move(newTool);
            }
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Export", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button("Export as PNG")) {
                if (document) {
                    const char* filters[1] = {"*.png"};
                    const char* filepath = tinyfd_saveFileDialog(
                        "Export as PNG",
                        "image.png",
                        1,
                        filters,
                        nullptr
                    );
                    
                    if (filepath) {
                        core::Exporter exporter;
                        if (exporter.savePNG(*document, filepath)) {
                            s_lastExportStatus = "PNG exported successfully!";
                            s_exportStatusTime = 3.0f;
                        } else {
                            s_lastExportStatus = "Failed to export PNG";
                            s_exportStatusTime = 3.0f;
                        }
                    }
                }
            }

            if (ImGui::Button("Export as JPG")) {
                if (document) {
                    const char* filters[1] = {"*.jpg"};
                    const char* filepath = tinyfd_saveFileDialog(
                        "Export as JPG",
                        "image.jpg",
                        1,
                        filters,
                        nullptr
                    );
                    
                    if (filepath) {
                        core::Exporter exporter;
                        if (exporter.saveJPG(*document, filepath)) {
                            s_lastExportStatus = "JPG exported successfully!";
                            s_exportStatusTime = 3.0f;
                        } else {
                            s_lastExportStatus = "Failed to export JPG";
                            s_exportStatusTime = 3.0f;
                        }
                    }
                }
            }

            if (ImGui::Button("Export as BMP")) {
                if (document) {
                    const char* filters[1] = {"*.bmp"};
                    const char* filepath = tinyfd_saveFileDialog(
                        "Export as BMP",
                        "image.bmp",
                        1,
                        filters,
                        nullptr
                    );
                    
                    if (filepath) {
                        core::Exporter exporter;
                        if (exporter.saveBMP(*document, filepath)) {
                            s_lastExportStatus = "BMP exported successfully!";
                            s_exportStatusTime = 3.0f;
                        } else {
                            s_lastExportStatus = "Failed to export BMP";
                            s_exportStatusTime = 3.0f;
                        }
                    }
                }
            }

            // Show export status message
            if (s_exportStatusTime > 0.0f) {
                ImGui::TextColored(
                    s_lastExportStatus.find("successfully") != std::string::npos ?
                    ImVec4(0.2f, 0.8f, 0.2f, 1.0f) :  // Green for success
                    ImVec4(0.8f, 0.2f, 0.2f, 1.0f),    // Red for failure
                    "%s", s_lastExportStatus.c_str()
                );
                s_exportStatusTime -= ImGui::GetIO().DeltaTime;
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
