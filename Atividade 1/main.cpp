#include "main.h"

void bresenhamDemo(){
    Pixel pixel1  = criaPixel((IMAGE_WIDTH-1)/2, 0, 255, 0, 0, 255, pixel1);
    Pixel pixel2  = criaPixel((IMAGE_WIDTH-1)/2, IMAGE_HEIGHT-1, 255, 255, 0, 255, pixel2);

    Pixel pixel3  = criaPixel(0, (IMAGE_HEIGHT-1)/2, 0, 255, 0, 255, pixel3);
    Pixel pixel4  = criaPixel(IMAGE_WIDTH-1, (IMAGE_HEIGHT-1)/2, 0, 255, 255, 255, pixel4);

    Pixel pixel5  = criaPixel(0, 0, 0, 255, 255, 255, pixel5);
    Pixel pixel6  = criaPixel(IMAGE_WIDTH-1, IMAGE_HEIGHT-1, 0, 0, 255, 255, pixel6);

    Pixel pixel7  = criaPixel(0, IMAGE_HEIGHT-1, 0, 0, 255, 255, pixel7);
    Pixel pixel8  = criaPixel(IMAGE_WIDTH-1, 0, 255, 0, 255, 255, pixel8);

    drawLine(pixel1, pixel2);
    drawLine(pixel3, pixel4);
    drawLine(pixel5, pixel6);
    drawLine(pixel7, pixel8);
}

void triangleDemo(){
    Pixel pixel1  = criaPixel((IMAGE_WIDTH-1)/2, 1, 255, 0, 0, 255, pixel1);
    Pixel pixel2  = criaPixel((IMAGE_WIDTH-1),(IMAGE_HEIGHT-1), 255, 255, 0, 255, pixel2);
    Pixel pixel3  = criaPixel(1, IMAGE_HEIGHT-1, 0, 255, 0, 255, pixel3);

    drawTriangle(pixel1, pixel2, pixel3);
}






//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	// Testando o putpixel, coloquei os pares pra ficarem um pouco separados
	//	Pixel tempPixel;
	//	int j=0;
	//	for(int i =0; i<255;i++){			
	//		tempPixel = criaPixel(30+i,30, 255,0,0,255,tempPixel);
	//		if(i%2){	
	//		putPixel(tempPixel);
	//		}
	//	}
	//	for(int i =0; i<255;i++){
	//		tempPixel = criaPixel(30+i,40, 0,255,0,255,tempPixel);
	//		if(i%2){
	//		putPixel(tempPixel);
	//		}
	//	}
	//	for(int i =0; i<255;i++){
	//		tempPixel = criaPixel(30+i,50, 0,0,255,255,tempPixel);
	//		if(i%2){			
	//		putPixel(tempPixel);
	//		}
	//	}
	//	*/
	//bresenhamDemo();
	triangleDemo();


}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

