/**
*Name : Polyminoe.h
*Purpose : PROI Projekt_3 - Polyminoes
*@author Patrycja Cieplicka
*@version 1.0 1/04/2019
*/

#ifndef _LISTOFPOLYMINOES_H_
#define _LISTOFPOLYMINOES_H_

#include "polyminoe.h"
#include <iostream>

// Klasa przechowujaca listy polyminow jednego rodzaju (o takiej samej ilosci klockow)
template <int N>
class ListOfPolyminoes {
    public:
        ListOfPolyminoes();
        ~ListOfPolyminoes();

        //wypisanie list
        friend std::ostream &operator << (std::ostream &exit, ListOfPolyminoes<N> lists){
            for(size_t i = 0; i < lists.NPoly.size() ; i++){
                exit << lists.NPoly[i];
            }
            return exit;
        }

        ListOfPolyminoes<N> operator = (const ListOfPolyminoes<N-1> lists);

        Polyminoe<N> getPolymino(int index);
        size_t getListSize();

    private:
        void addToPoly(Polyminoe<N-1> poly, Point a, int x, int y);
        bool ifPolyExist(Polyminoe<N> temp);
        std::vector< Polyminoe<N> > NPoly;
        void generatePoly(Polyminoe<N-1> poly);
};

//konstruktor dla n=1, czylli jednego polymina, zakonczenie rekurencji przy wywolywaniu konstruktora o innym n
template <>
inline ListOfPolyminoes<1>::ListOfPolyminoes(){
    NPoly.push_back(Polyminoe<1>());
}

template <int N>
size_t ListOfPolyminoes<N>::getListSize(){
    return NPoly.size();
}

template <int N>
Polyminoe<N> ListOfPolyminoes<N>::getPolymino(int index){
    return NPoly[index];
}


template <int N>
ListOfPolyminoes<N>::~ListOfPolyminoes(){

};

//rekurencyjne wywołanie obiektu (lista n polymin powstaje z listy n-1 polymin)
template <int N>
ListOfPolyminoes<N>::ListOfPolyminoes(){
    ListOfPolyminoes<N-1> poly;
    for(size_t i = 0 ; i < poly.getListSize(); ++i ){
        generatePoly( poly.getPolymino(i) );
    }
};

//sprawdzenie czy takie polymino juz istnieje
template <int N>
bool ListOfPolyminoes<N>::ifPolyExist(Polyminoe<N> temp){
    for(size_t i = 0; i < NPoly.size() ; ++i){
        if(NPoly[i] == temp){
            return true;
        }
    }
    return false;
}

//operator = przeciązony ze wzgledu na przepisywaniu wartosci polymina n-1
template<int N>
ListOfPolyminoes<N> ListOfPolyminoes<N>::operator = (const ListOfPolyminoes<N-1> lists){
    Polyminoe<N> temp;
    for(size_t i = 0 ; i < lists.getListSize() ; ++i){
        for(int j = 0; j < lists.getPolymino(i).getSize(); ++j){
            temp.addPoint(lists.getPolymino(i).getPoint(j));
        }
        this->NPoly.push_back(temp);
    }
    return this;
}

template <int N>
void ListOfPolyminoes<N>::generatePoly(Polyminoe<N-1> poly){
    for(size_t i = 0; i < poly.getSize() ; ++i){                                                    //dodawanie do kazdego kwadratu w polyminie sąsiedni kwadrat, jesli to mozliwe
        addToPoly(poly, poly.getPoint(i), 0,1);
        addToPoly(poly, poly.getPoint(i), 1,0);
        addToPoly(poly, poly.getPoint(i), 0,-1);
        addToPoly(poly, poly.getPoint(i), -1,0);
    }
}

//funkcja realizujaca dodawanie kwadratu(punktu) do polymina
template <int N>
void ListOfPolyminoes<N>::addToPoly(Polyminoe<N-1> poly, Point a, int x, int y){
    Polyminoe<N> temp;
    Point temporary;
    temp = poly;
    temporary = a + Point(x,y);
    if( !temp.ifPointInPoly(temporary) ){
        temp.addPoint(temporary);
        temp.translateToOrigin();
        if(!ifPolyExist(temp)){
            NPoly.push_back(temp);
        }
    }
}




#endif // _LISTOFPOLYMINOES_H_

