// arquivo de definicao da classe; aqui ocorre a implementacao dos metodos da classe

#include <iostream>
#include "sculptor.h"

using namespace std;

// implementacao do construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // alocacao do eixo x
    v = new Voxel**[nx];

    // alocacao do eixo y
    for(int i = 0; i < nx; i++)
    {
        v[i] = new Voxel*[ny];
    }

    // alocacao do eixo z
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            v[i][j] = new Voxel[nz];
        }
    }

    // inicializacao dos voxels
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                v[i][j][k].show = false;
            }
        }
    }

    cout << "[Construtor] objeto criado com dimensoes (" << nx << "," << ny << "," << nz << ")" << endl;
}

// implementacao do destrutor da classe
Sculptor::~Sculptor()
{
    // liberacao do eixo z
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            delete[] v[i][j];
        }
    }

    // liberacao do eixo y
    for(int i = 0; i < nx; i++)
    {
        delete[] v[i];
    }

    // liberacao do eixo x
    delete[] v;

    cout << "[Destrutor] memoria liberada com sucesso" << endl;
}

// define a cor atual do desenho
void Sculptor::setColor(float r, float g, float b, float alpha)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;

    cout << "[setColor] cor definida: ("
         << r << "," << g << "," << b << "," << alpha << ")" << endl;
}

// ativa um voxel
void Sculptor::putVoxel(int x, int y, int z)
{
    if(x < 0 || x >= nx || y < 0 || y >= ny || z < 0 || z >= nz)
    {
        cout << "[putVoxel] coordenada invalida: (" << x << "," << y << "," << z << ")" << endl;
        return;
    }

    v[x][y][z].show = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;

    cout << "[putVoxel] ativado voxel em ("
         << x << "," << y << "," << z << ")" << endl;
}

// desativa um voxel
void Sculptor::cutVoxel(int x, int y, int z)
{
    if(x < 0 || x >= nx || y < 0 || y >= ny || z < 0 || z >= nz)
    {
        cout << "[cutVoxel] coordenada invalida: (" << x << "," << y << "," << z << ")" << endl;
        return;
    }

    v[x][y][z].show = false;

    cout << "[cutVoxel] desativado voxel em (" << x << "," << y << "," << z << ")" << endl;
}