# OpenGL Playground

This repository is my personal sandbox for learning modern **OpenGL** using **C++**, **GLFW**, and **GLAD**.  
Right now it’s focused on getting comfortable with the fundamentals:

- Creating a window and OpenGL context  
- Setting up VBOs / VAOs  
- Writing basic shaders  
- Rendering simple shapes  

## 🎯 Goal

The long-term goal of this project is to explore **particle effects** and small visual simulations — things like:

- fire / sparks  
- falling sand  
- flowing water  
- materials interacting (e.g., fire burning wood, water putting out fire)  

Basically, a small physics-toy or “falling sand” style environment built with OpenGL.

## 📚 What I’m Learning Along the Way

- How GPU buffers work (VBOs, VAOs, EBOs)  
- How shaders process vertex + fragment data  
- How to animate things frame-by-frame  
- Uploading CPU simulation data to the GPU  
- Rendering particles using points or textured quads  
- Eventually, post-processing (bloom, blending, etc.)

## 🛠️ Tech Stack

- **C++17**
- **OpenGL 4.1 (macOS maximum)**
- **GLFW** – window + input  
- **GLAD** – OpenGL function loader  
- **CMake** – build system  
- **VS Code** – editor

## 🚧 Status

Currently at the “learn the basics” stage — drawing simple geometry, setting up buffers, and getting the render loop working.  
Particle effects will come once the foundational pieces are solid.

## 📌 Future Ideas

- Simple particle engines (CPU + GPU variants)  
- Falling-sand simulation grid  
- Fire / smoke simulation  
- Material reactions (fire vs wood, water vs fire, sand piling, etc.)  
- Small real-time demos to visualize effects

---

Feel free to follow along or fork this if you’re also learning OpenGL!
