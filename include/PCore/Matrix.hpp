#ifndef MATRIX_H
#define MATRIX_H



namespace Compass{
namespace PCore{


template<typename Type>
class Matrix
{
    public:
        /** Default constructor */
        Matrix();
        Matrix(int _x,int _y,Type _val);
        /** Default destructor */
        virtual ~Matrix();

        void create(int _x,int _y,Type _val);
        void copy(Matrix<Type> const  matrix) const ;
        void clear();

        Type get(int _x,int _y) const ;
        void set(int _x,int _y,Type val) const ;

        int getSizeX() const  {return x;}
        int getSizeY() const  {return y;}

    private:

        Type **tab;
        int x,y;
};

}}

#include  "Matrix.tpp"


#endif // MATRIX_H
