// arquivo de definicao da classe; aqui ocorre a implementacao dos metodos da classe

#include "sculptor.h" // inclusao do header da classe

//implementacao do construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    // atribuicao das dimensoes da matriz 3D de voxels
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // processo de alocacao dinamica da matriz 3D

    // v passa a apontar para uma regiao de memoria que pode conter 'nx' ponteiro para ponteiro para Voxel 
    v = new Voxel** [nx];

    // laco for percorre todos os elementos v[i] e eles passam a apontar para regioes de memoria que podem conter cada uma 'ny' ponteiros para Voxel
    for(int i = 0; i < nx; i++){
        v[i] = new Voxel* [ny];
    }

    // lacos for aninhados percorres v[i][j] e eles passam a apontar para regioes de memoria que podem conter cada uma 'nz' Voxel
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            v[i][j] = new Voxel [nz];
        }
    }

    // lacos for aninhados para desativar os voxels
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                v[i][j][k].show = false;
            }
        }
    }
}