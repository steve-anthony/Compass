#include "include/Compass.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;


int main()
{
    cout << "Hello world!" << endl;
    //Compass::PAStar::AStar *  astar = new Compass::PAStar::AStar();

    Compass::PCore::Matrix<int> mapi(20,20,1);

    mapi.set(4,0,Compass::WALL);
    mapi.set(4,1,Compass::WALL);
    mapi.set(4,2,Compass::WALL);
    mapi.set(4,3,Compass::WALL);
    mapi.set(4,4,Compass::WALL);
    mapi.set(4,5,Compass::WALL);
    mapi.set(4,6,Compass::WALL);
    mapi.set(4,7,Compass::WALL);
    mapi.set(4,8,Compass::WALL);
    mapi.set(5,8,Compass::WALL);
    mapi.set(6,8,Compass::WALL);
    mapi.set(7,8,Compass::WALL);
    mapi.set(8,8,Compass::WALL);
    mapi.set(9,8,Compass::WALL);
    mapi.set(9,10,Compass::WALL);
    mapi.set(9,11,Compass::WALL);
    mapi.set(9,12,Compass::WALL);
    mapi.set(9,7,Compass::WALL);
    mapi.set(10,8,Compass::WALL);
    mapi.set(10,9,Compass::WALL);
    mapi.set(10,10,Compass::WALL);
    mapi.set(11,10,Compass::WALL);
    mapi.set(12,10,Compass::WALL);
    mapi.set(13,10,Compass::WALL);


    Compass::PPathfinding::AStar  astar;
    astar.init(&mapi);
    std::list<Compass::PCore::Point> res = astar.run(Compass::PCore::Point(2,2),Compass::PCore::Point(6,7));
    res = astar.run(Compass::PCore::Point(2,2),Compass::PCore::Point(18,3));

    int n=1;
    while (!res.empty())
    {
        mapi.set(res.front().x,res.front().y,n);
        n++;
        res.pop_front();
    }


    for (int i = 0; i< mapi.getSizeX();i++){
        for (int j = 0; j< mapi.getSizeY();j++){
            if (i == 2 && j == 2) cout << "XX" << " " ;
            else if (i == 18 && j == 3) cout << "YY" << " " ;
            else if (mapi.get(i,j) < 0) cout << "**" << " " ;
            else if (mapi.get(i,j) == 1) cout << "  " << " " ;
            else printf ("%.2i ", mapi.get(i,j));
        }
        cout << endl;
    }


    return 0;
}
