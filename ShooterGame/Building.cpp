#include "Building.h"

Building::~Building() {
    for (Room* room : rooms)
        delete room;
    rooms.clear();
}

void Building::addRoom(float x, float y, float z, float width, float height, float lenght, float thickness)
{
    rooms.push_back(new Room(x, y, z, width, height, lenght, thickness));
}

void Building::Draw() {
    for (Room* room : rooms)
        room->Draw();
}
