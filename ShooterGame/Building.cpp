#include "Building.h"

Building::~Building() {
    for (Room* room : rooms)
        delete room;
    rooms.clear();
}

void Building::addRoom(Room* room)
{
    rooms.push_back(room);
}

void Building::Draw(Shader* shader) {
    for (Room* room : rooms)
        room->Draw(shader);
}
