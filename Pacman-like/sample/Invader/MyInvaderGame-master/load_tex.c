#include"func.h"

int load_tex(const char *file_name, unsigned int *id, unsigned int height, unsigned int width){

	glGenTextures(1, id);

	FILE* fp = fopen(file_name, "rb");
	unsigned char *texture = (unsigned char*)malloc(sizeof(unsigned char) * height * width * 4); //ピクセルxピクセルxRGBA

	if(fp == NULL){
		printf("error\n");
		return 1;
	}else{
		fread(texture, sizeof(unsigned char), height * width * 4, fp);
		fclose(fp);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	free(texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return 0;
}
