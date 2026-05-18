# projeto-sculptor

projeto da segunda e terceira unidade de programação avançada

# descrição

implementação da classe Sculptor, um escultor de modelos 3D com voxels que exporta a figura em formato OFF. pode ser visualizado em 3dviewer.net (visualizador online), meshlab (mais pratico para windows)  e geomview (mais pratico para linux).

# como compilar (linux)
no terminal, deve-se acessar a pasta onde estão os arquivos sculptor.h; sculptor.cpp e sculptor-main.cpp; após isso, executar o seguinte comando:

g++ sculptor.cpp sculptor-main.cpp -o sculptor-main

# como visualizar e dicas de visualização (linux)

apos isso, o arquivo proveniente da compilação pode ser executado com ./sculptor-main

na pasta, vai surgir um arquivo .off que pode ser visualizado com o comando

geomview nome_do_arquivo.off

## dicas de visualização

inspect -> cameras -> background color -> HSV; troca de HSV para RGB e puxa todos os sliders para a direita (o fundo fica branco)
inspect -> material -> [aT] Translucent; se o desenho usar transparencia, ela aparece na visualização ao marcar essa caixa
inspect -> appearance -> [ae] Edges; as arestas ficam visíveis, facilitando visualizar cada Voxel
