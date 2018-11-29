#include "Route.h"

Route::Route(int id, Truck *truck, int type):id(id), truck(truck), type(type), remainingCapacity(truck->totalCapacity), cost(0), full(false), distance(0){}

Route::~Route() {}

int Route::getId(){ return this->id; }

int Route::getTypeIndex(){ return this->type - 1; }

int Route::getType(){ return this->type; }

bool Route::isFull(){ return this->full; }

void Route::setId(int id) { this->id = id; }

void Route::setFull() { this->full = true; }

void Route::printAll() {
    double aux(0);
    for(Trip *trip: this->trips){
        aux += trip->benefit;
    }
    cout << "Route: " << this->getId() << " truck: " << this->truck->getId() << " milk type: " << this->type << " isFull: "
         << this->full << " total benefit: " << aux << endl;
    cout << "Num. of trips: " << this->trips.size() << " remaining Capacity: " << this->remainingCapacity << " distance: " << this->distance << endl;
}

bool Route::FirstTrip(){ return  this->trips.empty(); }

