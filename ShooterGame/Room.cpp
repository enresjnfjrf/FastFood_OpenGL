#include "Room.h"

Room::Room(float x, float y, float z,float width, float height, float length, float thickness):x(x),y(y),z(z),width(width),height(height), length(length), thickness(thickness){
}
Room::~Room() {
    delete floor;
    for (auto& wall : walls)
        delete wall;
    walls.clear();
}

void Room::createWall(float x, float y, float z, float width, float height, float length)
{
    float y_h = y + height; // y + h
    float x_l = x - length; // x + l
    float z_w = z + width;  // z + w
    float wall[] = {
        // --- грань 1 (боковая передняя)
        x,      y,       z,
        x,      y_h,     z,
        x,      y_h,     z_w,
        x,      y_h,     z_w,
        x,      y,       z_w,
        x,      y,       z,
        //
        x_l,    y,       z,
        x_l,    y,       z_w,
        x_l,    y_h,     z,
        x_l,    y_h,       z,
        x_l,    y,       z_w,
        x_l,    y_h,     z_w,
        //
        x,      y,       z,
        x_l,    y,       z,
        x_l,    y_h,     z,
        x,      y,       z,
        x_l,    y_h,     z,
        x,      y_h,     z,
        //
        x,      y,       z_w,
        x,      y_h,     z_w,
        x_l,    y_h,     z_w,
        x,      y,       z_w,
        x_l,    y_h,     z_w,
        x_l,    y,       z_w,
        //
        x,      y,       z,
        x,      y,       z_w,
        x_l,    y,       z_w,
        x,      y,       z,
        x_l,    y,       z_w,
        x_l,    y,       z,
        //
        x,      y_h,     z,
        x_l,    y_h,     z,
        x_l,    y_h,     z_w,
        x,      y_h,     z,
        x_l,    y_h,     z_w,
        x,      y_h,     z_w
    };

    walls.push_back(new Wall(wall, sizeof(wall)));
}

void Room::Draw() {
    for (auto& wall : walls)
        wall->Draw();
}
