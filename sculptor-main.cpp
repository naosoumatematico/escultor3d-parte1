#include <iostream>
#include "sculptor.h"
using namespace std;

int main(void){
    // sculptor-main por enquanto sera um arquivo de teste

    // construtor da classe criando uma matriz do tamanho necessario para uma pixel art de coracao
    Sculptor heart(15, 14, 1);
    // seta a cor vermelha
    heart.setColor(1.0, 0.0, 0.0, 1.0);
    
    // desenha a subida e a descida da parte inferior em um loop so
    for(int x = 0; x < 7; x++){
        heart.putVoxel(x, 7 - x, 0);
        heart.putVoxel(x + 8, x + 1, 0);
    }

    // desenha a pontinha
    heart.putVoxel(7, 0, 0);

    // desenha as retas verticais que ligam a parte inferior a superior em um loop so
    for (int y = 8; y < 12; y++){
        heart.putVoxel(0, y, 0);
        heart.putVoxel(14, y, 0);
    }

    // desenha as retas horizontais da parte superior em um loop so
    for(int x = 2; x < 6; x++){
        heart.putVoxel(x, 13, 0);
        heart.putVoxel(x + 7, 13, 0);
    }

    // desenha os voxels faltantes
    heart.putVoxel(1, 12, 0);
    heart.putVoxel(6, 12, 0);
    heart.putVoxel(7, 11, 0);
    heart.putVoxel(8, 12, 0);
    heart.putVoxel(13, 12, 0);
    

    // metodo writeOFF vibecodado temporario
    heart.writeOFF("heart.off");

    return 0;
}