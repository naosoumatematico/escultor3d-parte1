#include <iostream>
#include "sculptor.h"
using namespace std;

int main(void){
    // sculptor-main por enquanto sera um arquivo de teste, seguindo o exemplo 'trono' do professor

    // cria um escultor cuja matriz tem 10x10x10 voxels (testa o construtor da classe)
    Sculptor trono(10, 10, 10);

    // para mudar a cor do voxel (testa o metodo setColor)
    trono.setColor(0,0,1.0,1.0); // cor atual definida como azul
    
    return 0;
}