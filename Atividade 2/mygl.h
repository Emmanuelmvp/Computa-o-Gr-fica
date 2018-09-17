#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

enum colors
{
	RED   = 0,
    GREEN = 1,
    BLUE  = 2,
    ALPHA = 3
};

struct Pixel{

	 int x;
	 int y;
	unsigned char color[4];
};

//Criando o pixel
Pixel criaPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, Pixel pixel){

	pixel.x = x;
	pixel.y = y;

	pixel.color[RED] = red;
	pixel.color[GREEN] = green;
	pixel.color[BLUE] = blue;
	pixel.color[ALPHA] = alpha;

	return pixel;
}
//Função que rasteria um ponto na memória de video recebendo as informacoes do pixel
void putPixel(Pixel p){
	int offset = 4*p.x+4*p.y*IMAGE_WIDTH;  
	FBptr[offset+RED] = p.color[RED];
	FBptr[offset+GREEN] = p.color[GREEN];
	FBptr[offset+BLUE]  = p.color[BLUE];
	FBptr[offset+ALPHA] = p.color[ALPHA];	
}

void drawLine(Pixel pixelInicial, Pixel pixelFinal){

	int d, dx, dy, incE, incNE, x, y, declive;

	dx = pixelFinal.x - pixelInicial.x;
	dy = pixelFinal.y - pixelInicial.y;

	if(dx<0){
		std::swap(pixelInicial, pixelFinal);
		dx = -dx;
		dy = -dy;
	}

	if(dy<0){
		declive=-1;
	}
	else{
		declive=1;
	}

	Pixel tempPixel = pixelInicial;
	putPixel(pixelInicial);

	if(declive*dy <= dx){
		if(dy<0){
			d=2*dy+dx;
			while(tempPixel.x<pixelFinal.x){
				if(d<0){
					d+=2*(dy+dx);
					tempPixel.x++;
					tempPixel.y--;
				}
				else{
					d+=2*dy;
					tempPixel.x;
				}
				for(int i = RED; i<=ALPHA; i++){
					tempPixel.color[i] = (unsigned char)(pixelInicial.color[i] + (tempPixel.x - pixelInicial.x)*(pixelFinal.color[i] - pixelInicial.color[i])/dx);
				}
				putPixel(tempPixel);
			}
		
		} else {
            d = 2*dy - dx;            
            while(tempPixel.x < pixelFinal.x) { 
                if(d < 0) {                 
                    d+= 2*dy;
                    tempPixel.x++;
                } else {                    
                    d += 2*(dy - dx);
                    tempPixel.x++;
                    tempPixel.y++;;
                }
                for(int i = RED; i <= ALPHA; i++) {
                    tempPixel.color[i] = (unsigned char)(pixelInicial.color[i] + (tempPixel.x - pixelInicial.x)*(pixelFinal.color[i] - pixelInicial.color[i])/dx);
                }
                putPixel(tempPixel);
            }
        }
	}else{
        if(dy < 0) {
            d = dy + 2*dx;
            while( tempPixel.y > pixelFinal.y ) {     
                if(d < 0) {                
                    d += 2*dx;
                    tempPixel.y--;
                } else {
                    d += 2*(dy + dx);
                    tempPixel.x++;
                    tempPixel.y--;
                }
                for(int i = RED; i <= ALPHA; i++) {   
                    tempPixel.color[i] = (unsigned char)(pixelInicial.color[i] + (tempPixel.y - pixelInicial.y)*(pixelFinal.color[i] - pixelInicial.color[i])/dy);
                }
                putPixel(tempPixel);
            }
        } else {
            d = dy -2*dx;
            while( tempPixel.y < pixelFinal.y ) {
                if(d < 0) { 
                    d += 2*(dy - dx);
                    tempPixel.x++;
                    tempPixel.y++;
                } else {
                    d += -2*dx;
                    tempPixel.y++;
                }
                for(int i = RED; i <= ALPHA; i++) {    // for each component, interpolate
                    tempPixel.color[i] = (unsigned char)(pixelInicial.color[i] + (tempPixel.y - pixelInicial.y)*(pixelFinal.color[i] - pixelInicial.color[i])/dy);
                }
                putPixel(tempPixel);
            }
        }
    }
    putPixel(pixelFinal);
}

void drawTriangle(Pixel p1, Pixel p2, Pixel p3){
	drawLine(p1,p2);
	drawLine(p2,p3);
	drawLine(p3,p1);
}


#endif // _MYGL_H_

