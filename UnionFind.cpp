#include "UnionFind.h"

UnionFind::UnionFind(int size){
    _size = size;
    id = new int[size];
    sz = new int[size];

    for(int i=0; i<size; i++){
        id[i] = i;  //each city ID "points" to itself (self root)
        sz[i] = 1;  //intialize size of each "group" to 1
    }
}

int UnionFind::find(int cityID){
    //Find the root of the city component
    int root = cityID;
    while(root != id[root]){
        root = id[root];
    }

    while(cityID != root){
        int next = id[cityID];
        id[cityID] = root;
        cityID = next;
    }
    return root;
}

bool UnionFind::unify(int p, int q){
    int root1 = find(p);
    int root2 = find(q);

    //if root1 and root2 are in the same "group" return false and do NOT unify
    if(root1 == root2) 
        return false;

    //Merge two "groups" together
    if (sz[root1] < sz[root2]){
        sz[root2] += sz[root1];
        id[root1] = root2;
    }
    else{
        sz[root1] += sz[root2];
        id[root2] = root1;
    }
    return true;
}

bool UnionFind::connected(int p, int q){
    return find(p) == find(q);
}

int UnionFind::size(){
    return _size;
}