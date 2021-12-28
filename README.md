# Shady
Shady is a simple glsl writing environment created for rapid shader development. I created Shady for educational reasons (graphics programming is cool) and use it
as a tool in learning shader programming.

## Functionality

|Feature|Key|
|-|-|
|Live reloading shaders| F5 |

## Compiling
### Dependencies
- [premake5](https://premake.github.io/)
- [GLFW](glfw.org)
- [glad](https://glad.dav1d.de/)

### Linux
[building]
- Install [GLFW](glfw.org) development binaries
- Run `premake5 gmake` in project directory
- Run `make all` in project directory

[cleanup]
- Run `make clean` in project directory

### Windows
[building]
- Run `premake5 vc2019` in project directory
- Open `*.sln` file with `Visual Studio (Community/Entiprise)`
<!-- - Weep -->


## Todo
- Time Controls
- Keyboard Input
- Load shaders by folder
- Shader management UI
- Add uniforms at runtime (through UI)
- Cross-Platform (Windows, Linux)
- Keyboard Input Uniforms
- ...
