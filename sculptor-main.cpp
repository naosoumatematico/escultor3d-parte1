#include <iostream>
#include "sculptor.h"
using namespace std;

int main(void){
    // sculptor-main por enquanto sera um arquivo de teste

    // teste do construtor da classe
    Sculptor escultor(10, 10, 10);

    // teste do metodo setColor
    escultor.setColor(0,0,1.0,1.0);

    // testes do putVoxel fora dos limites da matriz
    escultor.putVoxel(12, 10, 9);
    escultor.putVoxel(-1, 10, 10);

    // testes do putVoxel dentro dos limites da matriz
    escultor.putVoxel(9, 9, 9);
    escultor.putVoxel(3, 5, 9);

    // testes do cutVoxel fora dos limites da matriz
    escultor.cutVoxel(10, 20, 1);
    escultor.cutVoxel(3, 5, 9);

    return 0;
}