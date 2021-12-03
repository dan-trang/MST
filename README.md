# MST
program for finding minimum-spanning-tree using greedy algorithms like Prim's and Kruskal's


To compile and run, use `g++ main.cpp Union.cpp`
To test your own external data file, change Line 35 to include the name of your .txt file.
The format of the data should be ([name of vertex 1] [name of vertex 2] [weight/distance]) with a space between each
element. For example:

Portland Eugene 112
Vancouver Grants.Pass 547
Gresham Salem 254

Uncomment or comment out Prim's or Kruskal's algorithm to run separately if you so choose. You can also move the chrono timer to test the
runtime efficiency of each algorithm. For example:

auto t1 = high_resolution_clock::now();
//Prim's algo or Kruskal's algo here
auto t2 = high_resolution_clock::now();
