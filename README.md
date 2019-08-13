# OpenGL Tour

## Compile

### compile glfw on linux:

```
cd glfw
cmake -DBUILD_SHARED_LIBS=1 .
make
sudo make install
```

### compile app

`g++ src/app.cpp -o bin/app -L /usr/local/lib64 -lGL -lglfw`

## Run

`LD_LIBRARY_PATH=/usr/local/lib64 ./bin/app`
