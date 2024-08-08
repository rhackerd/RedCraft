#ifndef WORLDGEN_HPP
#define WORLDGEN_HPP


#include <vector>

class worldGen {
public:
    worldGen();  // Constructor to initialize PerlinNoise
    void init();
    std::vector<float> genCell(int x, int y);

private:

};

#endif
