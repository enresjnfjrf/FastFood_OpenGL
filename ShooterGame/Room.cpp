﻿#include "Room.h"

Room::Room(float x, float y, float z,float width, float height, float length, float thickness):x(x),y(y),z(z),width(width),height(height), length(length), thickness(thickness){
}
Room::~Room() {
    delete floor;
    for (auto& wall : walls)
        delete wall;
    walls.clear();
}

void Room::createWall(float x, float y, float z, float width, float height, float length, const std::string& diffuse, const std::string& normal, const std::string& roughness, float u, float v)
{
    float y_h = y + height; // y + h
    float x_l = x - length; // x + l
    float z_w = z + width;  // z + w
    float wall[] = {
        // --- грань 1 (боковая передняя, нормаль +X)
        x,   y,   z,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        x,   y_h, z,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        x,   y_h, z_w,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        x,   y_h, z_w,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        x,   y,   z_w,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        x,   y,   z,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,

        // --- грань 2 (боковая задняя, нормаль -X)
        x_l, y,   z,    -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        x_l, y,   z_w,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        x_l, y_h, z,    -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        x_l, y_h, z,    -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        x_l, y,   z_w,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        x_l, y_h, z_w,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,

        // --- грань 3 (левая, нормаль -Z)
        x,   y,   z,     0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        x_l, y,   z,     0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        x_l, y_h, z,     0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
        x,   y,   z,     0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        x_l, y_h, z,     0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
        x,   y_h, z,     0.0f, 0.0f, -1.0f,  0.0f, 1.0f,

        // --- грань 4 (правая, нормаль +Z)
        x,   y,   z_w,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        x,   y_h, z_w,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        x_l, y_h, z_w,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        x,   y,   z_w,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        x_l, y_h, z_w,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        x_l, y,   z_w,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,

        // --- грань 5 (низ, нормаль -Y)
        x,   y,   z,     0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        x,   y,   z_w,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        x_l, y,   z_w,   0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        x,   y,   z,     0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        x_l, y,   z_w,   0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        x_l, y,   z,     0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

        // --- грань 6 (верх, нормаль +Y)
        x,   y_h, z,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        x_l, y_h, z,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        x_l, y_h, z_w,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        x,   y_h, z,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        x_l, y_h, z_w,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        x,   y_h, z_w,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };


    walls.push_back(new Wall(wall, sizeof(wall), diffuse, normal, roughness, u, v));
}

void Room::Draw(Shader* shader) {
    for (auto& wall : walls)
        wall->Draw(shader);
}
