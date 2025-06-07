#include "Room.h"

Room::Room(float x, float y, float z,float width, float height, float lenght, float thickness):x(x),y(y),z(z),width(width),height(height),lenght(lenght), thickness(thickness){
    createWall(x - thickness, y - thickness, z, width, thickness, lenght); // Пол
    createWall(x, y, z, width, height / 3, thickness); 
    createWall(x, y + (2 * height) / 3, z, width, height / 3, thickness);
    createWall(x - thickness, y, z - thickness, thickness, height, lenght);
    createWall(x - lenght - thickness, y, z + width , -width, height, thickness);
    createWall(x - lenght - thickness, y, z + width , thickness, height, -lenght);
}
Room::~Room() {
    delete floor;
    for (auto& wall : walls)
        delete wall;
    walls.clear();
}

void Room::createWall(float x, float y, float z, float width, float height, float lenght)
{
    float y_h = y + height; // y + h
    float x_l = x - lenght; // x + l
    float z_w = z + width;  // z + w
    float wall[] = {
        //
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
