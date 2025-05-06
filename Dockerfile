FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential cmake libsfml-dev

WORKDIR /app

COPY CMakeLists.txt CMakeLists.txt
COPY src/ src/
COPY assets/ assets/

RUN  useradd -ms /bin/bash appuser && \
    chown -R appuser:appuser /app
USER appuser

RUN mkdir build && \
    cmake -S . -B build && \
    cmake --build build

ENTRYPOINT [ "./build/tetris" ]