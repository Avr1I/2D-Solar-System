# 2D Solar System

A 2D solar system simulation written in C++ using OpenGL, GLFW, and GLUT. The Sun and the eight planets are animated in real time following a simplified gravitation model, with each planet's speed displayed on screen.

## Overview

- Physics simulation based on universal gravitation (the Sun's pull on each planet)
- 2D rendering of celestial bodies (Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune)
- Randomly generated starfield background
- Real-time display of each planet's speed (in km/s) in the top-right corner
- Orbit trail rendering (present in the code, disabled by default)

## Requirements

The project is set up for **Visual Studio** (`.sln` / `.vcxproj` files) and targets **Windows**.

Dependencies (installed via NuGet, see `packages.config`):

| Library | Version |
|---|---|
| freeglut | 3.2.2 (v140) |
| GLEW | 1.12.0 (v140) |
| GLFW | 3.4.0 |

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Avr1I/2D-Solar-System.git
   ```
2. Open `Solar System.sln` in Visual Studio.
3. Restore the NuGet packages (Visual Studio usually does this automatically when the project opens; otherwise, right-click the solution → **Restore NuGet Packages**).
4. Build and run (F5) using the **x86** or **x64** configuration, depending on the installed packages.

## Usage

Once launched, the application opens a window showing the animated solar system. No keyboard or mouse interaction is required: the simulation runs automatically and each planet's speed is displayed live on screen.

## Project structure

```
2D-Solar-System/
├── main.cpp                     # Entry point, simulation and render loop
├── Solar System.sln             # Visual Studio solution
├── Solar System.vcxproj         # Project file
├── Solar System.vcxproj.filters
├── Solar System.vcxproj.user
└── packages.config              # NuGet dependencies
```

## How it works

Each planet is represented by a `planet` class storing its position, velocity, mass, radius, and color. On every frame:

1. The gravitational force exerted by the Sun on each planet is computed.
2. The planet's acceleration and velocity are updated accordingly.
3. The new position is applied and the body is redrawn as a filled circle (via `GL_TRIANGLE_FAN`).

## Known limitations

- Distance, size, and mass scales are artistic choices, not physically accurate.
- Orbit trail rendering (`Lesorbites` method) is implemented but commented out in the main loop.
- The project depends on Windows/Visual Studio; no cross-platform build setup (CMake, etc.) is provided.
