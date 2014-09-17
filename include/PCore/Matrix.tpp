#include "Matrix.hpp"
#include <iostream>

namespace Compass{
namespace PCore{


template<typename Type>
Matrix<Type>::Matrix(int _x,int _y,Type _val)
{
    tab = NULL;
    create(_x,_y,_val);
}

template<typename Type>
void Matrix<Type>::create(int _x,int _y,Type _val)
{
    clear();
    x = _x;
    y = _y;
    tab = new Type*[x];
    for (int i = 0; i < x; i++)
        tab[i] = new Type[y];

    for(int i = 0;i < x;i++)
        for(int j = 0;j < y;j++){
            tab[i][j] = _val;
        }

}

template<typename Type>
void  Matrix<Type>::copy(Matrix<Type> matrix){

    create(matrix.getSizeX(),matrix.getSizeY(),matrix.get(0,0));
    for(int i = 0;i < x;i++)
        for(int j = 0;j < y;j++){

            tab[i][j] = matrix.get(i,j);
            //std::cout << i << " - " << j << " - " << matrix.get(i,j) << std::endl;
        }
}


template<typename Type>
void Matrix<Type>::clear()
{
    if (tab != NULL ){
        /*for (int i = 0; i < x; i++)
            if (tab[i] != NULL ) delete[] tab[i];*/
        delete[] tab;
    }
    tab = NULL;
}

template<typename Type>
Matrix<Type>::~Matrix()
{
    clear();
}

template<typename Type>
Type Matrix<Type>::get(int _x,int _y){
    return tab[_x][_y];
}

template<typename Type>
void Matrix<Type>::set(int _x,int _y,Type val){
    tab[_x][_y] = val;
}

}}


