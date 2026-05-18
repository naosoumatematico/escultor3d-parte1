// arquivo de definicao da classe; aqui ocorre a implementacao dos metodos da classe

#include <iostream>
#include <fstream>
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

// metodo completamente vibecodado; nao confio nem um pouco (queria so testar os outros metodos visualmente)
void Sculptor::writeOFF(const char* filename)
{
    ofstream fout;

    fout.open(filename);

    if(!fout.is_open())
    {
        cout << "[writeOFF] erro ao abrir arquivo" << endl;
        return;
    }

    int nvoxels = 0;

    // conta quantos voxels estao ativos
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                if(v[i][j][k].show == true)
                {
                    nvoxels++;
                }
            }
        }
    }

    int nvertices = nvoxels * 8;
    int nfaces = nvoxels * 6;

    // cabecalho OFF
    fout << "OFF\n";
    fout << nvertices << " " << nfaces << " 0\n";

    // escrita dos vertices
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                if(v[i][j][k].show)
                {
                    fout << i-0.5 << " " << j+0.5 << " " << k-0.5 << "\n";
                    fout << i-0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    fout << i+0.5 << " " << j-0.5 << " " << k-0.5 << "\n";
                    fout << i+0.5 << " " << j+0.5 << " " << k-0.5 << "\n";

                    fout << i-0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                    fout << i-0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    fout << i+0.5 << " " << j-0.5 << " " << k+0.5 << "\n";
                    fout << i+0.5 << " " << j+0.5 << " " << k+0.5 << "\n";
                }
            }
        }
    }

    int voxel = 0;

    // escrita das faces
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                if(v[i][j][k].show)
                {
                    int base = voxel * 8;

                    fout << "4 "
                         << base+0 << " "
                         << base+3 << " "
                         << base+2 << " "
                         << base+1
                         << " "
                         << v[i][j][k].r << " "
                         << v[i][j][k].g << " "
                         << v[i][j][k].b << " "
                         << v[i][j][k].a << "\n";

                    fout << "4 "
                         << base+4 << " "
                         << base+5 << " "
                         << base+6 << " "
                         << base+7
                         << " "
                         << v[i][j][k].r << " "
                         << v[i][j][k].g << " "
                         << v[i][j][k].b << " "
                         << v[i][j][k].a << "\n";

                    fout << "4 "
                         << base+0 << " "
                         << base+1 << " "
                         << base+5 << " "
                         << base+4
                         << " "
                         << v[i][j][k].r << " "
                         << v[i][j][k].g << " "
                         << v[i][j][k].b << " "
                         << v[i][j][k].a << "\n";

                    fout << "4 "
                         << base+0 << " "
                         << base+4 << " "
                         << base+7 << " "
                         << base+3
                         << " "
                         << v[i][j][k].r << " "
                         << v[i][j][k].g << " "
                         << v[i][j][k].b << " "
                         << v[i][j][k].a << "\n";

                    fout << "4 "
                         << base+3 << " "
                         << base+7 << " "
                         << base+6 << " "
                         << base+2
                         << " "
                         << v[i][j][k].r << " "
                         << v[i][j][k].g << " "
                         << v[i][j][k].b << " "
                         << v[i][j][k].a << "\n";

                    fout << "4 "
                         << base+1 << " "
                         << base+2 << " "
                         << base+6 << " "
                         << base+5
                         << " "
                         << v[i][j][k].r << " "
                         << v[i][j][k].g << " "
                         << v[i][j][k].b << " "
                         << v[i][j][k].a << "\n";

                    voxel++;
                }
            }
        }
    }

    fout.close();

    cout << "[writeOFF] arquivo OFF salvo com sucesso: "
         << filename << endl;
}