#include "Room.h"

void Room::createFloor(float x, float z)
{
    std::cout << "Floor created" << std::endl;
    float y_bottom = 0.0f;
    float y_top = 0.02f;

    float vertices[] = {
        // Передняя грань (+Z)
        x,        y_bottom, z + 4,
        x + 4,    y_bottom, z + 4,
        x + 4,    y_top,    z + 4,
        x,        y_bottom, z + 4,
        x + 4,    y_top,    z + 4,
        x,        y_top,    z + 4,
        // Задняя грань (-Z)
        x,        y_bottom, z,
        x,        y_top,    z,
        x + 4,    y_top,    z,
        x,        y_bottom, z,
        x + 4,    y_top,    z,
        x + 4,    y_bottom, z,
        // Левая грань (-X)
        x,        y_bottom, z,
        x,        y_bottom, z + 4,
        x,        y_top,    z + 4,
        x,        y_bottom, z,
        x,        y_top,    z + 4,
        x,        y_top,    z,
        // Правая грань (+X)
        x + 4,    y_bottom, z,
        x + 4,    y_top,    z + 4,
        x + 4,    y_bottom, z + 4,
        x + 4,    y_bottom, z,
        x + 4,    y_top,    z,
        x + 4,    y_top,    z + 4,
        // Нижняя грань (низ пола)
        x,        y_bottom, z,
        x + 4,    y_bottom, z,
        x + 4,    y_bottom, z + 4,
        x,        y_bottom, z,
        x + 4,    y_bottom, z + 4,
        x,        y_bottom, z + 4,
        // Верхняя грань (верх пола)
        x,        y_top,    z,
        x,        y_top,    z + 4,
        x + 4,    y_top,    z + 4,
        x,        y_top,    z,
        x + 4,    y_top,    z + 4,
        x + 4,    y_top,    z,
    };
    floor = new Wall(vertices, sizeof(vertices));
}

void Room::createWalls(float x, float z)
{
    std::cout << "Walls created" << std::endl;
    float thickness = 0.05f; // Толщина стены
    float left[] = {
        // Внешняя (внутренняя)
        x, 0.0f,     z,
        x, h,        z,
        x, h,        z + 4,
        x, h,        z + 4,
        x, 0.0f,     z + 4,
        x, 0.0f,     z,
        // Обратная сторона (наружу)
        x - thickness, 0.0f,     z,
        x - thickness, h,        z + 4,
        x - thickness, h,        z,
        x - thickness, 0.0f,     z,
        x - thickness, 0.0f,     z + 4,
        x - thickness, h,        z + 4,
        // Левая боковая грань
        x, 0.0f, z,
        x - thickness, 0.0f, z,
        x - thickness, h,    z,
        x, 0.0f, z,
        x - thickness, h,    z,
        x, h,    z,
        // Правая боковая грань
        x, 0.0f, z + 4,
        x, h,    z + 4,
        x - thickness, h,    z + 4,
        x, 0.0f, z + 4,
        x - thickness, h,    z + 4,
        x - thickness, 0.0f, z + 4,
        // Нижняя грань
        x, 0.0f, z,
        x, 0.0f, z + 4,
        x - thickness, 0.0f, z + 4,
        x, 0.0f, z,
        x - thickness, 0.0f, z + 4,
        x - thickness, 0.0f, z,
        // Верхняя грань
        x, h, z,
        x - thickness, h, z,
        x - thickness, h, z + 4,
        x, h, z,
        x - thickness, h, z + 4,
        x, h, z + 4
    };

    float right[] = {
        // Внутренняя грань (X = x + 4), нормаль смотрит внутрь комнаты, но должна быть CCW для правильной ориентации
        x + 4, 0.0f, z,
        x + 4, 0.0f, z + 4,
        x + 4, h,    z + 4,
        
        x + 4, h,    z + 4,
        x + 4, h,    z,
        x + 4, 0.0f, z,

        // Наружная грань (обращена наружу комнаты)
        x + 4 + thickness, 0.0f, z,
        x + 4 + thickness, h,    z + 4,
        x + 4 + thickness, 0.0f, z + 4,
        
        x + 4 + thickness, h,    z + 4,
        x + 4 + thickness, 0.0f, z,
        x + 4 + thickness, h,    z,
        
        // Передняя грань (+Z)
        x + 4, 0.0f, z + 4,
        x + 4 + thickness, 0.0f, z + 4,
        x + 4 + thickness, h,    z + 4,
        x + 4 + thickness, h,    z + 4,
        x + 4, h, z + 4,
        x + 4, 0.0f, z + 4,

        // Задняя грань (−Z)
        x + 4, 0.0f, z,
        x + 4, h,    z,
        x + 4 + thickness, h,    z,
        x + 4 + thickness, h,    z,
        x + 4 + thickness, 0.0f, z,
        x + 4, 0.0f, z,

        // Нижняя грань 
        x + 4, 0.0f, z,
        x + 4 + thickness, 0.0f, z,
        x + 4 + thickness, 0.0f, z + 4,
        x + 4 + thickness, 0.0f, z + 4,
        x + 4, 0.0f, z + 4,
        x + 4, 0.0f, z,

        // Верхняя грань 
        x + 4, h, z,
        x + 4, h, z + 4,
        x + 4 + thickness, h, z + 4,
        x + 4 + thickness, h, z + 4,
        x + 4 + thickness, h, z,
        x + 4, h, z
    };

    float back[] = {
        // Исправленный порядок для внутренней грани передней стены:
    x,      0.0f, z + 4,
    x,      h,    z + 4,
    x + 4,  h,    z + 4,

    x,      0.0f, z + 4,
    x + 4,  h,    z + 4,
    x + 4,  0.0f, z + 4,


    x,      0.0f, z + 4 + thickness,
    x + 4,  0.0f, z + 4 + thickness,
    x + 4,  h,    z + 4 + thickness,
    
    x,      0.0f, z + 4 + thickness,
    x + 4,  h,    z + 4 + thickness,
    x,      h,    z + 4 + thickness,


    x, 0.0f, z + 4,
    x, 0.0f, z + 4 + thickness,
    x, h,    z + 4 + thickness,
    x, 0.0f, z + 4,
    x, h,    z + 4 + thickness,
    x, h,    z + 4,

    x + 4, 0.0f, z + 4,
    x + 4, h,    z + 4,
    x + 4, h,    z + 4 + thickness,
    x + 4, 0.0f, z + 4,
    x + 4, h,    z + 4 + thickness,
    x + 4, 0.0f, z + 4 + thickness,

    x, 0.0f, z + 4,
    x + 4, 0.0f, z + 4,
    x + 4, 0.0f, z + 4 + thickness,
    x, 0.0f, z + 4,
    x + 4, 0.0f, z + 4 + thickness,
    x, 0.0f, z + 4 + thickness,

    x, h, z + 4,
    x, h, z + 4 + thickness,
    x + 4, h, z + 4 + thickness,
    x, h, z + 4,
    x + 4, h, z + 4 + thickness,
    x + 4, h, z + 4
    };

    float front[] = {
        // Первый треугольник (нижний левый треугольник)
        x,      0.0f, z,
        x + 4,  h,    z,
        x,      h,    z,

        // Второй треугольник (верхний правый)
        x,      0.0f, z,
        x + 4,  0.0f, z,
        x + 4,  h,    z, 

        // Наружная грань (на z - thickness), порядок вершин такой же, сдвинуто по -Z
        x,      0.0f, z - thickness,
        x,      h,    z - thickness,
        x + 4,  h,    z - thickness,

        x,      0.0f, z - thickness,
        x + 4,  h,    z - thickness,
        x + 4,  0.0f, z - thickness,

        // Левая боковая грань (толщина стены)
        x, 0.0f, z,
        x, h,    z,
        x, h,    z - thickness,

        x, 0.0f, z,
        x, h,    z - thickness,
        x, 0.0f, z - thickness,

        // Правая боковая грань (толщина стены)
        x + 4, 0.0f, z,
        x + 4, h,    z - thickness,
        x + 4, h,    z,

        x + 4, 0.0f, z,
        x + 4, 0.0f, z - thickness,
        x + 4, h,    z - thickness,

        // Нижняя грань
        x, 0.0f, z,
        x + 4, 0.0f, z - thickness,
        x + 4, 0.0f, z,

        x, 0.0f, z,
        x, 0.0f, z - thickness,
        x + 4, 0.0f, z - thickness,

        // Верхняя грань
        x, h, z,
        x + 4, h, z,
        x + 4, h, z - thickness,

        x, h, z,
        x + 4, h, z - thickness,
        x, h, z - thickness
    };


    walls.push_back(new Wall(right, sizeof(right)));
    walls.push_back(new Wall(back, sizeof(back)));
    walls.push_back(new Wall(front, sizeof(front)));
    walls.push_back(new Wall(left, sizeof(left)));
}

Room::Room(float x, float z){
    std::cout << "Создаётся комната " << std::endl;
    createFloor(x, z);
    createWalls(x, z);
}
Room::~Room() {
    delete floor;
    for (auto& wall : walls)
        delete wall;
}

void Room::Draw() {
    floor->Draw();
    for (auto& wall : walls)
        wall->Draw();
}
