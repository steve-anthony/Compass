#include "include/Compass.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    //Compass::PAStar::AStar *  astar = new Compass::PAStar::AStar();

    Compass::PCore::Matrix<int> mapi(20,20,1);

    mapi.set(4,0,9);
    mapi.set(4,1,9);
    mapi.set(4,2,9);
    mapi.set(4,3,9);
    mapi.set(4,4,9);
    mapi.set(4,5,9);
    mapi.set(4,6,9);
    mapi.set(4,7,9);
    mapi.set(4,8,9);

    Compass::PCore::Matrix<int> mapres(20,20,0);
    mapres.set(4,0,9);
    mapres.set(4,1,9);
    mapres.set(4,2,9);
    mapres.set(4,3,9);
    mapres.set(4,4,9);
    mapres.set(4,5,9);
    mapres.set(4,6,9);
    mapres.set(4,7,9);
    mapres.set(4,8,9);


    Compass::PPathfinding::AStar  astar;
    astar.init(mapi);
    std::list<Compass::PCore::Point> res = astar.run(Compass::PCore::Point(2,2),Compass::PCore::Point(8,5));

    int n=1;
    while (!res.empty())
      {

        //std::cout << ' ' << res.front().x << " " << res.front().y << std::endl;
        mapres.set(res.front().x,res.front().y,n);
        n++;
        res.pop_front();
      }


    for (int i = 0; i< mapres.getSizeX();i++){
        for (int j = 0; j< mapres.getSizeY();j++){
            if (i == 2 && j == 2) cout << "XX" << " " ;
            else if (i == 8 && j == 5) cout << "YY" << " " ;
            else printf ("%.2i ", mapres.get(i,j));
        }
        cout << endl;
    }
    return 0;
}
