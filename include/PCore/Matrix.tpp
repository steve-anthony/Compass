#include "Matrix.hpp"
#include <iostream>

namespace Compass{
namespace PCore{


template<typename Type>
Matrix<Type>::Matrix()
{
    //tab = NULL;
    //create(0,0,NULL);
}

template<typename Type>
Matrix<Type>::Matrix(int _x,int _y,Type _val)
{
    //tab = NULL;
    create(_x,_y,_val);
}

template<typename Type>
void Matrix<Type>::create(int _x,int _y,Type _val)
{
    clear();
    x = _x;
    y = _y;

	for(int i = 0;i < x;i++)
        for(int j = 0;j < y;j++){
            //mymap.insert ( std::pair<std::pair<int,int>,Type>(std::pair<int,int>(i,j),_val) );
            mymap[std::pair<int,int>(i,j)] = _val;
        }
		/*
    tab = new Type*[x];
    for (int i = 0; i < x; i++)
        tab[i] = new Type[y];

    for(int i = 0;i < x;i++)
        for(int j = 0;j < y;j++){
            tab[i][j] = _val;
        }
*/
}

template<typename Type>
void  Matrix<Type>::copy(Matrix<Type> const  matrix) const {

/*
    create(matrix.getSizeX(),matrix.getSizeY(),matrix.get(0,0));
    for(int i = 0;i < x;i++)
        for(int j = 0;j < y;j++){

            tab[i][j] = matrix.get(i,j);
            //std::cout << i << " - " << j << " - " << matrix.get(i,j) << std::endl;
        }*/
}


template<typename Type>
void Matrix<Type>::clear()
{
	mymap.clear();
    /*if (tab != NULL ){

        delete[] tab;
    }
    tab = NULL;*/
}

template<typename Type>
Matrix<Type>::~Matrix()
{
    clear();
}

template<typename Type>
Type Matrix<Type>::get(int _x,int _y) const {
    return mymap.find(std::pair<int,int>(_x,_y))->second;
}

template<typename Type>
void Matrix<Type>::set(int _x,int _y,Type val) {
    //mymap.insert ( std::pair<std::pair<int,int>,Type>(std::pair<int,int>(_x,_y),val)
    //std::pair<int,int>(_x,_y);
	mymap[std::pair<int,int>(_x,_y)] = val;
}

}}


