/**
*Name : Polyminoe.h
*Purpose : PROI Projekt_3 - Polyminoes
*@author Patrycja Cieplicka
*@version 1.0 1/04/2019
*/


#include "point.h"
using namespace std;

//Implementacja klas obsługuących punkt(kwadrat polymina) oraz planszę

Point::Point(){

};

Point::Point(int x, int y) : x(x), y(y){

};

Point::~Point(){

};

int Point::getX() const{
    return x;
}

int Point::getY() const{
    return y;
}

void Point::changePoint(int a, int b){
    x = x - a;
    y = y - b;
}

void Point::setPoint(int a, int b){                                         //ustawienie punktow
    x = a;
    y = b;
}

Point operator+(const Point &one, const Point &two){
    Point temp(one.getX()+two.getX(), one.getY()+two.getY());
    return temp;
}




Board::Board(int n, int m) : N(n) , M(m){                                   //plansza to tablica dwuwymiarowa
    tab = new int*[ N ];

    for(int i = 0; i < N; ++i ){
        tab[i] = new int [ M ];
    }

    setBoard();
}

Board::~Board(){

}

void Board::deleteBoard(){
    if(N != 0){
        for( int i = 0; i < N; ++i ){
            delete [] tab[ i ];
        }
        delete [] tab;
    }
}

void Board::setBoard(){                                                 //wyczyszczenie planszy
    for(int i = 0 ; i < N; ++i){
        for(int j = 0; j < M; ++j){
            tab[i][j] = 0;
        }
    }
}

void Board::setSquare(int x, int y, int val){                           //zapelnienie jednego kwadratu na planszy
    tab[x][y] = val;
}

int Board::getValue(int x, int y){
    return tab[x][y];
}

ostream &operator <<(ostream &exit, const Board board){
    for(int i = 0; i < board.N; ++i){
        for(int j = 0; j < board.M; ++j){
            exit << board.tab[i][j] << "\t";
        }
        exit << endl;
    }
    return exit;
}
