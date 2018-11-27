#include "Route.h"

Route::Route(int id, Truck *truck, int type):id(id), truck(truck), type(type), remainingCapacity(truck->totalCapacity), cost(0), full(false), distance(0){}

Route::~Route() {}

int Route::getId(){ return this->id; }

int Route::getTypeIndex(){ return this->type - 1; }

int Route::getType(){ return this->type; }

bool Route::isFull(){ return this->full; }

void Route::setId(int id) { this->id = id; }

void Route::setFull() { this->full = true; }

bool Route::FirstTrip(){ return  this->trips.empty(); }

