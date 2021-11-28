#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;

class Destination{
    public:
        // Constructor
        Destination() : string destinationName(), int distance(0){}

        Destination(string newDestination, int newDistance){
            this.destinationName = newDestination;
            this.distance = newDistance;
        }

        string destinationName;
        int distance;

};

class City{
    public:

        City() : string name(), vector<Destination> destination(),
            bool visited(false){}

        string name;                        //Vertex name
        vector<Destination> destination;    //List of edges
        bool visited;
};
