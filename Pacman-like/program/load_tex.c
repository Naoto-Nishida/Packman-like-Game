#include "glpng.h"
#include "struct.h"

int load_tex(const char *file_name, unsigned int *id, unsigned int height, unsigned int width){

	glGenTextures(1, id);

	/*

	FILE* fp = fopen(file_name, "rb");
	unsigned char *texture = (unsigned char*)malloc(sizeof(unsigned char) * height * width * 4); //ピクセルxピクセルxRGBA ここのサイズハードコーディングでいい・・？pngの中身わかんねえので幾らmallocしていいのかわかんねえよ！！

	if(fp == NULL){
		printf("error\n");
		return 1;
	}else{
		fread(texture, sizeof(unsigned char), height * width * 4, fp); //ここのサイズもハードコーディングするしかねえ！！
		fclose(fp);
	}

	*/


	GLuint texture;// = (unsigned char*)malloc(sizeof(unsigned char) * (height * width * 4 + 10000)); //メモリ容量気にして 適当に1000余分に取った
	pngInfo info;
	texture = pngBind (file_name, PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, height, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture);

	//free(texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return 0;
}
