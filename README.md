# RenderE

A high-performance 2D image rendering and compositing application built with C++17, SFML 3.0, and ImGui.

## Features

- **Layer System** - Create and manage multiple layers with visibility and opacity control
- **Brush Tool** - Paint with customizable color, size, and smooth stroke interpolation
- **Eraser Tool** - Erase pixels with transparency support
- **Selection Tool** - Create rectangular selections to restrict painting to specific areas
- **Export** - Save your artwork as PNG (with transparency), JPG, or BMP
- **Real-time Rendering** - GPU-accelerated composition of all visible layers
- **Responsive UI** - ImGui-based toolbar and layer panel

## Build

### Requirements

- CMake 3.28+
- C++17 compatible compiler
- Linux/macOS/Windows

### Build Instructions

```bash
# Configure
cmake -B build

# Build
cmake --build build

# Run
./build/bin/rendere
```

Dependencies are automatically fetched via CMake:

- **SFML 3.0.2** - Graphics and windowing
- **ImGui v1.91.1** - User interface
- **ImGui-SFML v3.0** - SFML integration for ImGui
- **tinyfiledialogs** - File dialogs for exports

## Usage

### Tools

- **Brush** - Click and drag to paint with the current color
- **Eraser** - Click and drag to erase (paint with transparency)
- **Selection** - Click and drag to create a rectangular selection. Painting is restricted to the selected area.

### Exporting

Click the **Export** section in the Tools panel to save your artwork:

- **PNG** - Preserves transparency and layer blending
- **JPG** - Composites to white background (no transparency)
- **BMP** - Uncompressed bitmap format

### Toolbar

- Adjust brush size with the size slider (1-100px)
- Pick colors with the color picker
- View layer properties in the Layers panel

## Architecture

The codebase follows a strict namespace-based layered architecture:

- **`app/`** - Application entry point and event loop
- **`core/`** - Data model (Document, Layer, Selection, Renderer, Exporter)
- **`tools/`** - Tool implementations (Brush, Selection)
- **`gui/`** - ImGui UI components (Toolbar, LayerPanel)

For detailed architecture documentation, see [.github/copilot-instructions.md](.github/copilot-instructions.md).

## Known Limitations

- No undo/redo system yet
- Selection tool only supports rectangles
- No layer blending modes (only opacity)
- No rotation or transformation tools

## Development

For AI agent instructions and development guidelines, see [.github/copilot-instructions.md](.github/copilot-instructions.md).

### Testing

Manual testing only—verify features in the GUI.

### Build Artifacts

- Executable: `build/bin/rendere`
- ImGui state saved to: `build/bin/imgui.ini`
