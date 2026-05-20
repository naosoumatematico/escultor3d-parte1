// programa de teste para a classe Sculptor. o teste sera feito com 2 desenhos:
// uma pixel art de coracao tirada do minecraft 
// o trono.off do site do professor sobre o projeto

#include "sculptor.h"

int main(void){
    // construtor da classe criando uma matriz do tamanho necessario para uma pixel art de coracao
    Sculptor heart(15, 14, 1);

    // seta a cor preta para desenhar o contorno
    heart.setColor(0.0, 0.0, 0.0, 1.0);
    
    // ===============================
    // desenho do contorno do coracao
    // ===============================

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

    // ===============================
    // pintura do interior do coracao
    // ===============================

    // seta a cor vermelha para o interior do coracao
    heart.setColor(1.0, 0.0, 0.0, 1.0);

    for(int x = 2; x < 6; x++){
        heart.putVoxel(x, 12, 0);
        heart.putVoxel(x + 7, 12, 0);
    }

    for(int x = 1; x < 7; x++){
        heart.putVoxel(x, 11, 0);
        heart.putVoxel(x + 7, 11, 0);
    }

    heart.putBox(1, 13, 7, 10, 0, 0);

    for(int x = 2; x < 13; x++){
        heart.putVoxel(x, 6, 0);
    }

    for(int x = 3; x < 12; x++){
        heart.putVoxel(x, 5, 0);
    }

    for(int x = 4; x < 11; x++){
        heart.putVoxel(x, 4, 0);
    }

    for(int x = 5; x < 10; x++){
        heart.putVoxel(x, 3, 0);
    }

    for(int x = 6; x < 9; x++){
        heart.putVoxel(x, 2, 0);
    }

    heart.putVoxel(7, 1, 0);

    // ===============================
    // pintura do ponto luminoso no coracao
    // ===============================

    heart.setColor(1.0, 1.0, 1.0, 1.0);

    for(int y = 9; y < 11; y++){
        heart.putVoxel(2, y, 0);
        heart.putVoxel(3, y + 1, 0);
    }

    heart.putVoxel(4, 11, 0);

    // ===============================
    // criacao e salvamento do arquivo .off com o desenho
    // ===============================

    heart.writeOFF("heart.off");

    // exemplo trono.off
    // cria um escultor cuja matriz tem 10x10x10 voxels
    Sculptor trono(10,10,10);
    // para mudar a cor do voxel
    trono.setColor(0,0,1.0,1.0); // azul
    // ativa os voxels na faixa de [x,y,z] pertencendo a [0-9]
    trono.putBox(0,9,0,9,0,9);
    // desativa os voxels na faixa de [x,y,z] pertencendo a [0-9]
    trono.cutBox(1,8,1,9,1,9);
    // grava a escultura digital no arquivo "trono.off"
    trono.writeOFF("trono.off");

    // exemplo excultura.off
    Sculptor escultura(2, 2, 2);

    escultura.setColor(0, 1, 0, 1);
    escultura.putVoxel(0, 0, 0);

    escultura.setColor(1, 0, 0, 0.8);
    escultura.putVoxel(1, 0, 0);

    escultura.setColor(0, 0, 1, 1);
    escultura.putVoxel(0, 1, 0);

    escultura.setColor(1, 1, 0, 0.5);
    escultura.putVoxel(0, 0, 1);

    escultura.writeOFF("escultura.off");
    
    return 0;
}