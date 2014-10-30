#ifndef POINT_H
#define POINT_H

namespace Compass{
namespace PCore{

/** Struct of a point */
class Point
{
    public:
        /** Default constructor */
        Point();
        /** Default constructor */
        Point(int _x,int _y);

        /** Position X */
        int x;

        /** Position Y */
        int y;

};

}}

#endif // POINT_H
