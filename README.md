# Escultor 3D - Parte 1

Projeto da segunda unidade da disciplina de Programação Avançada.

---

## Descrição
Este projeto consiste na implementação da classe Sculptor, um escultor de modelos 3D com Voxels que exporta a figura em formato OFF. As figuras geradas podem ser visualizadas online no site 3dviewer.net, no software meshlab (mais prático para Windows) e no software geomview (mais prático para Linux).

Informações detalhadas sobre o projeto estão disponíveis em https://agostinhobritojr.github.io/curso/progav-dca0803/escultor.html

## Estrutura do Repositório
- `sculptor.h`: Declaração da classe `Sculptor`.
- `sculptor.cpp`: Implementação da classe; responsável pela lógica por trás de cada formato geométrico e do algoritmo de gravação do arquivo OFF.
- `sculptor-main.cpp`: Código de testes utilizado para criar um modelo tridimensional.

---

## Como desenhar as estruturas?

A classe `Sculptor` funciona como uma matriz de coordenadas tridimensionais $(x, y, z)$ onde cada posição (Voxel) possui propriedades de estado (ativo/inativo) e cor (RGB + Transparência). Abaixo está um breve tutorial de como utilizar cada método disponível.

### 1. Criação da matriz

* `Sculptor(int _nx, int _ny, int _nz)`
    É o construtor da classe. Aloca dinamicamente o espaço tridimensional da escultura com as dimensões especificadas.
    * **Exemplo:** `Sculptor exemplo(50, 50, 50);` (Cria uma grade de $50 \times 50 \times 50$).

* `void setColor(float r, float g, float b, float alpha)`
    Define a cor atual de desenho. Todas as funções `put...` chamadas após este comando usarão essa cor. Os valores de RGBA devem variar estritamente entre `0.0` (ausência) e `1.0` (intensidade máxima).
    * **Exemplo:** `exemplo.setColor(1.0, 0.0, 0.0, 1.0);` (define a cor para vermelho sólido)
    * **Exemplo:** `exemplo.setColor(0.0, 0.0, 1.0, 0.5);` (define a cor para azul transparente)

---

### 2. Funções para desenhar e apagar estruturas

* `void putVoxel(int x, int y, int z)`
    Ativa o voxel na coordenada espacial $(x, y, z)$ aplicando a cor atual definida em `setColor`.
    * **Exemplo:** `exemplo.putVoxel(0, 0, 0);` (ativa um voxel em $(0, 0, 0)$ com a cor definida no último `setColor`)

* `void cutVoxel(int x, int y, int z)`
    Apaga o voxel na coordenada $(x, y, z)$.
    * **Exemplo:** `exemplo.cutVoxel(0, 0, 0);` (desativa um voxel em $(0, 0, 0)$)

* `void putBox(int x0, int x1, int y0, int y1, int z0, int z1)`
    Ativa todos os voxels no intervalo $x \in [x0, x1]$, $y \in [y0, y1]$, $z \in [z0, z1]$ e atribui aos mesmos a cor atual de desenho.
    * **Exemplo:** `exemplo.putBox(0, 5, 0, 5, 0, 5);` (cria um cubo preenchido de dimensões $6 \times 6 \times 6$ voxels)

* `void cutBox(int x0, int x1, int y0, int y1, int z0, int z1)`
    Apaga todos os voxels dentro do intervalo $x \in [x0, x1]$, $y \in [y0, y1]$, $z \in [z0, z1]$.
    * **Exemplo:** `exemplo.cutBox(1, 4, 1, 4, 1, 4);` (remove uma região cúbica interna, deixando o bloco anterior oco)

* `void putSphere(int xcenter, int ycenter, int zcenter, int radius)`
    Ativa uma esfera sólida de voxels com centro em $(xcenter, ycenter, zcenter)$ e raio igual a `radius`.
    * **Exemplo:** `exemplo.putSphere(10, 10, 10, 5);` (cria uma esfera de raio 5 centrada na coordenada $(10, 10, 10)$)

* `void cutSphere(int xcenter, int ycenter, int zcenter, int radius)`
    Apaga todos os voxels que estejam dentro do raio da esfera especificada.
    * **Exemplo:** `exemplo.cutSphere(10, 10, 10, 3);` (corta/esvazia o interior da esfera gerada anteriormente usando um raio menor)

* `void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)`
    Ativa uma elipsoide sólida tridimensional centralizada no ponto dado, onde `rx`, `ry` e `rz` são os raios nos eixos $x$, $y$ e $z$, respectivamente.
    * **Exemplo:** `exemplo.putEllipsoid(20, 20, 20, 5, 3, 2);` (cria uma forma elíptica alongada no eixo X e achatada no eixo Z)

* `void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)`
    Remove todos os voxels que pertencem ao volume da elipsoide especificada.
    * **Exemplo:** `exemplo.cutEllipsoid(20, 20, 20, 5, 3, 2);` (apaga completamente a elipsoide anterior)

---

### 3. Exportação do Modelo

* `void writeOFF(const char* filename)`
    Varre toda a matriz tridimensional na memória, calcula quais vértices e faces são necessários para representar os voxels ativos e grava a geometria resultante em um arquivo de texto no formato `.off`.
    * **Exemplo:** `exemplo.writeOFF("modelo.off");`
    
O arquivo `sculptor-main.cpp` já possui uma estrutura desenhada. Ela mostra também como estruturas de repetição podem ser usadas para simplificar o desenho. Este mesmo arquivo pode ser posteriormente modificado, a fim de desenhar outras estruturas.

## Como Compilar e Executar (Linux)

Como o projeto possui apenas 3 arquivos, ele pode ser compilado facilmente no terminal executando o seguinte comando no terminal:

`g++ sculptor.cpp sculptor-main.cpp -o sculptor-main`

## Como Visualizar + Dicas de Visualização (Linux)

Após isso, o arquivo proveniente da compilação pode ser executado com `./sculptor-main`

Na pasta, surgirá um arquivo .off que pode ser visualizado executando o seguinte comando no terminal:

`geomview nome_do_arquivo.off`

### Dicas de Visualização

inspect -> cameras -> [v~] Software Shading; deixa as cores mais bonitas

inspect -> cameras -> background color -> HSV; troca de HSV para RGB e puxa todos os sliders para a direita (o fundo fica branco)

inspect -> material -> [aT] Translucent; se o desenho usar transparência, ela aparece na visualização ao marcar essa caixa

inspect -> appearance -> [ae] Edges; as arestas ficam visíveis, facilitando visualizar cada Voxel

inspect -> appearance -> [ab] BBoxes; tira o contorno que mostra toda a região alocada e usada no desenho
