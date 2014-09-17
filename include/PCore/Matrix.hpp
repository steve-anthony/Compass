#ifndef MATRIX_H
#define MATRIX_H



namespace Compass{
namespace PCore{


template<typename Type>
class Matrix
{
    public:
        /** Default constructor */
        Matrix(int _x,int _y,Type _val);
        /** Default destructor */
        virtual ~Matrix();

        void create(int _x,int _y,Type _val);
        void copy(Matrix<Type> matrix);
        void clear();

        Type get(int _x,int _y);
        void set(int _x,int _y,Type val);

        int getSizeX() {return x;}
        int getSizeY() {return y;}

    private:

        Type **tab;
        int x,y;
};

}}

#include  "Matrix.tpp"


#endif // MATRIX_H
