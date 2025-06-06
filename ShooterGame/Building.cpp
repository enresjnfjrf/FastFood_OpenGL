#include "Building.h"

Building::~Building() {
    for (Room* room : rooms)
        delete room;
    rooms.clear();
}

void Building::addRoom(float x, float z)
{
    rooms.push_back(new Room(x, z));
}

void Building::Draw() {
    for (Room* room : rooms)
        room->Draw();
}
