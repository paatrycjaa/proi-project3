/**
*Name : Polyminoe.h
*Purpose : PROI Projekt_3 - Polyminoes
*@author Patrycja Cieplicka
*@version 1.0 1/04/2019
*/

#ifndef _POLYMINOE_H_
#define _POLYMINOE_H_

#include <vector>
#include <iostream>

#include "point.h"

//Klasa bazowa - INTERFEJS
class Base {

public:

    //metody potrzebne do implementacji algorytmu
    virtual ~Base(){};
    virtual void movePoly(int x, int y) = 0;
    virtual void placePoly(Board &board, int x, int y, int color) = 0;
    virtual bool checkifCorrectPlace(Board board, int n, int m) const = 0;
    virtual void backPosition(Board &board) = 0;
    virtual void print() const = 0;
    virtual void translateToPlay() = 0;
    virtual size_t getSize() const = 0;

};


//szablon polymina, argument N określa z ilu kwadratów składa się polymino
template <int N>
class Polyminoe: public Base {

public:
    Polyminoe();
    //Polyminoe<N>( const Polyminoe<N> &temp);                                    //stopień polymidu (1 - mono, 2 - domino etc

    virtual ~Polyminoe();
    virtual void movePoly(int x, int y);
    virtual void placePoly(Board &board, int x, int y, int color);
    virtual bool checkifCorrectPlace(Board board, int n, int m) const;
    virtual void backPosition(Board &board);
    virtual void print() const{
        std::cout << (*this);
    }
    virtual size_t getSize() const;
    virtual void translateToPlay();

    Point getPoint(int i) const;
    void addPoint(Point a);
    bool ifPointInPoly(Point p) const;
    void translateToOrigin();

    friend std::ostream &operator<< (std::ostream &exit, const Polyminoe<N> poly){
        int **tab;
        tab = new int*[ N ];
        for(int i=0; i<N;++i){
            tab[i] = new int[N];
        }
        tab = poly.fillTable(tab);
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                if(tab[i][j] == 0)
                    exit << " ";
                else
                    exit << "#";
            }
            exit << std::endl;
        }

        for( int i = 0; i < N; ++i )
            delete [] tab[ i ];
        delete [] tab;

        return exit;
    }


    bool operator== (const Polyminoe<N> poly);
    Polyminoe<N> operator=(const Polyminoe<N-1> poly);

private:
    std::vector<Point> points;
    int** fillTable(int **tab) const;
    int findHow(int minRow) const;
    void setPolyminoes();
    int findMinRow() const;
    int findMinColumn() const;

};

//metoda, która wstawia polymino w dane miejse na planszy
template <int N>
void Polyminoe<N>::placePoly(Board &board, int x, int y, int color){
    for(size_t i = 0; i < points.size() ; ++i){
        board.setSquare(points[i].getX(), points[i].getY(), color);
    }
}

//metoda przesuwająca polymino na dane miejsce
template <int N>
void Polyminoe<N>::movePoly(int x, int y){
    for(size_t i = 0; i < points.size() ; ++i){
            points[i].changePoint(-x, -y);
        }

}

//metoda sprawdzająca czy polymino może być postawione w dane miejsce na planszy
template <int N>
bool Polyminoe<N>::checkifCorrectPlace(Board board, int n, int m) const{
    for(size_t i = 0; i < points.size() ; ++i){
        if((points[i].getX() >= n) ||  (points[i].getX() < 0) || (points[i].getY() < 0) || (points[i].getY() >= m)){
            return false;
            }
        if (board.getValue(points[i].getX(), points[i].getY()) > 0){
            return false;
        }
    }
    return true;
}

//metoda usuwajaca polymino z plansy i przywracajaca do pozycji poczatkowej
template <int N>
void Polyminoe<N>::backPosition(Board &board){
    for(size_t i = 0; i < points.size() ; ++i){
        board.setSquare(points[i].getX(), points[i].getY(), 0);
    }
    translateToPlay();
}

/*template <int N>
Polyminoe<N>::Polyminoe( const Polyminoe &temp ){
    for(size_t j = 0; j < temp.getSize(); ++j){
        this->points.push_back(temp.getPoint(j));
    }
}*/

template <int N>
bool Polyminoe<N>::operator== (const Polyminoe<N> poly){
    int value = 0;

    for(int i = 0; i < N; i++){
        if( ifPointInPoly(poly.points[i]) ){
            value++;
        }
    }
    if(value == N){
        return true;
    }
    else return false;
}

//metoda przygotowująca polymino do wydruku - wstawianie go w tablice NxN
template<int N>
int** Polyminoe<N>::fillTable(int **tab) const{
    int** temp = tab;
    for(int i = 0; i < N; ++i){
        for( int j = 0; j < N; ++j){
            if( ifPointInPoly( Point(i,j) ) ){
               temp[i][j] = 1;
            }
            else{
               temp[i][j] = 0;
            }
        }
    }
    return temp;
}

//sprawdzenie czy kwadrat pojawił się juz w polyminie
template<int N>
bool Polyminoe<N>::ifPointInPoly(Point p) const {
    for(size_t i = 0; i < points.size() ; ++i){
        if(points[i].getX() == p.getX() && points[i].getY() == p.getY()){
            return true;
        }
    }
    return false;
}

//metoda przywracajaca polymino do ukladu poczatkowego, dobre do wydruku
template <int N>
void Polyminoe<N>:: translateToOrigin(){
    int minRow = findMinRow();
    int minCol = findMinColumn();
        for(size_t i = 0; i < points.size() ; ++i){
            points[i].changePoint(minRow, minCol);
        }
}

//metoda przygotowujaca polymino do wykorzystania przez algorytm
template <int N>
void Polyminoe<N>:: translateToPlay(){
    /*if(ifPointInPoly(Point(0,0))){
        return;
    }*/
    int minRow;
    int minCol;
    while(!ifPointInPoly(Point(0,0))){
        minRow = findMinRow();
        minCol = findHow(minRow);
        for(size_t i = 0; i < points.size() ; ++i){
            points[i].changePoint(minRow, minCol);
        }
    }
}

//metoda zliczajaca o ile trzeba przesunac punkty w minimalnej row
template <int N>
int Polyminoe<N>:: findHow(int minRow) const{
    int minCol = N;
	for(size_t i = 0; i < points.size() ; ++i){
		if(points[i].getX() == minRow)
            if( minCol > points[i].getY())
                minCol = points[i].getY();
        }
    return minCol;
}

template <int N>
Polyminoe<N> Polyminoe<N> ::operator=(const Polyminoe <N-1> poly){
    this -> points.clear();
    for(size_t j = 0; j < poly.getSize(); j++){
        this->points.push_back(poly.getPoint(j));
    }
    return *this;
}


template <int N>
Polyminoe<N>::Polyminoe(){
    if(points.empty()){
        setPolyminoes();
    }
};


template <int N>
Polyminoe<N>::~Polyminoe(){

};

template <int N>
void Polyminoe<N>::setPolyminoes(){
    points.push_back(Point(0,0));
}

template <int N>
void Polyminoe<N>::addPoint(Point a){
    points.push_back(a);
}

template <int N>
Point Polyminoe<N>::getPoint(int i) const{
    return points[i];
}

template <int N>
size_t Polyminoe<N>::getSize() const{
    return points.size();
}

template <int N>
int Polyminoe<N>::findMinRow() const{
    int minrow = N;
    for(size_t i = 0; i < points.size() ; i++){
        if(minrow > points[i].getX()){
            minrow = points[i].getX();
        }
    }
    return minrow;
}

template <int N>
int Polyminoe<N>::findMinColumn() const{
    int mincolumn = N;
    for(size_t i = 0; i < points.size() ; i++){
        if(mincolumn > points[i].getY()){
                mincolumn = points[i].getY();
        }
    }
    return mincolumn;
}

#endif // _POLYMINOE_H_
