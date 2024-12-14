# MiniRayX: A Compact Ray Tracer with MiniLibX

MiniRayX is a simple yet powerful ray tracing program built with MiniLibX, designed to generate stunning 3D computer graphics. This project serves as an introduction to the fascinating world of ray tracing, allowing you to create simple yet impressive computer-generated images.

## 🌟 Features

- Implements basic ray tracing techniques
- Supports multiple geometric objects: spheres, planes, and cylinders
- Handles ambient and diffuse lighting
- Applies translations and rotations to objects, lights, and cameras
- Reads scene descriptions from .rt files
- Renders images in a resizable window

## 🚀 Getting Started

### Prerequisites

- C compiler (gcc recommended)
- MiniLibX library
- Math library

### Installation

1. Clone the repository:
```bash
git clone https://github.com/48k483x/miniRayX.git
```
2. Navigate to the project directory:
```bash
cd MiniRayX
```
3. Compile the project:
```bash
make re
```
### Usage

Run the program with a scene file as an argument:
```bash
./miniRT scenes/scene.rt
```
## 📐 Supported Objects

- Sphere (sp)
- Plane (pl)
- Cylinder (cy)

## 🎨 Scene File Format

Scene files use the .rt extension and follow this format:

- Ambient lighting: `A 0.2 255,255,255`
- Camera: `C -50.0,0,20 0,0,1 70`
- Light: `L -40.0,50.0,0.0 0.6 10,0,255`
- Sphere: `sp 0.0,0.0,20.6 12.6 10,0,255`
- Plane: `pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`
- Cylinder: `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`

## 🎮 Controls

- ESC: Close the window and exit the program
- Red cross: Close the window and exit the program

Happy ray tracing! 🌟
