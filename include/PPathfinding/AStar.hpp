#ifndef ASTAR_H
#define ASTAR_H

#include "../predef.hpp"
#include "../stdafx.hpp"

namespace Compass{
namespace PPathfinding{

/**
Function to compare if a node have a better fscore
*/
bool compareNode (Compass::PCore::Node * first, Compass::PCore::Node * second);


/**
AStar algorithm apply for pathfinding in valued matrix
*/
class AStar
{
    public:
        /** Default constructor */
        AStar();
        /** Default destructor */
        virtual ~AStar();

        /**
        Init whit a height map.
        REM: Const "Compass::WALL" can define an insurmountable obstacle
        */
        void init(const Compass::PCore::Matrix<int> * _map);

        /**
        Define if you want in the result every step of path or just significants points (smoot).
        Set true for smoot path.
        */
        void smoothPath(bool activated);

        /**
        Compute the path form _startPosition to _endPosition
        */
        std::list<Compass::PCore::Point> run(Compass::PCore::Point _startPosition,Compass::PCore::Point _endPosition);

    private:
        /** Distance as the crow flies between too points */
        int heuristic(Compass::PCore::Point p1,Compass::PCore::Point p2);

        /** Get neightboors nodes of a node (point) */
        std::list<Compass::PCore::Node*> getNeighbors(Compass::PCore::Node* node);

        /** Retrun true if the position in the map is already visited by  algorithm */
        bool isVisited(Compass::PCore::Point position);

        /** Check if node is in the openlist */
        bool isInOpenList(Compass::PCore::Node* n);

        /** Retrun if the point at this position is a map */
        bool isWall(Compass::PCore::Point position);

        /** Visited nodes */
        Compass::PCore::Matrix<Compass::PCore::Node*> * closeList;

        /** Node to visit */
        std::list<Compass::PCore::Node*> openList;

        /** Start position for the research */
        Compass::PCore::Point startPosition;

        /** End position for research */
        Compass::PCore::Point endPosition;

        /** Height map */
        Compass::PCore::Matrix<int> * map;

        /** True if you want a smooth path */
        bool isSmoothPath;


};

}}

#endif // ASTAR_H
