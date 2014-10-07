#ifndef ASTAR_H
#define ASTAR_H

#include "../predef.hpp"
#include "../stdafx.hpp"

namespace Compass{
namespace PPathfinding{

bool compareNode (Compass::PCore::Node * first, Compass::PCore::Node * second);


class AStar
{
    public:
        /** Default constructor */
        AStar();
        /** Default destructor */
        virtual ~AStar();

        void init(const Compass::PCore::Matrix<int> * _map);
        std::list<Compass::PCore::Point> run(Compass::PCore::Point _startPosition,Compass::PCore::Point _endPosition);

    protected:
        int heuristic(Compass::PCore::Point p1,Compass::PCore::Point p2);
        std::list<Compass::PCore::Node*> getNeighbors(Compass::PCore::Node* node);
        bool isVisited(Compass::PCore::Point position);
        bool isInOpenList(Compass::PCore::Node* n);
        bool isWall(Compass::PCore::Point position);


    private:
        Compass::PCore::Matrix<Compass::PCore::Node*> * closeList;
        std::list<Compass::PCore::Node*> openList;
        Compass::PCore::Point startPosition;
        Compass::PCore::Point endPosition;
        Compass::PCore::Node* startNode;
        Compass::PCore::Matrix<int> * map;


};

}}

#endif // ASTAR_H
