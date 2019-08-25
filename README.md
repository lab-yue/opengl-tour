# OpenGL Tour

## Compile dependencies

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

## Run

## build and run

`./run.sh`

### compile app

`./run.sh build`

### run built binary

`./run.sh run`
