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

        /*
        Destination(const Destination &aDestination){
            this->destinationName = aDestination.destinationName;
            this->distance = aDestination.distance;
        }
        */

        string destinationName;
        int distance;

};

class City{
    public:

        City() : name(), destination(),
            visited(false){}
        City(string newName) : name(newName), destination(),
            visited(false){}
        City(const City &aCity){
            this->name = aCity.name;
            this->destination = aCity.destination;
            this->visited = aCity.visited;
        }

        string name;                        //Vertex name
        vector<Destination> destination;    //List of edges
        bool visited;
};
