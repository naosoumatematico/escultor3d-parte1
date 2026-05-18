// arquivo de definicao da classe; aqui ocorre a implementacao dos metodos da classe
#include "sculptor.h" // inclusao do header da classe

//implementacao do construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    // atribuicao das dimensoes da matriz 3D de voxels
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // processo de alocacao dinamica da matriz 3D

    // alocacao do eixo x
    v = new Voxel** [nx];

    // alocacao do eixo y; 
    for(int i = 0; i < nx; i++){
        v[i] = new Voxel* [ny];
    }

    // alocacao do eixo z
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            v[i][j] = new Voxel [nz];
        }
    }

    // os voxels sao inicialmente desativados
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                v[i][j][k].show = false;
            }
        }
    }
}

// implementacao do destrutor da classe
Sculptor::~Sculptor(){
    // no destrutor, a memoria alocada deve ser liberada
    // o processo acontece "de tras pra frente"

    // liberacao do eixo z
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            delete[] v[i][j];
        }
    }

    // liberacao do eixo y
    for(int i = 0; i < nx; i++){
        delete[] v[i];
    }

    // liberacao do eixo x
    delete[] v;
}

// implementacao do metodo que define a cor atual do desenho
void Sculptor::setColor(float r, float g, float b, float alpha){
    // usando this pois os argumentos tem os mesmos nomes que os atributos privados da classe
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
}