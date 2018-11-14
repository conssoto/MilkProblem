cmake_minimum_required(VERSION 3.12)
project(newMCPB)

set(CMAKE_CXX_STANDARD 14)

add_executable(newMCPB main.cpp Node.cpp Node.h Trip.cpp Trip.h Route.cpp Route.h Truck.cpp Truck.h ProblemInstance.cpp ProblemInstance.h Reader.cpp Reader.h Solution.cpp Solution.h Construction.cpp Construction.h)