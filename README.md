
# Shady
Shady is a simple glsl writing environment created for rapid shader development.

## Compiling
### Dependencies
- [premake5](https://premake.github.io/)
- [GLFW](glfw.org)
- [glad](https://glad.dav1d.de/)

### Linux
[setup]
- Download premake executable [premake](https://premake.github.io/download/)
[building]
- Install [GLFW](glfw.org) development binaries
- Run `premake5 gmake2` in project directory
- Run `make all` in project directory

[cleanup]
- Run `make clean` in project directory

### Windows
[building]
- Run `premake5 vs2019` in project directory
- Open `*.sln` file with `Visual Studio (Community/Entiprise)`
<!-- - Weep -->


## Showcase
> ![3 ray traced spheres, left dialetric, middle normal, right metal. Adapted from ray tracing in one weekend (book 1)](images/rtweekend_1.gif)
> 
> examples/rtw1

> ![Program Flow](images/v0.1.gif)
