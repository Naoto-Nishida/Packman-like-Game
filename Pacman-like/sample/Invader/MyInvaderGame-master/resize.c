#include"func.h"

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(-w / 2.0, w / 2.0, -h / 2.0, h / 2.0, -1.0, 1.0);
}
