cmake_minimum_required(VERSION 3.28)
project(RenderE LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(ImGui)

set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable(rendere 
    src/main.cpp 
    src/app/Application.cpp
    src/core/Layer.cpp
    src/core/Document.cpp
    src/core/Renderer.cpp
    src/tools/BrushTool.cpp
    src/gui/GuiManager.cpp
    src/gui/Toolbar.cpp
    src/gui/LayerPanel.cpp
)
target_compile_features(rendere PRIVATE cxx_std_17)
target_link_libraries(rendere PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)
