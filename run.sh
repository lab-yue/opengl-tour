g++ src/*.cpp -o bin/app -L /usr/local/lib64  -lGL -lglfw -lGLEW
MESA_GL_VERSION_OVERRIDE=4.4 LD_LIBRARY_PATH=/usr/local/lib64 ./bin/app