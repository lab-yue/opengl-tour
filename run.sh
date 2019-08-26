#!/bin/bash

build(){
    g++ -I stb src/*.cpp vendor/*.cpp -o bin/app -L /usr/local/lib64  -lGL -lglfw -lGLEW
}

run(){
    MESA_GL_VERSION_OVERRIDE=4.4 LD_LIBRARY_PATH=/usr/local/lib64 ./bin/app
}


case $1 in 
    "build") build;;
    "run") run;;
    *) build && run;;
esac
