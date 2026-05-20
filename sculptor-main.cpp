#include <iostream>
#include "sculptor.h"
using namespace std;

int main(void){
    Sculptor teste(30, 30, 30);

    teste.setColor(1, 0, 0, 1);

    teste.putVoxel(0, 0, 0);
    teste.putVoxel(1, 0, 0);

    teste.cutVoxel(0, 0, 0);

    teste.putBox(5, 15, 5, 15, 5, 15);

    teste.cutBox(5, 10, 5, 10, 5, 10);

    teste.writeOFF("teste.off");

    return 0;
}