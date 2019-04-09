/**
*Name : point.h
*Purpose : PROI Projekt_3 - Polyminoes
*@author Patrycja Cieplicka
*@version 1.0 1/04/2019
*/

#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

//Klasa punkt obrazująca jeden kwadrat w polyminie
class Point {

public:
    Point();
    Point(int x, int y);
    ~Point();
    int getX() const;
    int getY() const;
    friend Point operator+(const Point &one, const Point &two);
    void changePoint(int a, int b);
    void setPoint(int a, int b);

private:
    int x;
    int y;

};

//Klasa będąca planszą

class Board {

public:
    Board(int n, int m);
    Board(){ setBoard(); };
    ~Board();
    void deleteBoard();
    void setSquare(int x, int y, int val);
    int getValue(int x, int y);
    void setBoard();
    friend std::ostream& operator <<(std::ostream &exit, const Board board);

private:
    int **tab;
    int N = 0;                                          //w pionie
    int M = 0;                                          // w poziomie
};



#endif // _POINT_H_
