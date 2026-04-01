# Kinetic Desktop Environment (Core)

Kinetic is a lightweight, architecturally minimalist Linux Desktop Environment built from the ground up. It leverages the power of **wlroots** and **Wayland** to provide a high-performance, fluid user experience designed with a "less is more" industrial aesthetic.

## 🏗️ Current Architecture
The core is currently a custom Wayland compositor that manages:
- **Fixed Layout**: A dedicated 1920x1200 logical workspace.
- **Modern Input**: Fully compatible with `wlroots 0.17+` event handling.
- **Hybrid Rendering**: Supports both GLES2 hardware acceleration and Pixman software fallback for virtualized environments (WSL).

## 🛠️ Tech Stack
- **Language**: Pure C (C11)
- **Framework**: wlroots (Unstable API)
- **Protocol**: Wayland
- **Frontend**: Qt-based UI components (Panel/Shell)

## 🚀 Getting Started
To compile and run the compositor:
```bash
gcc -o kinetic-compositor main.c input.c -DWLR_USE_UNSTABLE $(pkg-config --cflags --libs wlroots wayland-server)
./kinetic-compositor
