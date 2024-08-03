#ifndef VOXEL_H
#define VOXEL_H

#include <raylib.h>
#include <algorithm>  // For std::max

class Voxel {
public:
    int x, y;
    int id;
    Color color;
    Color originalColor;
    bool isHovered;
    bool isClicked;
    bool isDisabled;
    bool hasGui;
    int durability;  // If durability is 0, block is unbreakable
    int offsetX;
    int offsetY;
    int blockSize;
    Texture2D texture;

    Voxel(int x, int y, Color color = {10, 10, 10, 255}) 
        : x(x), y(y), id(0), color(color), originalColor(color), isHovered(false), isClicked(false), isDisabled(false), hasGui(false), durability(0), offsetX(0), offsetY(0), blockSize(50) {}

    virtual ~Voxel() = default;

virtual void Draw() const {
    if (texture.id != 0) {
        Rectangle sourceRec = {0, 0, (float)texture.width, (float)texture.height};  // Source rectangle (texture size)
        Rectangle destRec = {static_cast<float>((x * blockSize) + offsetX), static_cast<float>((y * blockSize) + offsetY), static_cast<float>(blockSize), static_cast<float>(blockSize)}; // Destination rectangle (where to draw)
        Vector2 origin = {0, 0}; // Rotation origin

        // Draw the texture
        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, color);  // No rotation and tint color is white
    } else {
        // Draw a rectangle if texture is not set
        DrawRectangle((x * blockSize) + offsetX, (y * blockSize) + offsetY, blockSize, blockSize, color);
    }
}


    virtual void onClick() {
    }

    virtual void onHover() {
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
        Rectangle blockRect = { static_cast<float>(x*blockSize)+offsetX, static_cast<float>(y*blockSize)+offsetY, 50, 50 };
        

        bool currentlyHovered = CheckCollisionPointRec(mousePos, blockRect);


        if (currentlyHovered) {

            color.r = std::max(originalColor.r - 30, 0);
            color.g = std::max(originalColor.g - 30, 0);
            color.b = std::max(originalColor.b - 30, 0);
            this->isHovered = true;


            if (!wasHoveredLastFrame) {
                onHover();
            }
        } else {

            color = originalColor;
            this->isHovered = false;
        }

        wasHoveredLastFrame = currentlyHovered;
    }

    void HandleClicking() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            

            if (this->isHovered) {
                onClick();
            }
        }
    }
};

#endif // VOXEL_H
