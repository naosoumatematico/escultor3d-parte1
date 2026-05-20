// arquivo de definicao da classe; aqui ocorre a implementacao dos metodos da classe

#include <fstream> // para criar e escrever no arquivo .off que sera gerado
#include <cstdlib> // para usar exit(1)
#include "sculptor.h" // header da classe sculptor

using namespace std;

// construtor da classe
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

// destrutor da classe
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
// this eh usado pois os parametros rgb do argumento tem o mesmo nome que os atributos da classe
// ou seja, r = r nao faria sentido;
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

    // se a coordenada for valida, ativa o voxel com a cor definida no setColor
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

    // se a coordenada for valida, desativa o voxel
    v[x][y][z].show = false;
}

// ativa os voxels no intervalo dado
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int x = x0; x <= x1; x++){
        for(int y = y0; y <= y1; y++){
            for(int z = z0; z <= z1; z++){
                putVoxel(x, y, z); // os lacos de repeticao percorrem o intervalo, e ativam o voxel onde for valido chamando o metodo putVoxel
            }
        }
    }
}

// desativa os voxels no intervalo dado
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int x = x0; x <= x1; x++){
        for(int y = y0; y <= y1; y++){
            for(int z = z0; z <= z1; z++){
                cutVoxel(x, y, z); // os lacos de repeticao percorrem o intervalo, e desativam o voxel onde for valido chamando o metodo cutVoxel
            }
        }
    }
}

// salva o desenho em um arquivo OFF
void Sculptor::writeOFF(const char* filename){
   ofstream fout; // objeto da classe ofstream para escrever no arquivo
   fout.open(filename); // metodo open tenta abrir o arquivo
   if(!fout.is_open()){
    exit(1);
   }

   // variavel acumuladora inteira para contar o total de voxels no desenho
   // deve ser inicializada com valor 0 para que o lixo nao interfira na contagem
   int nVoxels = 0;

   // lacos de repeticao aninhados que percorrem toda a matriz 3D contando o total de voxels
   for(int x = 0; x < nx; x++){
        for(int y = 0; y < ny; y++){
            for(int z = 0; z < nz; z++){
                if(v[x][y][z].show){
                    nVoxels++;
                }
            }
        }
    }

    // escreve o header do arquivo
    /* exemplo:
       OFF
       8 6 0
       cria um arquivo .off que comporta 8 vertices e 6 faces */
    fout << "OFF\n";
    fout << nVoxels*8 << " " << nVoxels*6 << " 0\n"; /* como vamos desenhar apenas cubos, multiplicamos nVoxels por 8 para saber o 
                                                        total de vertices e por 6 para saber o total de faces */
                                                        

    // escreve uma lista com todos os vertices presentes no desenho
    for(int x = 0; x < nx; x++){
        for(int y = 0; y < ny; y++){
            for(int z = 0; z < nz; z++){
                if(v[x][y][z].show){ // aqui estou considerando (x, y, z) como a coordenada no centro do voxel

                    /* considerando o voxel como sendo 1x1x1 e (x, y, z) como o centro, cada vertice eh deslocado em 0.5 em cada
                       dimensao com relacao ao seu centro 
                       eh util visualizar como uma tabela verdade
                       cada linha de fout imprime uma linha com as coordenadas de cada um dos vertices
                       a sequencia de fout se repete para cada v[x][y][z].show verdadeiro*/
                    
                                                                                 // indices de cada vertice
                    fout << x - 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n"; // v0
                    fout << x + 0.5 << " " << y - 0.5 << " " << z - 0.5 << "\n"; // v1
                    fout << x - 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n"; // v2
                    fout << x + 0.5 << " " << y + 0.5 << " " << z - 0.5 << "\n"; // v3
                    fout << x - 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n"; // v4
                    fout << x + 0.5 << " " << y - 0.5 << " " << z + 0.5 << "\n"; // v5
                    fout << x - 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n"; // v6
                    fout << x + 0.5 << " " << y + 0.5 << " " << z + 0.5 << "\n"; // v7
                }
            }
        }
    }

    /* escreve uma lista onde cada linha contem a conexao de vertices que forma uma face, pintando-a com a cor definida para cada voxel
       para idealizar essa lista, desenhei um cubo e atribui para cada vertice indices de 0 a 7 e fiz as conexoes que desenham
       corretamente as faces de um cubo no formato pedido pelo OFF */

    // variavel que armazena o indice de cada vertice
    int vertice = 0;

    for(int x = 0; x < nx; x++){
        for(int y = 0; y < ny; y++){
            for(int z = 0; z < nz; z++){
                if(v[x][y][z].show){ // lacos aninhados que percorrem toda a matriz procurando voxels ativos
                    
                    /* escrita no arquivo ocorre na forma:
                       nVertices v0 v1 v3 v2 r g b a
                       onde nVertices eh o numero de vertices a serem ligadas para desenhar uma face (no caso dos cubos, sao sempre 4)
                       v0 - v2 sao os indices dos vertices seguindo uma ordem que complete a face
                       r, g, b, a sao as cores e opacidade definidas no setColor
                        */
                    fout << 4 << " " << vertice + 0 << " " << vertice + 1 << " " << vertice + 3 << " " << vertice + 2 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].a << "\n";
                    fout << 4 << " " << vertice + 0 << " " << vertice + 1 << " " << vertice + 5 << " " << vertice + 4 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].b << "\n";
                    fout << 4 << " " << vertice + 0 << " " << vertice + 2 << " " << vertice + 6 << " " << vertice + 4 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].b << "\n";
                    fout << 4 << " " << vertice + 3 << " " << vertice + 1 << " " << vertice + 5 << " " << vertice + 7 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].b << "\n";
                    fout << 4 << " " << vertice + 3 << " " << vertice + 2 << " " << vertice + 6 << " " << vertice + 7 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].b << "\n";
                    fout << 4 << " " << vertice + 4 << " " << vertice + 5 << " " << vertice + 7 << " " << vertice + 6 << " " << v[x][y][z].r << " " << v[x][y][z].g << " " << v[x][y][z].b << " " << v[x][y][z].b << "\n";

                    // apos o fim da escrita de um Voxel, vertice eh somado 8 para continuar no proximo voxel
                    vertice += 8;
                }
            }
        }
    }

    // fecha o arquivo apos fazer todas as alteracoes
    fout.close();
    
}