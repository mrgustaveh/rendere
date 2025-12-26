# RenderE - AI Agent Instructions

## Project Overview

**RenderE** is a 2D image rendering and compositing application built with C++17, SFML 3.0, and ImGui. It's a high-performance painting tool supporting layers, selection tools, and brush-based drawing.

## Architecture

### Layered Component Model

The codebase follows a strict namespace-based layer architecture:

- **`app/Application`** - Entry point & event loop orchestration. Manages window lifecycle, ties together Document, Renderer, Tools, and GUI.
- **`core/`** - Data & rendering layer:
  - `Document` - State container for width, height, layer stack, active layer, and selection
  - `Layer` - Pixel data storage (SFML `Image` + `Texture` for GPU access)
  - `Renderer` - Composite layer stack to output (renders all visible layers in order)
  - `Selection` - Mask-based selection state (respects document bounds)
  - `MathUtils` - Utility functions like `drawLine()` for rasterization
- **`tools/`** - Tool abstraction for user interactions:
  - `Tool` (base) - Virtual interface: `onPress()`, `onDrag()`, `onRelease()` + activate/deactivate hooks
  - `BrushTool` - Pixel painting with color, size, line interpolation
  - `SelectionTool` - Rectangular selection creation
- **`gui/`** - ImGui-SFML UI layer:
  - `GuiManager` - Event routing, ImGui frame updates
  - `Toolbar` - Tool selection, brush settings, color picker
  - `LayerPanel` - Layer visibility, opacity, add/delete/reorder

### Key Data Flow

1. **Input** → `Application::handleEvents()` → active `Tool::onPress/Drag/Release()`
2. **Tool modifies** → `Document` (pixel changes via `Layer::setPixel()`, or selection changes)
3. **GUI interaction** → `GuiManager` → modifies brush size/color or layer properties
4. **Rendering** → `Renderer::render()` → composes all visible layers in order to SFML RenderTarget

**Critical Pattern**: Tools receive mutable `Document&` and directly modify pixel data. Selection acts as a mask—always check `selection.contains(x, y)` before painting.

## Build & Development

```bash
# Configure (uses FetchContent for SFML 3.0.2, ImGui v1.91.1, ImGui-SFML v3.0)
cmake -B build

# Build
cmake --build build

# Run
./build/bin/rendere
```

**FetchContent Strategy**: All three major dependencies are fetched from remote repos. Rebuild from scratch if dependency versions need updating in CMakeLists.txt. No local vendor directory.

## Common Patterns & Conventions

### Pixel Data Access

- Layers store pixel data in `sf::Image` for CPU access; always call `layer->updateTexture()` after batches of `setPixel()` calls to sync GPU texture.
- Out-of-bounds pixel access is safe (not painted), but check bounds explicitly for performance.

### Tool Implementation Template

```cpp
// In BrushTool::onDrag, interpolate between lastPos and current pos:
core::drawLine(m_lastPos.x, m_lastPos.y, pos.x, pos.y,
    [this, &document](int x, int y) { paintAt({x, y}, document); }
);
```

Use lambda callbacks in `MathUtils::drawLine()` for line rasterization—avoids direct vector accumulation.

### Selection Awareness

All painting operations must check `document.getSelection().contains(x, y)` before modifying pixels. If no selection is active, assume full canvas is selected.

### ImGui Integration Points

- `GuiManager::processEvent()` - Must receive SFML events for ImGui input handling
- `GuiManager::update()` - Called each frame with deltaTime for ImGui state
- `GuiManager::render()` - Handles ImGui rendering within SFML RenderTarget

## Important Files to Know

| File                                               | Purpose                                                                  |
| -------------------------------------------------- | ------------------------------------------------------------------------ |
| [CMakeLists.txt](CMakeLists.txt)                   | Dependency fetch & build config; update here for library version changes |
| [src/app/Application.hpp](src/app/Application.hpp) | Main loop, event dispatch—modify for new core systems                    |
| [src/core/Document.hpp](src/core/Document.hpp)     | Document API—all persistent state flows through here                     |
| [src/core/Layer.hpp](src/core/Layer.hpp)           | Pixel storage & texture management; understand Image/Texture lifecycle   |
| [src/tools/Tool.hpp](src/tools/Tool.hpp)           | Tool base contract—all tools inherit & override press/drag/release       |
| [src/tools/BrushTool.cpp](src/tools/BrushTool.cpp) | Reference implementation for tool logic + line interpolation             |
| [src/gui/GuiManager.hpp](src/gui/GuiManager.hpp)   | GUI event routing & ImGui setup—modify for new panels                    |

## Testing & Debugging

- **Manual testing only** - No test framework; verify feature in the GUI.
- **Visual debugging** - Use ImGui overlay panels to inspect layer state, selection bounds, brush parameters.
- **Build artifacts** - Executable at `build/bin/rendere`; ImGui state saved to `build/bin/imgui.ini`.

## Namespace Convention

All code is namespaced: `app::`, `core::`, `tools::`, `gui::`. Use FQN (fully qualified names) when referencing across namespaces.

## Guidance for Agents

When implementing features:

1. **Identify the component layer** - Is this UI (GuiManager), tool logic (Tool subclass), document state (Document), or rendering (Renderer)?
2. **Understand data flow** - Trace from event → tool → document → renderer
3. **Test selection masks** - If painting, verify selection is respected
4. **Update textures** - Always call `layer->updateTexture()` after pixel modifications
5. **Respect bounds** - Check document dimensions before accessing layers
6. **ImGui integration** - All UI changes go through GuiManager; coordinate with existing panels
