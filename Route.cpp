#include "Route.h"

Route::Route(Truck *truck, int type):truck(truck), type(type), remainingCapacity(truck->totalCapacity), cost(0){}

Route::~Route() { cout<< "Deleting Route" << endl; }

int Route::getTypeIndex(){ return this->type - 1; }

int Route::getType(){ return this->type; }

bool Route::FirstTrip(){ return  this->trips.empty(); }