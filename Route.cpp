#include "Route.h"

Route::Route(Truck *truck, int type):truck(truck), type(type), remainingCapacity(truck->totalCapacity), cost(0), full(false){}

Route::~Route() {}

int Route::getTypeIndex(){ return this->type - 1; }

int Route::getType(){ return this->type; }

bool Route::isFull(){ return this->full; }

void Route::setFull() { this->full = true; }

bool Route::FirstTrip(){ return  this->trips.empty(); }

