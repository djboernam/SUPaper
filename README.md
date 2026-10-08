# SUPaper

A native Windows 2D documentation and layout application for SketchUp workflows.

**Status:** V0.1 Architecture & Development

SUPaper is a professional-grade documentation tool designed to work seamlessly with SketchUp models. It enables users to create print-ready sheets, generate drawing sets, manage viewports, and automate documentation workflows through a Ruby-based extension API.

## Features (V0.1)

- Native Windows application (C++/Qt)
- Project and sheet management
- SketchUp model reference support
- Viewport placement and scaling
- Basic 2D geometry (lines, rectangles, text)
- Dimension and annotation tools
- Layer management
- PDF export (vector-based)
- Ruby extension framework
- Full undo/redo support

## Architecture

```
SUPaper
├── Core (Document engine)
├── Rendering (2D/PDF)
├── SketchUp Integration
├── Ruby API Layer
├── UI (Qt 6)
└── Extension System
```

## Quick Start

### Building from Source

```powershell
# Prerequisites
# - Visual Studio 2022 (C++ workload)
# - Qt 6.x
# - CMake 3.20+
# - Ruby 3.0+

cd SUPaper
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Running

```powershell
.\SUPaper.exe
```

## Development Roadmap

- **V0.1** — Core document engine, basic geometry, SketchUp references
- **V0.2** — Advanced drafting tools (trim, extend, fillet, chamfer)
- **V0.3** — Documentation features (dimensions, leaders, hatching)
- **V0.4** — Full SketchUp integration and sync
- **V0.5** — Ruby API and extension system
- **V0.6** — Schedules, tables, drawing sets
- **V0.7** — DWG/DXF import/export
- **V0.8** — Automation and AI integration
- **V1.0** — Production release

## Documentation

- [Architecture](docs/architecture.md)
- [Ruby API](docs/ruby_api.md)
- [SketchUp Integration](docs/sketchup_integration.md)
- [Contributing](CONTRIBUTING.md)

## License

MIT License - see LICENSE file

## Author

David Boerner (@djboernam)
