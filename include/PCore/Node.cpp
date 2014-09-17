#include "Node.hpp"


namespace Compass{
namespace PCore{

Node::Node(): gScore(0),fScore(0){
    verified = false;
}

Node::Node( int _gScore,int _fScore): gScore(_gScore),fScore(_fScore)
{
    verified = false;
}


}}
