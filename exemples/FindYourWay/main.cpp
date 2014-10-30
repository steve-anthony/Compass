#include "../../include/Compass.hpp"

#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

Compass::PCore::Matrix<int> getMapFromFile(std::string file);
void savePathInFile(std::string file,Compass::PCore::Matrix<int> m,std::list<Compass::PCore::Point> path);

int main()
{
    cout << "Find your way whith astar algo!" << endl;

    /* Load map in matrix */
    Compass::PCore::Matrix<int> mapi = getMapFromFile("mapInput.txt");

    /* Config parameters for the algorithm */
    Compass::PPathfinding::AStar  astar;
    astar.smoothPath(true); //To have smoot path
    astar.init(&mapi);

    /* Find the path from pend to pstart*/
    Compass::PCore::Point pend(2,2);
    Compass::PCore::Point pstart(8,8);
    std::list<Compass::PCore::Point> res = astar.run(pend,pstart);

    /* Save result in file */
    savePathInFile("outFile.txt",mapi,res);

    return 0;
}





/** ... */
Compass::PCore::Matrix<int> getMapFromFile(std::string file){
    Compass::PCore::Matrix<int> res(1,1,1);
    ifstream fichier(file.c_str());

    if(fichier)
    {
        string sx;
        string sy;
        string mot;
        fichier >> sx;
        fichier >> sy;
        int x = atoi(sx.c_str());
        int y = atoi(sy.c_str());
        res.create(x,y,0);

        int i = 0;
        int j = 0;
        while(fichier >> mot)
        {
            if (mot == "--"){

                res.set(i%x,j,Compass::WALL);
            }
            else res.set(i%x,j,atoi(mot.c_str()));
            i++;
            if (i%x == 0 ) j++;
        }
        fichier.close();

    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    return res;
}



void savePathInFile(std::string file,Compass::PCore::Matrix<int> m,std::list<Compass::PCore::Point> path){
        ofstream fichier(file.c_str(), ios::out | ios::trunc);

        if(fichier)
        {
            int n=1;
            Compass::PCore::Point pstart,pend;
            while (!path.empty())
            {
                if (n == 1) pstart = path.front();
                pend = path.front();
                m.set(path.front().x,path.front().y,n);
                //printf("aa %i,%i",path.front().x,path.front().y);
                n++;
                path.pop_front();
            }

            for(int j = 0; j < m.getSizeX();j++){
                for(int i = 0; i < m.getSizeX();i++){
                    if (i == pstart.x && j == pstart.y) fichier << "XX" << " ";
                    else if (i == pend.x && j == pend.y) fichier << "YY" << " ";
                    else if (m.get(i,j) == Compass::WALL) fichier << "--" << " ";
                    else if (m.get(i,j) == 0) fichier << "  " << " ";
                    else{
                        char tmp[10];
                        sprintf (tmp,"%.2i", m.get(i,j));
                        fichier << tmp << " ";
                    }

                }
                fichier << "\n";
            }
            fichier.close();
        }
        else{
            cout << "Erreur à l'ouverture !" << endl;
        }

}



