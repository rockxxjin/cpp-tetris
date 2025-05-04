# cpp-tetris

<img src="./tetris_demo.gif" width="500px" />

## 🛠 Development Environment
- Ubuntu 22.04
- g++ (C++17)
- CMake 3.16.3
- SFML 2.5.1 (`libsfml-dev`)
- Docker 24.0.5

---

## 🎮 How to Run

### Using Docker

``` bash
$ docker build -t tetris .
$ docker run --rm -it \
     -e DISPLAY=$DISPLAY \
     -v /tmp/.X11-unix:/tmp/.X11-unix \
     tetris
```

### Using CMake
``` bash
$ mkdir build
$ cmake -S . -B build
$ cmake --build build
$ ./build/tetris
```