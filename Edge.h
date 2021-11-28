#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::vector;

class Destination{
    public:
        // Constructor
        Destination() : destinationName(""), distance(0){}

        Destination(string newDestination, int newDistance){
            destinationName = newDestination;
            distance = newDistance;
        }

        string destinationName;
        int distance;

};

class City{
    public:

        City() : name(), destination(),
            visited(false){}

        string name;                        //Vertex name
        vector<Destination> destination;    //List of edges
        bool visited;
};
