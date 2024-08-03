#include "logging.hpp"
#include "inventory.hpp"
#include <raylib.h>

// info(); for output

Inventory::Inventory() {
    invSize = 2;
    selected = 0;
    items = std::vector<std::pair<Item, std::pair<int, int>>>();
}

Inventory::~Inventory() {
    items.clear();
}

void Inventory::draw() {
    // Colors
    const Color BORDER_COLOR = BLACK;
    const Color ITEM_COLOR = WHITE;
    const Color SELECTED_COLOR = YELLOW;

    // Get the screen width once for efficiency
    int screenWidth = GetScreenWidth();

    // Calculate the starting X position to center items on the screen
    int totalWidth = invSize * ITEM_SIZE; // Total width of all items
    int startX = screenWidth - totalWidth; // Starting X position for the first item

    // Draw each inventory item
    for (int i = 0; i < invSize; i++) {
        // Calculate the X position for the current item
        int x = startX + i * ITEM_SIZE;
        int y = 0;

        // Determine color based on selection
        Color currentItemColor = (i == selected) ? SELECTED_COLOR : ITEM_COLOR;

        // Draw the border rectangle
        DrawRectangle(x, y, ITEM_SIZE, ITEM_SIZE, BORDER_COLOR);

        // Draw the inner item rectangle with padding
        DrawRectangle(x + ITEM_PADDING, y + ITEM_PADDING, ITEM_SIZE - 2 * ITEM_PADDING, ITEM_SIZE - 2 * ITEM_PADDING, currentItemColor);
    }
}

void Inventory::update() {
    // Check for raylib input instead of SDL events
    if (IsKeyPressed(KEY_ONE)) {
        selected = 0;
    } else if (IsKeyPressed(KEY_TWO)) {
        selected = 1;
    } else if (IsKeyPressed(KEY_LEFT)) {
        if (selected > 0) {
            selected--;
        }
    } else if (IsKeyPressed(KEY_RIGHT)) {
        if (selected < invSize - 1) {
            selected++;
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        int mouseX = mousePos.x;
        int mouseY = mousePos.y;

        // Calculate the starting X position to center items on the screen
        int screenWidth = GetScreenWidth();
        int totalWidth = invSize * ITEM_SIZE; // Total width of all items
        int startX = screenWidth - totalWidth; // Starting X position for the first item

        // Check which item was clicked
        for (int i = 0; i < invSize; i++) {
            int x = startX + i * ITEM_SIZE;
            int y = 0;

            if (mouseX >= x && mouseX <= x + ITEM_SIZE && mouseY >= y && mouseY <= y + ITEM_SIZE) {
                selected = i;
            }
        }
    }

    int wheelMove = GetMouseWheelMove();
    if (wheelMove > 0) {
        if (selected > 0) {
            selected--;
        }
    } else if (wheelMove < 0) {
        if (selected < invSize - 1) {
            selected++;
        }
    }
}

Item Inventory::getSelectedItem() {
    return items[selected].first;
}