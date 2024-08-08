#ifndef VOXEL_H
#define VOXEL_H


#include <csignal>
#include <cstdlib>
#include <algorithm>  // For std::max
#include <iostream>
#include <random>
#include <raylib.h>

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
    int rotation;

    Voxel(int x, int y, Color color = {10, 10, 10, 255}) 
        : x(x), y(y), id(0), color(color), originalColor(color), isHovered(false), isClicked(false), isDisabled(false), hasGui(false), durability(0), offsetX(0), offsetY(0), blockSize(50), rotation(0) {
            texture.id = 0;
        }

    virtual ~Voxel() {
    };

virtual void Draw() const {
    int realx = (x * blockSize) + offsetX;
    int realy = (y * blockSize) + offsetY;
    if (texture.id != 0) {
        Rectangle sourceRec = {0, 0, (float)texture.width, (float)texture.height};  // Source rectangle (texture size)
        Rectangle destRec = {static_cast<float>((x * blockSize) + offsetX), static_cast<float>((y * blockSize) + offsetY), static_cast<float>(blockSize), static_cast<float>(blockSize)}; // Destination rectangle (where to draw)
        Vector2 origin = {0, 0}; // Rotation origin

        // Draw the texture
        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
    } else {
        // Draw a rectangle if texture is not set
        DrawRectangle((x * blockSize) + offsetX, (y * blockSize) + offsetY, blockSize, blockSize, color);
    }
    if (isHovered) {
        DrawRectangleLines((x*blockSize)+offsetX, (y*blockSize)+offsetY, blockSize, blockSize, BLACK);
        DrawRectangle(realx, realy, blockSize, blockSize, {0,0,0,128});
    }
}

    virtual void autoRotate() {
        // i want it to be 0, 90, 180, 270, 360
        this->rotation = (this->rotation + 90) % 360;
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
