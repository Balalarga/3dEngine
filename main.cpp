#include <iostream>
#include "game.h"

using namespace std;



int main(int argc, char** argv){
    Game g;
    g.init();
    g.start();

    cout<<"End\n";
    return 0;
}
