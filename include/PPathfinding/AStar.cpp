#include "AStar.hpp"


namespace Compass{
namespace PPathfinding{

AStar::AStar()
{
    closeList = new Compass::PCore::Matrix<Compass::PCore::Node*>(0,0,NULL);
    map = new Compass::PCore::Matrix<int>(0,0,NULL);
    this->isSmoothPath = false;
}

AStar::~AStar()
{
    openList.clear();
    closeList->clear();
    delete closeList;
}

void AStar::init(const Compass::PCore::Matrix<int> * _map){
    //map = _map;
    map->clear();


    map->create(_map->getSizeX(),_map->getSizeY(),NULL);
    for (int i = 0; i< _map->getSizeX();i++)
        for (int j = 0; j< _map->getSizeY();j++){
            map->set(i,j,_map->get(i,j));
        }


}

int AStar::heuristic(Compass::PCore::Point p1,Compass::PCore::Point p2){
    return abs( sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p1.y)) );
}


bool AStar::isInOpenList(Compass::PCore::Node* n){

    return (std::find(openList.begin(), openList.end(), n) != openList.end());
}

bool AStar::isVisited(Compass::PCore::Point position){
    Compass::PCore::Node* n = closeList->get(position.x,position.y);
    return (n->verified);
}

bool AStar::isWall(Compass::PCore::Point position){
    Compass::PCore::Node* n = closeList->get(position.x,position.y);
    return (n->gScore == -1);
}

std::list<Compass::PCore::Node*> AStar::getNeighbors(Compass::PCore::Node* node){

    Compass::PCore::Point position = node->position;
    std::vector<Compass::PCore::Point> positionsNeighbors;



    positionsNeighbors.push_back(Compass::PCore::Point(position.x-1,position.y-1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x+1,position.y+1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x-1,position.y+1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x+1,position.y-1));

    positionsNeighbors.push_back(Compass::PCore::Point(position.x,position.y-1));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x-1,position.y));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x+1,position.y));
    positionsNeighbors.push_back(Compass::PCore::Point(position.x,position.y+1));

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

            if(!isWall(newnode->position)) neighbors.push_back(newnode);
            //newnode->parent = node;



        }
    }
    //        Compass::PCore::Node* neighbor = neighbors.front();


    return neighbors;
}


void AStar::smoothPath(bool activated){

    this->isSmoothPath = activated;
}


bool compareNode (Compass::PCore::Node * first, Compass::PCore::Node * second)
{
    return ( first->fScore < second->fScore );
}


std::list<Compass::PCore::Point> AStar::run(Compass::PCore::Point _startPosition,Compass::PCore::Point _endPosition){

    // RESET
    openList.clear();
    closeList->clear();
    closeList->create(map->getSizeX(),map->getSizeY(),NULL);
    for (int i = 0; i< map->getSizeX();i++)
        for (int j = 0; j< map->getSizeY();j++){
            if (map->get(i,j) != Compass::WALL) closeList->set(i,j,new Compass::PCore::Node(map->get(i,j)+1,0));
            else closeList->set(i,j,new Compass::PCore::Node(map->get(i,j),0));
        }

    //CONF
    startPosition = _startPosition;
    endPosition = _endPosition;
    std::list<Compass::PCore::Point> result;

    //VERIF
    if(isWall(startPosition) || isWall(endPosition)) return result;


    if (not (startPosition.x > 0 &&
            startPosition.y > 0 &&
            startPosition.x < map->getSizeX() &&
            startPosition.y < map->getSizeY()
            ))throw std::logic_error( "Start position is out of map." );


    if (not (endPosition.x > 0 &&
            endPosition.y > 0 &&
            endPosition.x < map->getSizeX() &&
            endPosition.y < map->getSizeY()
            )) throw std::logic_error( "End position is out of map." );


    Compass::PCore::Node * n = closeList->get(startPosition.x,startPosition.y);
    n->position.x = startPosition.x;
    n->position.y = startPosition.y;
    n->gScore = 0;
    n->fScore = n->gScore + heuristic(startPosition,endPosition);

   // std::list<Compass::PCore::Node*> openListFake;
    //openListFake.push_front(n);
    openList.push_front(n);

    startNode = n;


    while (!openList.empty())
    {
       openList.sort (compareNode);
//openListFake.sort (compareNode);
        Compass::PCore::Node * current = openList.front();


        /*while(!openListFake.empty()){
            Compass::PCore::Node * c = openListFake.front();
            cout << c->gScore << " " << c->fScore << endl;
            openListFake.pop_front();

        }
        cout << endl << endl;*/
        /*string gg;
        cin>> gg ;*/

        // GOAL
        if (current->position.x == endPosition.x && current->position.y == endPosition.y){

                Compass::PCore::Node * nend = closeList->get(endPosition.x,endPosition.y);
                Compass::PCore::Node * prevNend = NULL;
                Compass::PCore::Point prevDir;
                result.push_front(Compass::PCore::Point(nend->position.x,nend->position.y));
                while (nend->parent){
                    prevNend = nend;
                    nend = nend->parent;
                    if (this->isSmoothPath ){

                        if(prevNend != NULL){
                            Compass::PCore::Point dir;
                            dir.x =  nend->position.x - prevNend->position.x;
                            dir.y =  nend->position.y - prevNend->position.y;

                            if (!(dir.x == prevDir.x && dir.y == prevDir.y))
                                result.push_front(Compass::PCore::Point(prevNend->position.x,prevNend->position.y));

                            prevDir.x = dir.x;
                            prevDir.y = dir.y;
                        }
                        else result.push_front(Compass::PCore::Point(nend->position.x,nend->position.y));




                    }
                    else{
                        result.push_front(Compass::PCore::Point(nend->position.x,nend->position.y));
                    }

                }

                if (this->isSmoothPath )result.push_front(Compass::PCore::Point(nend->position.x,nend->position.y));


                return result; // path
        }

        std::list<Compass::PCore::Node*> neighbors = getNeighbors(current);


        openList.pop_front();

        current->verified = true; // add to closed list

        while (!neighbors.empty()){

            Compass::PCore::Node* neighbor = neighbors.front();
            neighbors.pop_front();

            if (!neighbor->verified){// si pas dans la closed list on continue

                int gscore = current->gScore + current->score;

                if(!isInOpenList(neighbor) || gscore < neighbor->gScore){

                    neighbor->parent = current;
                    neighbor->gScore = gscore;
                    neighbor->fScore = neighbor->gScore + heuristic(neighbor->position,endPosition);

                    if(!isInOpenList(neighbor)){
                        openList.push_front(neighbor);

                    }
                }


            }

        }
    }
}

}}
