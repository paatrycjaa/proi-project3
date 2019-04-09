#include <iostream>
#include "shell.h"

using namespace std;


int main(){

    srand(time(NULL));
    Shell program = Shell();
    program.action();

    return 0;
}
