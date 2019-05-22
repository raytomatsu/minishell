#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H


#include <vector>


using namespace std;

class graphObj
{
public:
    graphObj();
    graphObj(vector<int> time,vector<int>change);

    vector<int> time;
    vector<int> change;
};

#endif // GRAPHOBJ_H
