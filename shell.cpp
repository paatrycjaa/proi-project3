/**
*Name : shell.cpp
*Purpose : PROI Projekt_3 - Polyminoes
*@author Patrycja Cieplicka
*@version 1.0 1/04/2019
*/

#include <limits>
#include <iostream>

#include "shell.h"
using namespace std;

//implementacja klasy reprezentującą powłokę programu - to w niej wykonuje się algorytm

Shell::Shell(){
    printStart();
};

//zwolnenie pamieci w destruktorze
Shell::~Shell(){
    board.deleteBoard();
    if(!(polyminoes.size() == 0)){
        for(size_t i = 0; i < polyminoes.size(); ++i){
            delete polyminoes[i];
        }
        polyminoes.clear();
    }
};

void Shell::addPolys(){                                                                         //metoda dodająca polymina biorące udzial w grze
    if(!(polyminoes.size() == 0)){                                                              //czyszczenie wektora trzymajcego wskazniki polymin
        for(size_t i = 0; i < polyminoes.size(); ++i){
            delete polyminoes[i];
        }
        polyminoes.clear();
    }
    int number = 0;                                                                             //zmienna mowiaca ile kwadratow zaplenionych
    int process = 1;
    while(process){
        cout << "1 - dodaj polymino" << endl;
        cout << "2 - skończ dodawanie" << endl;
        switch(getInt(1,2)){
            case 1:
                generatePolys(number);
                cout << "Zapelnione kwadraciki:" << number << endl;
                break;
            case 2:
                cout << "Wylosowane polymina:" << endl;
                printPolys();
                process = 0;
                break;
            default:
                cout << "Blad";
                break;

        }
    }
   for(size_t i = 0; i < polyminoes.size(); ++i){                                               //przesuniecie polymin do pozycji pozwaljac
        polyminoes[i]->translateToPlay();
   }

};

void Shell::printPolys(){
    for(size_t i = 0; i < polyminoes.size(); ++i){
        polyminoes[i]->print();
        cout << endl;
    }
}


void Shell::getBoard(){                                                                         //czysczenie planszy
    if (!(N == 0)){
        board.deleteBoard();
    }
    cout << "Podaj długość tablicy" << endl;
    N = getInt(1);
    cout << "Podaj szerokość tablicy" << endl;
    M = getInt(1);

    board = Board(N,M);
    cout << board;
}

bool Shell::checkIfCanProceed(){                                                                    //sprawdzenie czy wybrane polymina sa w stanie wypelnic plansze
    int number = 0;
    for(size_t i = 0; i < polyminoes.size(); ++i){                                                  //ze wzgledu na licze
        number+= static_cast < int > (polyminoes[i]->getSize());
    }

    if(M > 0 && N > 0 && number == M*N)
        return true;

    else return false;

}

bool Shell::backtracingAlgorythm( int *temp, int numberOfPolys, int positionX, int positionY, int positionTemp, int option){
    //positionX //positonY //positionTemp - przechowuja informacje o aktualnej pozycji na planszy i w tablicy polymin
    //petla po wszystkich polyminach
    for(int i = 0; i < numberOfPolys; ++i){
        //sprawdzenie czy polymino juz uzyte, jesli tak to przesuwamy na pozycje
        if(temp[i] == 0){
            polyminoes[i]-> movePoly(positionX, positionY);
        }
        else continue;
        //sprawdzenie, czy wstawione prawidłowo, jesli nie to wraca
        if(! polyminoes[i]-> checkifCorrectPlace(board, N, M)){
            polyminoes[i]-> translateToPlay();
            temp[i] = 0;
            continue;
        }

        //wstawiam polymino na dana pozyce
        positionTemp = i;
        polyminoes[positionTemp] -> placePoly(board, positionX, positionY, positionTemp+1);
        temp[positionTemp] = 1;

        //ile miejsc zajetych
        int squareTofill = 0;

        for(int j = 0; j < numberOfPolys; j++){
            if(temp[j] > 0) squareTofill++;
        }

        //sprawdzenie czy to rozwiazanie, jesli tak to wypisuje i wraca
        if(squareTofill == numberOfPolys){
            cout << board << endl;
            polyminoes[positionTemp] -> backPosition(board);
            temp[positionTemp] = 0;
            return true;
        }

        //ustawienie pozycji na nowe pole
        int exist = 0;
        int tempx = positionX;
        int tempy = positionY;
        int x = positionX;
        int y = positionY;
        //znalezienie wolnej pozycji
        while(x < N && !exist){
            while(y < M && !exist){
                if(board.getValue(x,y) == 0){
                    positionX = x;
                    positionY = y;
                    exist = 1;
                    break;
                }
                y++;
            }
            x++;
            y=0;
        }

        //option 2 - wszytskie rozwiazania, option1 - tylko jedno
        if(option == 2){
            backtracingAlgorythm(temp, numberOfPolys, positionX, positionY, positionTemp, option );
        }

        else{
            if( backtracingAlgorythm(temp, numberOfPolys, positionX, positionY, positionTemp, option ) == true){
                return true;
            }
        }
        // powrot
        polyminoes[positionTemp] -> backPosition(board);
        temp[positionTemp] = 0;
        positionX = tempx;
        positionY = tempy;
    }
    return false;
}

void Shell::solve(){
    if(!checkIfCanProceed()){
        cout << "Suma wszystkich kwadratów polymin nie jest równa polom na planszy." << endl;
        cout <<" Aby możliwe było znalezienie rozwiąń muszą się zgadzać i być większe od zera" << endl;
        return;
    }

    cout << "1 - wypisz przykladowe rozwiazanie" << endl;
    cout << "2 - wypisz wszystkie rozwiązania" << endl;

    int option = getInt(1,2);                                                                       //wybranie opcji algorytmu
    int numberOfPolys = static_cast < int >(polyminoes.size());                                     //liczba polymin
    int *temp = new int[numberOfPolys]();                                                           //inicjalizacja tablicy, w ktorej pbedziemy przechowywac, czy polymino zostalo
    int positionTemp = 0;                                                                           //juz wstawione, czy jeszcze nie

    if(option == 1){
        cout << "Przykladowe rozwiazanie:" << endl;                                                 //zaczynamy z pozycji 0,0
        if(backtracingAlgorythm(temp, numberOfPolys, 0, 0, positionTemp, option) == false){
            cout << "Brak rozwiązań" << endl;
        }
        board.setBoard();
    }

    else{
        cout << "Istniejące rozwiązania:" << endl;
        backtracingAlgorythm(temp, numberOfPolys, 0, 0, positionTemp, option);
        board.setBoard();
    }

    for(size_t i = 0; i < polyminoes.size(); ++i){                                                  //przywracamy polymina do pozycji startowej
        polyminoes[i]->translateToPlay();
    }

    delete [] temp;
};

void Shell::displayAvailable(){
    switch (getInt(2,8)){
        case 2:
            cout << "Dostępne możliwości" << endl;
            cout << ListOfPolyminoes<2>() << endl;
            break;
        case 3:
            cout << "Dostępne możliwości" << endl;
            cout << ListOfPolyminoes<3>() << endl;
            break;
        case 4:
            cout << "Dostępne możliwości" << endl;
            cout << ListOfPolyminoes<4>() << endl;
            break;
        case 5:
            cout << "Dostępne możliwości" << endl;
            cout << ListOfPolyminoes<5>() << endl;
            break;
        case 6:
            cout << "Dostępne możliwości" << endl;
            cout << ListOfPolyminoes<6>() << endl;
            break;
        case 7:
            cout << "Dostępne możliwości" << endl;
            cout << ListOfPolyminoes<7>() << endl;
            break;
        case 8:
            cout << "Dostępne możliwości" << endl;
            cout << ListOfPolyminoes<8>() << endl;
            break;
        default:
            cout << "Blad" << endl;
            break;
    }

}
void Shell::displayHelp(){
    cout << "1 - aby określić rozmiar planszy" << endl;
    cout << "2 - aby podać jakie polymina mają brać udział w układaniu" << endl;
    cout << "3 - aby podać rozwiązanie" << endl;
    cout << "4 - wyświetlić możliwe polymina" << endl;
    cout << "5 - wyswietlić instrukcje" << endl;
    cout << "6 - wyjść z programu" << endl;
}

int Shell::getInt(int x1, int x2) const{                                                            //metoda wczytująca liczbę całkowitą z podanego przedziału
    int number;                                                                                     //sprawdza poprawność wprowadzonych danych, prosi o ponowne wpisanie w przypadku bledu
    while (!(cin >> number) || number < x1 || number > x2 || cin.peek() != '\n'){
        cout << "Wpisz liczbę z przedziału "<< x1 <<"-"<< x2 << endl;
        clearBufor();
    }
    return number;
}

int Shell::getInt(int x1) const{                                                                  //metoda wczytująca liczbę całkowitą z podanego przedziału
    int number;                                                                                   //sprawdza poprawność wprowadzonych danych, prosi o ponowne wpisanie w przypadku bledu
    while (!(cin >> number) || number < x1 || cin.peek() != '\n'){
        cout << "Wpisz liczbę całkowitą z większą od "<< x1 << endl;
        clearBufor();
    }
    return number;
}


void Shell::clearBufor() const{                                                                           //metoda czyszcząca bufor
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Shell::action(){                                                                               //metoda pozwalająca na obsługę menu przez użytkownika
    int process = 1;
    while(process){
        switch(getInt(1,7)){
            case 1:
                getBoard();                                                                         // 1 - okreslenei tablicy
                break;
            case 2:                                                                                 // 2 - dodanie polymina
                addPolys();
                break;
            case 3:                                                                                 // 3 - ulozenie polymina
                solve();
                break;
            case 4:                                                                                 //wyswietlenie mozliwych polymin
                cout << "Podaj z ilu kwadratów ma się składać polymino" << endl;                                                                               // 2 -
                displayAvailable();
                break;
            case 5:
                displayHelp();                                                                      //pomoc
                break;
            case 6:                                                                                 //WYJSCIE
                process = 0;
                break;
            default:
                cout << "Blad" << endl;
                break;
        }
    }
}

void Shell::printStart(){
    cout << "Witaj w programie układającym polymino" << endl;
    cout << "Wybierz:" << endl;
    cout << "1 - aby określić rozmiar planszy" << endl;
    cout << "2 - aby podać jakie polymina mają brać udział w układaniu" << endl;
    cout << "3 - aby podać rozwiązanie" << endl;
    cout << "4 - wyświetlić możliwe polymina" << endl;
    cout << "5 - wyswietlić instrukcje" << endl;
    cout << "6 - wyjść z programu" << endl;
}

void Shell::generatePolys( int &number){
    cout << "Podaj z ilu kwadratów ma sie składać polymino" << endl;
    int variable = getInt(2,8);
    cout << "Podaj ile chcesz polymin tego rodzaju" << endl;
    int howMany = getInt(0);
    number += (variable*howMany);                                                       //obliczenie ile dodanych kwadratów, mnozenie liczby kwadratow w polyminie razy ilosc ich wystpaienia
    size_t listSize;

    if(variable == 2){                                                                  //wygenerowanie polymin z listy skladajacych sie z polymin n-kwadratow
        ListOfPolyminoes<2> lists;
        listSize = lists.getListSize();
        for(int i = 0; i < howMany; ++i){
            Polyminoe<2> temp = lists.getPolymino(rand()%(static_cast < int >(listSize)));
            polyminoes.push_back(new Polyminoe<2> (temp));                              //dodanie fo tablicy wskaznikow
        }
    }
    else if(variable == 3){
        ListOfPolyminoes<3> lists;
        listSize = lists.getListSize();
        for(int i = 0; i < howMany; ++i){
            Polyminoe<3> temp = lists.getPolymino(rand()%(static_cast < int >(listSize)));
            polyminoes.push_back(new Polyminoe<3> (temp));
        }
    }
    else if(variable == 4){
        ListOfPolyminoes<4> lists;
        listSize = lists.getListSize();
        for(int i = 0; i < howMany; ++i){
            Polyminoe<4> temp = lists.getPolymino(rand()%(static_cast < int >(listSize)));
            polyminoes.push_back(new Polyminoe<4> (temp));
        }
    }
    else if(variable == 5){
        ListOfPolyminoes<5> lists;
        listSize = lists.getListSize();
        for(int i = 0; i < howMany; ++i){
            Polyminoe<5> temp = lists.getPolymino(rand()%(static_cast < int >(listSize)));
            polyminoes.push_back(new Polyminoe<5> (temp));
        }
    }
    else if(variable == 6){
        ListOfPolyminoes<6> lists;
        listSize = lists.getListSize();
        for(int i = 0; i < howMany; ++i){
            Polyminoe<6> temp = lists.getPolymino(rand()%(static_cast < int >(listSize)));
            polyminoes.push_back(new Polyminoe<6> (temp));
        }
    }
    else if(variable == 7){
        ListOfPolyminoes<7> lists;
        listSize = lists.getListSize();
        for(int i = 0; i < howMany; ++i){
            Polyminoe<7> temp = lists.getPolymino(rand()%(static_cast < int >(listSize)));
            polyminoes.push_back(new Polyminoe<7> (temp));
        }
    }
    else if(variable == 8){
        ListOfPolyminoes<8> lists;
        listSize = lists.getListSize();
        for(int i = 0; i < howMany; ++i){
            Polyminoe<8> temp = lists.getPolymino(rand()%(static_cast < int >(listSize)));
            polyminoes.push_back(new Polyminoe<8> (temp));
        }
    }
        return;
}
