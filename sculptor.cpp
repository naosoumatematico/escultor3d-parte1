// arquivo de definicao da classe; aqui ocorre a implementacao dos metodos da classe

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "sculptor.h"

using namespace std;

// implementacao do construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    // definicao das dimensoes da matriz 3D
	nx = _nx;
	ny = _ny;
	nz = _nz;

    // alocacao dinamica da matriz
	v = new Voxel**[nx];
	for(int i = 0; i < nx; i++){
		v[i] = new Voxel*[ny];
		for(int j = 0; j < ny; j++){
			v[i][j] = new Voxel[nz];
			for(int k = 0; k < nz; k++){
				v[i][j][k].show = false; // inicialmente os Voxels sao desativados
			}
		}
	}
}

// implementacao do destrutor da classe
Sculptor::~Sculptor(){
    // como a classe trabalha com alocacao dinamica de memoria, o construtor deve se encarregar de liberar a memoria alocada
    // a liberacao deve ser feita "na ordem contraria" da alocacao, a fim de evitar memory leak
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}

// define a cor atual do desenho
void Sculptor::setColor(float r, float g, float b, float alpha){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
}

// ativa um voxel nas coordenadas dadas
void Sculptor::putVoxel(int x, int y, int z){
    // verifica se a coordenada esta dentro dos limites da matriz 3D
    if(x < 0 || x >= nx || y < 0 || y >= ny || z < 0 || z >= nz){
        return; // se tentar acessar uma regiao fora da matriz, o metodo nao faz nada
    }

    // ativa o voxel com a cor definida no setColor
    v[x][y][z].show = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

// desativa um voxel nas coordenadas dadas
void Sculptor::cutVoxel(int x, int y, int z){
    // verifica se a coordenada esta dentro dos limites da matriz 3D
    if(x < 0 || x >= nx || y < 0 || y >= ny || z < 0 || z >= nz){
        return; // se tentar acessar uma regiao fora da matriz, o metodo nao faz nada
    }

    // desativa o voxel
    v[x][y][z].show = false;
}

// ativa os voxels no intervalo dado
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int x = x0; x <= x1; x++){
        for(int y = y0; y <= y1; y++){
            for(int z = z0; z <= z1; z++){
                putVoxel(x, y, z); // os lacos de repeticao percorrem o intervalo, e ativam o voxel onde for valido
            }
        }
    }
}

// desativa os voxels no intervalo dado
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int x = x0; x <= x1; x++){
        for(int y = y0; y <= y1; y++){
            for(int z = z0; z <= z1; z++){
                cutVoxel(x, y, z); // os lacos de repeticao percorrem o intervalo, e desativam o voxel onde for valido
            }
        }
    }
}

// salva o desenho em um arquivo OFF
void Sculptor::writeOFF(const char* filename)
{
   ofstream fout;
   fout.open(filename);
   if(!fout.is_open()){
    exit(1);
   }

   int nVoxels = 0;

   for(int x = 0; x < nx; x++){
        for(int y = 0; y < ny; y++){
            for(int z = 0; z < nz; z++){
                if(v[x][y][z].show == true){
                    nVoxels++;
                }
            }
        }
    }

    int nFaces = nVoxels*6;
    int nVertices = nVoxels*8;

    fout << "OFF\n";
    fout.close();
    
}