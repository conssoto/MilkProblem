#pragma once
#include <vector>
#include "Truck.h"
#include "Node.h"
#include "ProblemInstance.h"
#include "Route.h"
#include "Solution.h"
#include <iostream>
#include <numeric>


class AddNodes {
public:
    vector<Trip *> neighborhood;
    Node *removedNode;
    double totalBenefit;
    int insertPosition;


public:
    explicit AddNodes();
    ~AddNodes();

    Trip *getBestNeighbor(Solution *solution, Route *currentRoute, Trip *trip);
    void setNeighborhood(Solution *solution, Route *route);
    bool fitsInTruck(Route *route, Node *node);
    void deleteOptions(vector<Trip *> options, int aux);
    void setTotalBenefit();
    Trip *roulette();
    void insertTrip(Trip *selectedTrip, Solution *solution);
    void movement(Solution *solution);




    };
