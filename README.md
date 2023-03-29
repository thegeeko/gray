# Gray

a raytracer I made following "raytracing in one weekend" .. it creates an image and use opengl to create a texture with the image and display it in ImGui image window

![preview](/preview.png)

## build

it builds on linux using GCC and CLANG .. it depends on glfw .. so make sure to install glfw from ur package manager

instructions for arch based distros

```bash
pacman -S glfw-x11 # for x11
pacman -S glfw-wayland # for wayland

git clone git@github.com:thegeeko/gray
cd gray
mkdir build && cd build
cmake ..
cmake --build
```

## dependencies

- glfw
- imgui
