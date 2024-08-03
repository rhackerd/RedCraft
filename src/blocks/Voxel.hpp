#ifndef VOXEL_H
#define VOXEL_H

#include <raylib.h>
#include <algorithm>  // For std::max

class Voxel {
public:
    int x, y;
    int id;
    Color color;
    Color originalColor;  // Store the original color
    bool isHovered;
    bool isClicked;
    bool isDisabled;
    bool hasGui;
    int durability;  // Changed from bool to int. If durability is 0, block is unbreakable
    int offsetX;
    int offsetY;

    Voxel(int x, int y, Color color = {10, 10, 10, 255}) 
        : x(x), y(y), id(0), color(color), originalColor(color), isHovered(false), isClicked(false), isDisabled(false), hasGui(false), durability(0), offsetX(0), offsetY(0) {}

    virtual ~Voxel() = default;

    virtual void Draw() const {
        DrawRectangle(x+offsetX, y+offsetY, 50, 50, color);  // Assuming default size is 50x50
    }

    virtual void onClick() {
        // Implement click behavior here
    }

    virtual void onHover() {
        // Implement hover behavior here
    }

    virtual void Update() {
        HandleHovering();
        HandleClicking();
    }

    virtual void SetOffset(int x, int y) {
        offsetX = x;
        offsetY = y;
    }

private:
    bool wasHoveredLastFrame = false;

    void HandleHovering() {
        Vector2 mousePos = GetMousePosition();
        Rectangle blockRect = { static_cast<float>(x)+offsetX, static_cast<float>(y)+offsetY, 50, 50 };  // Assuming default size is 50x50
        
        // Check if the mouse is hovering over the block
        bool currentlyHovered = CheckCollisionPointRec(mousePos, blockRect);

        // Adjust color to be a bit darker when hovered
        if (currentlyHovered) {
            // Darken the color by reducing the RGB values
            color.r = std::max(originalColor.r - 30, 0);  // Ensure value does not go below 0
            color.g = std::max(originalColor.g - 30, 0);  // Ensure value does not go below 0
            color.b = std::max(originalColor.b - 30, 0);  // Ensure value does not go below 0

            // Call onHover() only when the voxel is hovered for the first time
            if (!wasHoveredLastFrame) {
                onHover();
            }
        } else {
            // Reset to the original color
            color = originalColor;
        }

        wasHoveredLastFrame = currentlyHovered;
    }

    void HandleClicking() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            Rectangle blockRect = { static_cast<float>(x), static_cast<float>(y), 50, 50 };  // Assuming default size is 50x50
            
            // Check if the mouse click is within the bounds of the block
            if (CheckCollisionPointRec(mousePos, blockRect)) {
                onClick();
            }
        }
    }
};

#endif // VOXEL_H
