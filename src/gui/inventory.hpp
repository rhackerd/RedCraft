#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <utility>
#include <SDL2/SDL.h>
#include <raylib.h>
#include "../resources/items.hpp"

// Forward declaration of Item class or struct


class Inventory {
public:
    Inventory();
    ~Inventory();
    void draw();
    void update();
    Item getSelectedItem();
    void setItem(Item item, int pos);
    
private:
    int invSize;
    int selected;
    std::vector<std::pair<Item, std::pair<int, int>>> items;

    // Constants for dimensions and spacing
    static const int ITEM_SIZE = 50;        // Width and height of the item
    static const int ITEM_PADDING = 5;      // Padding between item border and its content
    static const int ITEM_SPACING = ITEM_SIZE; // Space between the edges of adjacent items
};

#endif // INVENTORY_HPP
