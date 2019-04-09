/**
*Name : shell.h
*Purpose : PROI Projekt_3 - Polyminoes
*@author Patrycja Cieplicka
*@version 1.0 1/04/2019
*/

#ifndef _SHELL_H_
#define _SHELL_H_

#include "listofpolyminoes.h"

//Klasa reprezentującą powłokę programu - to w niej wykonuje się algorytm
class Shell{

    public:
        Shell();
        ~Shell();
        void action();
        void solve();
        void printStart();

    private:
        std::vector < Base* > polyminoes;       //tablica wskaznikow na polymina
        Board board;                            //plansza
        int N = 0;                              //dlugosc planszy
        int M = 0;                              //szerokosc planszy

        void addPolys();
        void generatePolys(int &number);
        void displayAvailable();
        void displayHelp();
        void getBoard();
        void printPolys();
        int getInt(int x1, int x2) const;
        int getInt(int x1) const;
        void clearBufor() const;
        bool checkIfCanProceed();
        bool backtracingAlgorythm(int *temp, int numberOfPolys, int positionX, int positionY, int positonTemp, int option);

};

#endif // _SHELL_H_
