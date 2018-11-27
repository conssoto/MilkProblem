#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Trip.h"
#include "ProblemInstance.h"
#include "Route.h"
#include "Solution.h"

using namespace std;

class reorderNodes {
public:
    double bestDistance;
    int bestIndex;
    Node *node;


public:
    reorderNodes();
    ~reorderNodes();
    void removeTrip(int tripIndex, Route *route, ProblemInstance *problemInstance);
    void setBest(Route *route, ProblemInstance *problemInstance);
    void insertTrip(Route *route, Solution *solution, ProblemInstance *problemInstance);
    void printRoute(Route *route);
    };
