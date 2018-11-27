#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Trip.h"
#include "ProblemInstance.h"
#include "Route.h"
#include "Solution.h"

using namespace std;

class Construction{
public:
    unsigned long alpha;
    int totalProduction;
    vector<Trip *> neighborhood;




public:
    explicit Construction(unsigned long alpha);
    ~Construction();

    void setNeighborhood(Solution *solution, Route *currentRoute);

    bool fitsInTruck(Route *route, Node *node);

    void deleteOptions(vector<Trip *> options, unsigned long alpha);
    vector<Trip *> getOptions(Solution *solution, int currentType, Node *currentNode);
    Trip *roulette();
    void setTotalProduction();
    void feasibleSolution(Solution *solution);
    void updateIds(vector<Route *> routes);



};
