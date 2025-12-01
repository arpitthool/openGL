# OpenGL Project

A 3D OpenGL application that renders a textured pyramid with lighting (Specular, Ambient, Diffused). The pyramid rotates continuously, and a small cube represents the light source.

[Screencast from 12-01-2025 02:56:53 PM.webm](https://github.com/user-attachments/assets/650632c7-8e3d-43c1-a4ff-d77c65d0928c)

## Core Architecture
- OpenGL 4.6 (Core Profile)
- GLFW for windowing and input
- GLAD for OpenGL function loading
- GLM for math (matrices, vectors)
- STB Image for texture loading

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
cd build
./main
```

## Controls

### Camera Movement
- **W** - Move forward
- **A** - Move left
- **S** - Move backward
- **D** - Move right
- **Space** - Move up
- **Left Control** - Move down

### Camera Rotation
- **Left Arrow** - Rotate camera left
- **Right Arrow** - Rotate camera right
