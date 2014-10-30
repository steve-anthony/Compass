#ifndef MATRIX_H
#define MATRIX_H



namespace Compass{
namespace PCore{

/**
2D Map of a <Type>
*/
template<typename Type>
class Matrix
{
    public:
        /** Default constructor */
        Matrix();
        Matrix(int _x,int _y,Type _val);
        /** Default destructor */
        virtual ~Matrix();

        /** Init matrix whit size and the choosen type */
        void create(int _x,int _y,Type _val);

        /** Copy the matrix passed in parameter */
        void copy(Matrix<Type> const  matrix) const ;

        /** Reset matrix */
        void clear();

        /** Get value at the point (x,y) */
        Type get(int _x,int _y) const ;

        /** Set value at the point (x,y) */
        void set(int _x,int _y,Type  val) ;

        /** Get size X */
        int getSizeX() const  {return x;}

        /** Get size Y*/
        int getSizeY() const  {return y;}

    private:
        std::map<std::pair<int,int>,Type> mymap;
        int x,y;
};

}}

#include  "Matrix.tpp"


#endif // MATRIX_H
