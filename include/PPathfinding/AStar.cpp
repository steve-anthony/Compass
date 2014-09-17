#include "AStar.hpp"


namespace Compass{
namespace PPathfinding{

AStar::AStar()
{
    map = new Compass::PCore::Matrix<int>(0,0,0);
    //closeList = new Compass::PCore::Matrix<int>(0,0,0);
    closeList = new Compass::PCore::Matrix<Compass::PCore::Node*>(0,0,NULL);
}

AStar::~AStar()
{
    //dtor
}

void AStar::init(Compass::PCore::Matrix<int> _map){

    //map->create(_map.getSizeX(),_map.getSizeY(),0);
    //map->copy(_map);

    closeList->create(_map.getSizeX(),_map.getSizeY(),NULL);

    for (int i = 0; i< closeList->getSizeX();i++)
        for (int j = 0; j< closeList->getSizeY();j++){
            closeList->set(i,j,new Compass::PCore::Node(_map.get(i,j),0));
        }



}

int AStar::heuristic(Compass::PCore::Point p1,Compass::PCore::Point p2){
    return abs(sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p1.y)));
}

bool AStar::isInOpenList(Compass::PCore::Node* n){

    std::list<Compass::PCore::Node*> openListCopy = openList;

    while(!openListCopy.empty()){

        if (n == openListCopy.front() ) return true;
        openListCopy.pop_front();

    }

    return false;
}

bool AStar::isVisited(Compass::PCore::Point position){
    Compass::PCore::Node* n = closeList->get(position.x,position.y);
    return (n->verified);
}

std::list<Compass::PCore::Node*> AStar::getNeighbors(Compass::PCore::Node* node){

    Compass::PCore::Point position = node->position;
    std::vector<Compass::PCore::Point> positionsNeighbors;
    positionsNeighbors.push_back(Compass::PCore::Point(position.x-1,position.y-1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x,position.y-1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x+1,position.y-1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x-1,position.y));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x+1,position.y));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x-1,position.y+1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x,position.y+1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x+1,position.y+1));

    std::list<Compass::PCore::Node*> neighbors;
    for(int i =0;i < positionsNeighbors.size();i++){
        if (positionsNeighbors.at(i).x > 0 &&
            positionsNeighbors.at(i).y > 0 &&
            positionsNeighbors.at(i).x < closeList->getSizeX() &&
            positionsNeighbors.at(i).y < closeList->getSizeY()
            ){
        //if ( !isVisited(positionsNeighbors.at(i)) ){

            Compass::PCore::Node* newnode = closeList->get(positionsNeighbors.at(i).x,positionsNeighbors.at(i).y);

            newnode->position.x = positionsNeighbors.at(i).x;
            newnode->position.y = positionsNeighbors.at(i).y;
            //newnode->parent = node;

            neighbors.push_back(newnode);

        }
    }
            Compass::PCore::Node* neighbor = neighbors.front();


    return neighbors;
}


bool compareNode (Compass::PCore::Node * first, Compass::PCore::Node * second)
{
    return ( first->fScore < second->fScore );
}


std::list<Compass::PCore::Point> AStar::run(Compass::PCore::Point _startPosition,Compass::PCore::Point _endPosition){
    startPosition = _startPosition;
    endPosition = _endPosition;

    Compass::PCore::Node * n = closeList->get(startPosition.x,startPosition.y);
    n->position.x = startPosition.x;
    n->position.y = startPosition.y;
    n->fScore = n->gScore + heuristic(startPosition,endPosition);

    openList.push_front(n);

    startNode = n;


    while (!openList.empty())
    {
        openList.sort(compareNode);
        Compass::PCore::Node * current = openList.front();


        /*string gg;
        cin>> gg ;*/


        if (current->position.x == endPosition.x && current->position.y == endPosition.y){

                Compass::PCore::Node * nend = closeList->get(endPosition.x,endPosition.y);
                std::list<Compass::PCore::Point> result;
                result.push_front(Compass::PCore::Point(nend->position.x,nend->position.y));
                while (nend->parent){
                    nend = nend->parent;

                    result.push_front(Compass::PCore::Point(nend->position.x,nend->position.y));
                }


                return result; // path
        }

        std::list<Compass::PCore::Node*> neighbors = getNeighbors(current);


        openList.pop_front();
        current->verified = true;
        /*string lol;
cin >> lol ;*/
        while (!neighbors.empty()){

            Compass::PCore::Node* neighbor = neighbors.front();
            //cout << "lol " << neighbor->verified << " " << neighbor->position.x << " " << neighbor->position.y << endl;
            if (!neighbor->verified){



                int gscore = current->gScore + neighbor->gScore + heuristic(neighbor->position,current->position);


                if(!isInOpenList(neighbor) || gscore < neighbor->gScore){


                    neighbor->parent = current;
                    neighbor->gScore = gscore;
                    neighbor->fScore = neighbor->gScore + heuristic(neighbor->position,endPosition);
                    //cout << neighbor->fScore << " " << neighbor->position.x <<  " " << neighbor->position.y << endl;

                    //cout << "lol " << neighbor->fScore << " " << neighbor->position.x << " " << neighbor->position.y << endl;
                    //cout << "mdr " << neighbor->position.x << " " << neighbor->position.y << " " << neighbor->fScore << endl;
                    if(!isInOpenList(neighbor)) openList.push_front(neighbor);
                }


            }
            neighbors.pop_front();
        }
    }
}

}}
