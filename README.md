# OpenGL Tour

## Compile

### compile glfw on linux:

```
cd glfw
cmake -DBUILD_SHARED_LIBS=1 .
make
sudo make install
```

### compile glew on linux:

```
cd glew
make extensions
make
sudo make install
make clean
```

### compile app

`g++ src/*.cpp -o bin/app -L /usr/local/lib64 -lGL -lglfw -lGLEW`

## Run

`MESA_GL_VERSION_OVERRIDE=4.4 LD_LIBRARY_PATH=/usr/local/lib64 ./bin/app`
