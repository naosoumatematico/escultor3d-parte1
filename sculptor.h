// arquivo de declaracao da classe

// protecao contra dupla inclusao acidental
#ifndef _SCULPTOR_H
#define _SCULPTOR_H

// declaracao da struct Voxel que sera manipulada pela classe Sculptor
struct Voxel {
  float r,g,b; // cor do voxel (em sistema aditivo, pois trata de luz); todas sao ponto flutuante e variam entre 0 e 1 
  float a; // transparencia do voxel. tambem varia entre 0 e 1
  bool show; // booleano que define se o voxel sera mostrado ou nao
};

// declaracao da classe Sculptor
class Sculptor {
private:
  Voxel ***v; // matriz 3d de Voxels (alocada dinamicamente)
  int nx,ny,nz; // dimensoes da matriz 3d
  float r,g,b,a; // cor atual a ser usada no desenho
public:
  Sculptor(int _nx, int _ny, int _nz); // construtor da classe
  ~Sculptor(); // destrutor da classe
  void setColor(float r, float g, float b, float alpha); // define a cor atual do desenho
  void putVoxel(int x, int y, int z); // ativa o voxel na posicao (x,y,z) (fazendo show = true) e atribui a ele a cor atual do desenho
  void cutVoxel(int x, int y, int z); // desativa o voxel na posicao (x,y,z) (fazendo show = false)
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1); // ativa todos os voxels no intervalo dado e atribui a eles a cor atual do desenho
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1); // desativa todos os voxels no intervalo dado
  void putSphere(int xcenter, int ycenter, int zcenter, int radius); // ativa todos os voxels que satisfazem a equacao da esfera e atribui a eles a cor atual do desenho
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius); // desativa todos os voxels que satisfazem a equacao da esfera
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz); // ativa todos os voxels que satisfazem a equacao do elipsoide e atribui a eles a cor atual do desenho
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz); // desativa todos os voxels que satisfazem a equacao do elipsoide
  void writeOFF(const char* filename); // grava o modelo 3D no formato OFF no arquivo filename
};

#endif