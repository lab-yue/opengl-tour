#!/bin/bash

build(){
    g++ -I stb\
        -I imgui\
        -I imgui/examples\
        -o bin/app\
        -L /usr/local/lib64\
        -lGL\
        -lglfw\
        -lGLEW\
        imgui/*.cpp\
        imgui/examples/imgui_impl_glfw.cpp\
        imgui/examples/imgui_impl_opengl3.cpp\
        src/*.cpp
}

run(){
    MESA_GL_VERSION_OVERRIDE=4.4\
    LD_LIBRARY_PATH=/usr/local/lib64\
    ./bin/app
}


case $1 in 
    "build") build;;
    "run") run;;
    *) build && run;;
esac
