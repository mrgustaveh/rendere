### The Goal
A high-performance 2D image rendering and compositing tool

### Painting
- **Layer system** > with composition and blending
- **Partial updating** > only redraw what changed
- **Decorations/overlays** > UI elements like selection outlines, guides, etc.
- **Index/palette mode** > support alongside full color

### Tools
- **Brush tool** > showing stroke management, pressure handling from tablets
- **Selection tool** > at least rectangular selection

### Multiple Document Support
- Handle multiple images/documents open at once
- Efficient memory and resource management

### Threading Model
- Design threading architecture for maximum performance

### Color Space
- RGB

### Windowing & Input
- **Window management**
- **Input handling** > mouse, keyboard support

### Build
```bash
cmake -B build
```

```bash
cmake --build build
```
