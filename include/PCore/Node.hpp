#ifndef NODE_H
#define NODE_H


#include "Point.hpp"

namespace Compass{
namespace PCore{

/** Struct for a node of the researh */
class Node
{
public:
    Node();
    Node( int _gScore,int _fScore);
    int score;
    int gScore;
    int fScore;
    Compass::PCore::Point position;
    Node * parent;
    bool verified;
    //int y;
};

}}

#endif // NODE_H
