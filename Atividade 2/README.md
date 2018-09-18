#Trabalho II - Implementação do Pipeline gráfico

## Obejtivo

O trabalho consiste em implementar todas as etapas do pipeline gráfico aplicando todas as transformações do pipeline gráfico em um objeto tridimensional. Saíndo do espaço do objeto até o espaço de tela. Tudo isso fazendo uso das bibliotecas GLUT e OpenGL.

## Pipeline Gráfico

O Pipeline Gráfico é do o conjunto etapas necessárias envolvendo transformações matemáticas para criar a representação de um objeto 3D representado como 2D na tela. Abaixo, segue uma imagem do algoritmo do pipeline gráfico.

### Pipeline Gráfico
<p align="center">
	<br>
	<img src="./screenshots/pipeline.png"/>
	<h5 align="center">Figura 1 - Representação do Pipeline Gráfico</h5>
	<br>
</p>


### Espaço do Objeto -> Espaço do Universo

É o espaço onde cada objeto é criado e modelado a partir de suas primitivas geométricas e que possui seu próprio sistema de coordenadas. 

Quando um objeto é criado, este, está situado na origem de seu espaço, e que nem sempre condiz com a origem do Espaço do Universo, como mostra a figura 2. Para trazer o objeto para o Espaço do Universo é preciso realizar uma série de transformações geométricas.

<p align="center">
	<br>
	<img src="./screenshots/obj-world.png"/>
	<h5 align="center">Figura 2 - Representação do Objeto no Espaço do Objeto e no Espaço do Universo</h5>
	<br>
</p>

Para realizar a transformação é necessário realiar a multiplicação dos vértices do objeto pela matriz de modelagem. Esta matriz de modelagem(Matriz Model) pode ser composta rotação, translação, escala e cisalhamento. E caso nenhuma transformação seja necessária, é feita a multiplicação pela matriz identidade. Segue abaixo o código referente as transformações citadas.

#### Matriz de Rotação
```C++

void rotateGL(double angle, double x, double y, double z)
{
    Matrix rotate(4, 4);

    rotate.loadIdentity();

    if(x > 0.0) {
        rotate.setValue(1, 1, cos(angle));
        rotate.setValue(1, 2, -sin(angle));
        rotate.setValue(2, 1, sin(angle));
        rotate.setValue(2, 2, cos(angle));
    }

    if(y > 0.0) {
        rotate.setValue(0, 0, cos(angle));
        rotate.setValue(0, 2, sin(angle));
        rotate.setValue(2, 0, -sin(angle));
        rotate.setValue(2, 2, cos(angle));
    }

    if(z > 0.0) {
        rotate.setValue(0, 0, cos(angle));
        rotate.setValue(0, 1, -sin(angle));
        rotate.setValue(1, 0, sin(angle));
        rotate.setValue(1, 1, cos(angle));
    }

    matrix_model.mult(matrix_model, rotate);
}

```

#### Matriz de TRANSLAÇÂO
```C++

void translateGL(double dx, double dy, double dz)
{
    Matrix translate(4, 4);

    translate.loadIdentity();

    translate.setValue(0, 3, dx);
    translate.setValue(1, 3, dy);
    translate.setValue(2, 3, dz);

    matrix_model.mult(matrix_model, translate);
}

```

#### Matriz de ESCALA
```C++

void scaleGL(double x, double y, double z)
{
    Matrix scale(4, 4);

    scale.loadIdentity();

    scale.setValue(0, 0, x);
    scale.setValue(1, 1, y);
    scale.setValue(2, 2, z);

    matrix_model.mult(matrix_model, scale);
}

```

#### Matriz de CISALHAMENTO(Shear)
```C++

void shearGL(double x, double y, double z)
{
    Matrix shear(4, 4);
    shear.loadIdentity();

    shear.setValue(0, 1, x);
    shear.setValue(0, 2, x);

    shear.setValue(1, 0, y);
    shear.setValue(1, 2, y);

    shear.setValue(2, 0, z);
    shear.setValue(2, 1, z);

    matrix_model.mult(matrix_model, shear);
}

```

Para realização de mais de uma transformação, basta realizar o produto das matrizes de transformações. Seguindo sempre de invertar a ordem das operações em relação as transformações desejadas para que o produto resulte no objetivo esperado.


### Espaço do Universo -> Espaço da Câmera

Em seguida devemos sair do Espaço do Universo para o Espaço da Câmera, que será a forma de como o nosso objeto será visto pela câmera. Sendo necessário assim definir a posição da câmera, a orientação(para onde está olhando) e qual lado é o de cima, para que tenhamos controle total da orientação da câmera. O resultado destra transformação é a Matriz View que é composta por uma translação e uma rotação.

Segue abaixo a imagem que ilustra a situação descrita.

<p align="center">
	<br>
	<img src="./screenshots/obj-world2.png"/>
	<h5 align="center">Figura 3 - Representação Espaço do Universo vs Espaço da Cãmera</h5>
	<br>
</p>

### Matriz View

```C++

void createCamera(double pos_x, double pos_y, double pos_z,
    double lookat_x, double lookat_y, double lookat_z,
    double up_x, double up_y, double up_z)
{
    Vector x_cam(3, 1);
    Vector y_cam(3, 1);
    Vector z_cam(3, 1);

    Matrix Bt(4, 4);
    Matrix T(4, 4);

    Vector aux(3, 1);
    Vector up(3, 1);

    double vec_pl[] = {pos_x - lookat_x, pos_y - lookat_y, pos_z - lookat_z};
    double vec_up[]  = {up_x, up_y, up_z};

    aux.setValues(vec_pl);
    up.setValues(vec_up);

    z_cam.div(aux, norm(&aux));

    cross(&up, &z_cam, &aux);

    x_cam.div(aux, norm(&aux));

    cross(&z_cam, &x_cam, &aux);
    y_cam.div(aux, norm(&aux));

    double bt_mtx[] = {
        x_cam.getValue(0, 0), x_cam.getValue(1, 0), x_cam.getValue(2, 0), 0,
        y_cam.getValue(0, 0), y_cam.getValue(1, 0), y_cam.getValue(2, 0), 0,
        z_cam.getValue(0, 0), z_cam.getValue(1, 0), z_cam.getValue(2, 0), 0,
                0,                    0,                    0,            1
    };

    Bt.setValues(bt_mtx);

    T.loadIdentity();
    T.setValue(0, 3, -pos_x);
    T.setValue(1, 3, -pos_y);
    T.setValue(2, 3, -pos_z);

    matrix_view.loadIdentity();

    matrix_view.mult(Bt, T);
}

```


### Espaço da Câmera -> Espaço de Recorte/Projetivo

Nesta estapa é feita a transformação para sair do Espaço da Câmera para o Espaço de Recorte, gerando uma nova matriz, a Matriz de Projeção(Matrix Projection). Essa matriz, contém as características de distorção de perspectiva, fazendo com que objetos mais próximos da câmera fiquem maiores e os que estão mais distantes se apresentem em tamanho menor.

A figura 4 ilustra o que ocorre nessa transformação. O "c" é a posição da câmera, "d" é definido como a distância focal da câmera, p um ponto no espaço da câmera e p' sua projeção. 


<p align="center">
	<br>
	<img src="./screenshots/Projection.png"/>
	<h5 align="center">Figura 4 - Projeção de Perspectiva</h5>
	<br>
</p>

### Matriz de Projeção

```C++

void viewPlaneDGL(double dist)
{
    double d = dist;

    matrix_projection.setValue(2, 3, d);
    matrix_projection.setValue(3, 2, (-1) / d);
    matrix_projection.setValue(3, 3, 0);
}

```

### Espaço de Recorte -> Espaço Canônico

Esta estapa é responsável por eliminar os vértices que não estão na visão da câmera do pipeline gráfico. Para realizar esta função primeiro precisamos primeiro transformar as coordenadas Euclidianas em coordenadas homogêneas.

As coordenadas homogêneas são uma forma de representar coordenadas de N-dimensões com números N+1.
O sistema de coordenadas Euclidianas representam espaços 2D e 3D de forma "ótima" e isso, de certa forma, gera um problema quando se trata de projeção de perspectiva. Um exemplo disso são retas paralelas indo ao infinito, sua representação de perspectiva no espaço deveria ilustrar as retas se encontrando mas isso não ocorre com coordenadas euclidianas, para isso fazemos uso de coordenadas homogêneas. 

Para realizar o processo de homogeneização adicionamos uma variável, w, no sistema de coordenadas, saindo de um sistema (x,y,z) para (x,y,z,w). Onde X, Y e Z são expressados de forma homogênea como: 

- X = x/w
- Y = y/w
- Z = z/w

Para realizar o processo de homogeinização dividimos as coordenadas dos vértice(pontos) provindos do espaço de recorte pela sua coordenada homogenea(w).

### Espaço Canônico -> Espaço de Tela

Saindo do espaço canônico e indo paara o Espaço de Tela, os vértices serão mapeados para o espaço de tela fazendo uso de outra transformação, chamada de Matriz Viewport.
Para isso precisamos realizar transformações de escalas e translações, uma vez que o sistema de coordenadas da tela começam pelo canto superior esquerdo e crescem no sentido para baixo e direita.

### Matriz ViewPort

```C++

void viewportGL(int x, int y, size_t width, size_t height)
{
    Matrix S1(4, 4);
    Matrix S2(4, 4);
    Matrix T(4, 4);

    S1.loadIdentity();
    S2.loadIdentity();
    T.loadIdentity();

    S1.setValue(1, 1, -1);

    S2.setValue(0, 0, (width - 1) / 2.0f);
    S2.setValue(1, 1, (height - 1) / 2.0f);

    T.setValue(0, 3, 1);
    T.setValue(1, 3, 1);

    matrix_viewport.loadIdentity();

    matrix_viewport.mult(T, S1);
    matrix_viewport.mult(S2, matrix_viewport);
}

```

### Rasteirização

Para finalizar o pipeline temos a rasteirização. Para realizar a rasteirização basta chamar as funções criadas no trabalho anterior.

### Rasteirizando

```C++

Point createPipeline(double x, double y, double z)
{
    double vert[] = {x, y, z, 1};
    Matrix vertice(4, 1);
    vertice.setValues(vert);

    vertice.mult(matrix_model, vertice);
    vertice.mult(matrix_view, vertice);
    vertice.mult(matrix_projection, vertice);
    vertice.div(vertice, vertice.getValue(3, 0));
    vertice.mult(matrix_viewport, vertice);

    Point p = {.x = (int)vertice.getValue(0, 0), .y = (int)vertice.getValue(1, 0)};

    return p;
}

```