# M777 Howitzer Prototype Simulation

## Contributors

- **Samuel Casellas**
- **Andrew Swayze**
- **Isaac Radford**

## Description

This program simulates firing the M777 howitzer 15mm artillery piece.

## Usage

To run the simulation, compile and run the program. Once running, the simulation can be interacted with using the following controls:

- **up arrow** and **down arrow** to adjust the angle of the howitzer.
- **left arrow** and **right arrow** to adjust the power of the shot.
- **space** to fire the howitzer.

## Implementation Details

The simulation is implemented using C++ and OpenGL. The `uiInteract` and `uiDraw` libraries are used for graphics rendering, and the `ground`, `bullet`, `howitzer`, `position`, and `physics` modules are used to simulate the movement of the howitzer, bullets, and ground. The simulation is organized into a `Demo` class, which contains all of the state and logic needed to simulate the firing of the howitzer. The `callBack` function is called repeatedly by the graphics engine to draw each frame of the simulation and update its state based on user input.

## Known Issues

The program does not fully implement the assignment, as it has difficulty getting the bullet to hit the ground. This is a known issue that the developers were unable to resolve within the timeframe of the assignment.
