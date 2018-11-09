#pragma once
#include "Truck.h"
#include "Trip.h"
#include <vector>
#include <iostream>

using namespace std;

class Route {
public:
    Truck *truck;
    vector<Trip *> trips;
    double cost;
    int remainingCapacity;
    int type;


public:
    Route(Truck *truck, int type);
    ~Route();

    int getTypeIndex();
    int getType();

    bool FirstTrip();
};
