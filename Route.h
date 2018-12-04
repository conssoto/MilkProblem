#pragma once
#include "Truck.h"
#include "Trip.h"
#include <vector>
#include <iostream>

using namespace std;

class Route {
public:
    int id;
    Truck *truck;
    vector<Trip *> trips;
    double cost;
    int remainingCapacity;
    int type;
    bool full;
    double distance;


public:
    Route(int id, Truck *truck, int type);
    ~Route();

    int getId();
    int getTypeIndex();
    int getType();
    bool isFull();

    void setId(int id);
    void setFull();
    bool FirstTrip();

    void removeTrip(int tripIndex, Route *route);

    void printAll();
};
