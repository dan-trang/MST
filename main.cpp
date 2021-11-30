#include <iostream>
#include "City.h"
#include "PQ.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <assert.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;

//Function forward declarations
bool buildCityList (vector<City> & cityList, const string fileName);
bool visited (string checkCity, vector<string> visitedList);
void displayCity (vector<City> cityList);
void displayPQ (vector<PQ> pqList);
void quicksort (vector<PQ> & pqList, int l, int r);
void swap (vector<PQ> & pqList, int l, int r);
int partition (vector<PQ> & pqList, int l, int r);

int prims(vector<City> & cityList, vector<string> & visitedList);
int primsRecursive(vector<City> cityList, vector<string> & visitedList, City *& currentCity, vector<PQ> priorityList);

int kruskals(vector<City> & cityList);

//Main 
int main(){
    const string fileName = "city-pairs.txt";
    vector<Destination> destinationArray;
    vector<City> cityList;
    vector<string> visitedList;
    
    if (!buildCityList(cityList, fileName)){
        cout << "Error opening file \"" << fileName << "\"" << '\n';
        return 1;
    }

    /*
    // ***************** PRIM'S ALGO ************************** //
    cout << "=============================================\n";
    cout << "\t Prim's Algorithm Solution\n";
    cout << "=============================================\n";
    int total = prims(cityList, visitedList);
    cout << endl << "Total distance [prims]: " << total << endl;
    // ******************************************************** //
    */

    //displayCity(cityList);

    // ***************** KRUSKAL'S ALGO ************************//
    cout << "\n=============================================\n";
    cout << "\t Kruskal's Algorithm Solution\n";
    cout << "=============================================\n";
    int total = kruskals(cityList);
    cout << endl << "Total distance [kruskals]: " << total << endl;


    return 0;
}

/*This function builds a list of unique cities based on the first in each line
 * of the input file.  Each City object's destination list
 * is also populated.  It returns false if the file name is unable to be opened.
 */
bool buildCityList(vector<City> & cityList, const string fileName){
    ifstream infile (fileName);
    if (!infile.is_open())
        return false;
    
    string cityName;
    string destinationName;
    int distance;

    /*The following code block reads in city names and stores them in a vector.
     * Each string read in is checked for uniqueness with the std::find()
     * function before being added.  The destination and distance values are
     * also read in and stored in the City object's destination list.
     */
    do{
        infile >> cityName;
        bool flag = false;
        for (auto &i: cityList){
            if (i.name == cityName){
                flag = true;
                infile >> destinationName >> distance;
                Destination *newDestination = new Destination(destinationName, distance);
                i.destination.push_back(*newDestination);
            }
        }
        if (flag == false){
            City *newCity = new City(cityName);
            cityList.push_back(*newCity);
            infile >> destinationName >> distance;
            Destination *newDestination = new Destination(destinationName, distance);
            cityList.back().destination.push_back(*newDestination);
        }
        infile.ignore(1000, '\n');
    }while (!infile.eof());
    return true;
}

//Utility function to compare string name to list of visited cities in a vector
bool visited(string checkCity, vector<string> visitedList){
    for (long unsigned int i = 0; i < visitedList.size(); i++){
        if (checkCity == visitedList[i])
            return true;
    }
    return false;
}

void displayCity(vector<City> cityList){
    for (City i: cityList){
        cout << i.name << '\n';
        for (Destination j: i.destination){
            cout << '\t' << j.destinationName << ", " << j.distance << '\n';
        }
    }
}

void displayPQ(vector<PQ> pqList){
    for (PQ i: pqList){
        cout << i.startCity << " " << i.endCity << " " << i.distance << endl;
    }
}

void quicksort (vector<PQ> & pqList, int l, int r){
    if (l < r){
        int s = partition(pqList, l, r);
        if (s - 1 >= 0)
            quicksort (pqList, l, s-1);
        if (s + 1 <= r)
            quicksort (pqList, s+1, r);
    }
    else
        return;
}

int partition (vector<PQ> & pqList, int l, int r){
    int pivot = pqList[r].distance;
    int j = (l - 1);

    for (int i = 1; i <= r-1; ++i){
        if (pqList[i].distance <= pivot){
            j++;
            swap (pqList, j, i);
        }
    }
    swap (pqList, j+1, r);
    return (j+1);
}

void swap (vector<PQ> & pqList, int l, int r){
    //store and save PQ left index values temporarily
    string tempStartCity = pqList[l].startCity;
    string tempEndCity = pqList[l].endCity;
    int tempDistance = pqList[l].distance;

    //copy PQ right to PQ left
    pqList[l].startCity = pqList[r].startCity;
    pqList[l].endCity = pqList[r].endCity;
    pqList[l].distance = pqList[r].distance;

    //copy PQ temp into PQ right
    pqList[r].startCity = tempStartCity;
    pqList[r].endCity = tempEndCity;
    pqList[r].distance = tempDistance;
}

/* This function implements Prim's greedy algorithm for finding a minimum 
 * spanning tree (MST).  For simplicity, the resulting tree will be represented
 * as a matrix where each square representing a nonexistent or not-utilized edge
 * contains a 0 and each edge used in the the MST displays the edge's weight.
 * The function keeps a running total of the overall weight as edges are added
 * to the MST.
 */
int prims(vector<City> & cityList, vector<string> & visitedList){ 
    if (cityList.empty())
        return 0;
    else{
        vector<PQ> priorityList; 
        City* currentCity = new City(cityList[0]);
        return primsRecursive(cityList, visitedList, currentCity, priorityList);
    }
}

int primsRecursive(vector<City> cityList, vector<string> & visitedList, City *& currentCity, vector<PQ> priorityList){ 
    if (cityList.empty())
        return 0;
    
    visitedList.push_back(currentCity->name);
    for (long unsigned int i = 0; i < cityList.size(); i++){
        if (currentCity->name == cityList[i].name){
            cityList.erase(cityList.begin() + i);
            break;
        }
    }

    //for loop to add new unvisited cities to priority list
    for (long unsigned int i = 0; i < currentCity->destination.size(); i++){
        if (visited(currentCity->destination[i].destinationName, visitedList) == false){ 
            PQ * newEdge = new PQ(currentCity->name, currentCity->destination[i].destinationName, currentCity->destination[i].distance);
            priorityList.push_back(*newEdge);
        }
    }

    //for loop to find the nearest City and index of that city in the priority list
    int smallestDistance = 0;
    int smallestIndex = 0;
    for (long unsigned int j = 0; j < priorityList.size(); j++){
        if (!visited(priorityList[j].endCity, visitedList)){
            if (smallestDistance == 0 || priorityList[j].distance < smallestDistance){
                smallestIndex = j;
                smallestDistance = priorityList[j].distance;
            }
        }
    }

    cout << priorityList[smallestIndex].startCity << "(" << priorityList[smallestIndex].endCity << "), " << priorityList[smallestIndex].distance << "\n";   //prints out MST edge
    //visitedList.push_back(priorityList[smallestIndex].endCity);     //add destination city to list of visited

    for (long unsigned int i = 0; i < cityList.size(); i++){
        if (priorityList[smallestIndex].endCity == cityList[i].name){
            currentCity = new City(cityList[i]);
            cityList.erase(cityList.begin() + i);
            break;
        }
    }

    priorityList.erase (priorityList.begin() + smallestIndex);      //pops entry from priority list

    return smallestDistance + primsRecursive(cityList, visitedList, currentCity, priorityList);
}


/* Kruskal's Algorithm implements a Union Find or disjoint abstract data structure to keep track of
* separate branches or groups inside the graph. Once all the groups are connected, the MST is found.
* The key difference is that the edges are all sorted in ascending order, then algorithmicly selected
* to find the MST.
*/
int kruskals(vector<City> & cityList){
    if (cityList.empty())
        return 0;

    vector<PQ> sortedList;  //container to gather all the edges and sort in ascending order

    for (long unsigned int i = 0; i < cityList.size(); ++i){
        for (long unsigned int j = 0; j < cityList[i].destination.size(); ++j){
            PQ * newEdge = new PQ(cityList[i].name, cityList[i].destination[j].destinationName,
                                  cityList[i].destination[j].distance);
            sortedList.push_back(*newEdge);
        }
    }

    int rightIndex = sortedList.size();
    int leftIndex = 0;

    cout << rightIndex << endl;
    cout << sortedList[rightIndex-1].distance << endl;

    quicksort(sortedList, leftIndex, rightIndex - 1); 
    displayPQ(sortedList);  


    return -1;
}