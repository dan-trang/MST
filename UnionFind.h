#include <iostream>

class UnionFind{
    public:
        int _size;
        int * id;
        int * sz;
        UnionFind(int size);


        int find(int cityID);
        bool unify(int p, int q);
        bool connected(int p, int q);
        int size();
};
