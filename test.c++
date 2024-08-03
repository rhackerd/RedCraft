#include <vector>
#include <iostream>

class Grass {
public:
    int x, y;

    Grass(int x, int y) : x(x), y(y) {}

    void Draw() const {
        std::cout << "Drawing grass at (" << x << ", " << y << ")" << std::endl;
    }
};

class Stone {
public:
    int x, y;

    Stone(int x, int y) : x(x), y(y) {}

    void Draw() const {
        std::cout << "Drawing Stone at (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    // Create a vector of Block objects
    std::vector<????> blocks;

    // Add some Block objects to the vector
    blocks.emplace_back(10, 20, Stone);
    blocks.emplace_back(30, 40, Grass);
    blocks.emplace_back(50, 60, Grass);

    // Iterate over the blocks and call the Draw method on each
    for (const auto& block : blocks) {
        block.Draw();
    }

    return 0;
}