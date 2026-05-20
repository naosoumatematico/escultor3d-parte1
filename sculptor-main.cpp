#include <iostream>
#include "sculptor.h"
using namespace std;

int main(void){
    Sculptor teste(11, 11, 11);

    teste.setColor(1, 0, 0, 1);

    teste.putVoxel(10, 10, 10);

    teste.cutVoxel(10, 10, 10);

    teste.putBox(0, 9, 0, 9, 0, 9);

    teste.writeOFF("teste.off");

    return 0;
}