SillyDB it's a simple key-value store. To create it I'm being inspired from other key value stores like Google's [LevelDB](https://github.com/google/leveldb/tree/main) or [Bitcast](https://github.com/basho/bitcask).

This is a personal project meant to learn about databases. To do so I'm trying to create my own one, following the book *"Designing Data-Intensive Applications"* as a guideline from Martin Kleppmann.

I'm also learning C so that's the reason behind the language choice. Maybe I'll make implementations in C++ and Rust in the future.

# Build

## Using [CMake](https://cmake.org/)

Build it from the terminal using the cmake tool.

1. Create build folder
```bash
mkdir build
cd build
cmake .. # Uses the CMakeLists.txt file from the parent folder
```

2. Compile the project using the created build folder
```bash
cmake --build ./build
```

## CLion
Compiling it from the [CLion IDE](https://www.jetbrains.com/clion/) has some advantages, one of them being the debugger capabilities that the IDE enables.

1. Create the `cmake-build-debug` directory at the root folder.
```bash
mkdir cmake-build-debug
```

2. Run the CMakeLists.txt file from the IDE using the *Debug CMake* button.
