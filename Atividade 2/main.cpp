#include "obj_loader/objLoader.h"
#include "main.h"
#include "pipeline.h"

objLoader* objData;
double angle = 0.0f;

void MyGlDraw(void){
    init();

    createCamera(
                 0.0f, 0.0f, 5.0f, // posicionamento da camera
                 0.0f, 0.0f, 0.0f, // ponto o qual a camera está olhando
                 0.0f, 1.0f, 0.0f, // vetor up
    );

    viewportGL(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT); // janela de projeção

    viewPlaneDGL(2.6); // distancia d do View Plane

    rotateGL(angle, 0.0f, 1.0f, 0.0f); //matriz de rotação

    angle += 0.01f; // velocidade de rotação

    memset(FBptr, 0, IMAGE_WIDTH * IMAGE_HEIGHT * 4);

    Pixel pixel[3];

    unsigned char red = 255;
    unsigned char green = 255;
    unsigned char blue = 255;
    unsigned char alpha = 0;

    for(int f = 0; f < objData->faceCount; f++){
        obj_face* obj = objData->faceList[f];

        for(int i = 0; i<3; i++){
            Point p = createPipeline(
                                     objData->vertexList[obj->vertex_index[i]]->e[0],
                                     objData->vertexList[obj->vertex_index[i]]->e[1],
                                     objData->vertexList[obj->vertex_index[i]]->e[2]
            );

            pixel[i] = createPixel(p.x, p.y, red, green, blue, alpha, pixel[i]);
        }

        deawTriangle(pixel[0]. pixel[1], pixel[2]);
    }
}

//----------------------------------------------------------------------------------------------
int main(int argc, char **argv){

    objData = new objLoader();

    objData->load((char*)argv[1]);

    //Inicialização
    InitOpenGL(&argc, argv);
    InitCallBacks();
    InitDataStrutures();


    DrawFunc = MyGlDraw;

    glutMainLoop;

    return 0;
}
