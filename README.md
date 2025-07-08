# RedCraft

**RedCraft** is a voxel-based game written in C++ using [raylib](https://www.raylib.com/).

## 🛠️ Requirements

Make sure the following dependencies are installed on your system:

* A C++17 compatible compiler (e.g. `g++`, `clang++`)
* [CMake](https://cmake.org/) (version 3.12 or higher)
* [raylib](https://github.com/raysan5/raylib) (installed and linked properly)

## 🚀 Building RedCraft

Follow these steps to build the game:

```bash
# Clone the repository (if you haven't already)
git clone https://github.com/yourusername/RedCraft.git
cd RedCraft

# Create a build directory and enter it
mkdir build
cd build

# Generate build files with CMake
cmake ..

# Build the project
cmake --build .
```

> ℹ️ On Linux, you might need to install raylib via your package manager or build it from source.
> On Windows, make sure raylib and its dependencies are properly set up in your compiler's include/lib paths.

## ▶️ Running the Game

After building, run the executable (inside the `build` folder):

```bash
./RedCraft
```

## 📌 Notes

* The development is paused until a workable version of Nova engine will be published.
* The game is still in **early development**, and features are subject to change.
* This version of RedCraft uses a basic voxel engine with raylib for rendering.

## 👤 Author

* [rhackerd](https://github.com/rhackerd)

---

Let me know if you want to add build instructions for Windows/MSVC, or package manager instructions for raylib (like `pacman -S raylib` or `vcpkg`).
