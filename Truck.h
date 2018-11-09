#pragma once
#include <iostream>

using namespace std;

class Truck
{
public:
    int id;
    int totalCapacity;

public:
    Truck(int id, int totalCapacity);
    ~Truck();

    int getId();
    int getTotalCapacity();

    bool operator==(const Truck& truck) const{return this->id == truck.id;}
    bool operator!=(const Truck& truck) const{ return !operator==(truck);}
    bool operator>(const Truck& truck) const{ return this->totalCapacity > truck.totalCapacity;}
    bool operator<(const Truck& truck) const{ return !operator>(truck);}
};

