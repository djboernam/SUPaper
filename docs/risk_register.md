# SUPaper Risk Register

## Overview

This risk register captures key product, technical, and integration risks for SUPaper V0.1 and the broader roadmap.

## Risk Register

| ID | Risk | Likelihood | Impact | Mitigation |
|----|------|------------|--------|-----------|
| R1 | SketchUp integration constraints are stricter than expected | Medium | High | Use bridge interface and file-reference mode as default |
| R2 | Scope creep extends beyond V0.1 | High | High | Strict milestone gates and feature limits |
| R3 | Geometry engine becomes too complex too early | High | High | Start with basic primitives before advanced CAD editing |
| R4 | PDF/export pipeline depends on screen rendering | Medium | High | Use separate vector export pipeline |
| R5 | Ruby extension API becomes unsafe or unstable | Medium | High | Manifest-based loading and explicit permissions |
| R6 | File format becomes hard to evolve | Medium | Medium | Versioned project schema and clean serialization layer |
| R7 | UI becomes too large before core stability | Medium | Medium | Keep V0.1 UI minimal and focused |
| R8 | DWG/DXF import/export is attempted too early | Medium | High | Defer until geometry model and export pipeline are stable |
| R9 | Native app cannot support the required rendering performance | Low | High | Use vector-first design and gradual performance profiling |
| R10 | Different SketchUp versions create compatibility issues | Medium | High | Abstraction layer and optional live bridge |

## Priority Risks for V0.1

1. SketchUp bridge strategy
2. geometry scope control
3. Ruby API safety
4. document serialization stability
5. export pipeline design

## Mitigation Strategy

### Product mitigation

- Keep V0.1 focused on documentation and model viewing
- Delay advanced CAD editing features until architecture stabilizes

### Technical mitigation

- Separate app logic from render logic
- Keep the Ruby API minimal and explicit
- Build bridge interfaces before the UI

### Integration mitigation

- Prefer file-based SKP references as the default integration method
- Keep live SketchUp bridge optional and version-aware

## Exit Criteria

The risk plan should be considered successful once:
- the document model is stable
- the Ruby API is documented and safe
- the SketchUp bridge supports a basic workflow
- rendering and export are reliable
- the first .exe build is possible on Windows

## Summary

SUPaper can succeed if it controls scope, isolates the bridge layer, and keeps the core document engine authoritative. Most project failure risks happen when the team moves into feature breadth before the architecture is stable.
