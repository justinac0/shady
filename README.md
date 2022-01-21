
# Shady
Shady is a simple glsl writing environment created for rapid shader development.

I am a big fan of [ShaderToy](https://www.shadertoy.com/) and the  impressive shaders that people have made there. I quite like graphics programming
and created Shady to learn more in-depth how tools like
ShaderToy work.

## Functionality

run `./build/[development/production]/shady ./examples/[shader_folder]`

|Feature|Key|
|-|-|
|Live reloading shaders| F5       |
|Freeze Time (Pausing) | Spacebar |
|<b>(Only while Paused)</b>||
|Move time forward| D|
|Move time backwards| A|

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
- Run `premake5 vs2019` in project directory
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

## Showcase
> ![3 raytraceced spheres, left dialetric, middle normal, right metal](images/rtweekend_1.gif)
> 
> captured from examples/rtweekened_1
