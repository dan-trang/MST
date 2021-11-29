#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;


class PQ{
    public:
        PQ() : startCity(""), endCity(""), distance(0) {}
        PQ(string newStartCity, string newEndCity, int newDistance) {
            startCity = newStartCity;
            endCity = newEndCity;
            distance = newDistance;
        }

        string startCity;
        string endCity;
        int distance;
};