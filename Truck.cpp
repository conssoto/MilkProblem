#include "Truck.h"

Truck::Truck(int id, int totalCapacity): id(id), totalCapacity(totalCapacity) {}

Truck::~Truck(){}

int Truck::getId(){ return this->id; }

int Truck::getTotalCapacity(){ return this->totalCapacity; }
