#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<GL/glut.h>
#include <unistd.h>
#include <time.h>
#include "glpng.h"
#include "struct.h"

#include "GenericTimer.h"


void draw_menu(void){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, menu_tex_id);
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex2d(-320.0, 320.0);
  glTexCoord2d(0.0, 1.0);
  glVertex2d(-320.0, -320.0);
  glTexCoord2d(1.0, 1.0);
  glVertex2d(320.0, -320.0);
  glTexCoord2d(1.0, 0.0);
  glVertex2d(320.0, 320.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void draw_map(){
  for(int i=0; i< 15; i++){
    for(int j=0; j<20; j++){
      switch(map[i][j]){ //テクスチャアトラスを使用したい人生だった...多分できるけど疲れた
        case 0:
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, map_tex_id0);
        glColor3d(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2d(j*64, i*64); //相対位置がおかしいかも？(-1~1指定の可能性がある)
        glTexCoord2d(0.0, 1.0);
        glVertex2d(j*64, (i-1)*64);
        glTexCoord2d(1.0, 1.0);
        glVertex2d((j+1)*64, (i-1)*64);
        glTexCoord2d(1.0, 0.0);
        glVertex2d((j+1)*64, i*64);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        break;
        case 1:
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, map_tex_id1);
        glColor3d(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2d(j*64, i*64); //相対位置がおかしいかも？(-1~1指定の可能性がある)
        glTexCoord2d(0.0, 1.0);
        glVertex2d(j*64, (i-1)*64);
        glTexCoord2d(1.0, 1.0);
        glVertex2d((j+1)*64, (i-1)*64);
        glTexCoord2d(1.0, 0.0);
        glVertex2d((j+1)*64, i*64);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        break;
        case 2:
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, map_tex_id2);
        glColor3d(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2d(j*64, i*64); //相対位置がおかしいかも？(-1~1指定の可能性がある)
        glTexCoord2d(0.0, 1.0);
        glVertex2d(j*64, (i-1)*64);
        glTexCoord2d(1.0, 1.0);
        glVertex2d((j+1)*64, (i-1)*64);
        glTexCoord2d(1.0, 0.0);
        glVertex2d((j+1)*64, i*64);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        break;
        default:
        break;
      }
    }
  }
}

void draw_kanamori(){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, kanamori_tex_id);
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex2d((kanamori.x)*64, (kanamori.y)*64); //相対位置がおかしいかも？(-1~1指定の可能性がある)
  glTexCoord2d(0.0, 1.0);
  glVertex2d((kanamori.x)*64, (kanamori.y - 1)*64);
  glTexCoord2d(1.0, 1.0);
  glVertex2d((kanamori.x+1)*64, (kanamori.y-1)*64);
  glTexCoord2d(1.0, 0.0);
  glVertex2d((kanamori.x+1)*64, (kanamori.y)*64);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void draw_emono(){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, emono_tex_id);
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex2d((Emono.x)*64, (Emono.y)*64); //相対位置がおかしいかも？(-1~1指定の可能性がある)
  glTexCoord2d(0.0, 1.0);
  glVertex2d((Emono.x)*64, (Emono.y - 1)*64);
  glTexCoord2d(1.0, 1.0);
  glVertex2d((Emono.x+1)*64, (Emono.y-1)*64);
  glTexCoord2d(1.0, 0.0);
  glVertex2d((Emono.x+1)*64, (Emono.y)*64);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void draw_enemy(unsigned char *id, Enemy enemy){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, *id);
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex2d((enemy.x)*64, (enemy.y)*64); //相対位置がおかしいかも？(-1~1指定の可能性がある)
  glTexCoord2d(0.0, 1.0);
  glVertex2d((enemy.x)*64, (enemy.y - 1)*64);
  glTexCoord2d(1.0, 1.0);
  glVertex2d((enemy.x + 1)*64, (enemy.y - 1)*64);
  glTexCoord2d(1.0, 0.0);
  glVertex2d((enemy.x+1)*64, (enemy.y)*64);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void  draw_nabe(){
  do  {
  	Nabe.x = (rand() % 20);
    Nabe.y = (rand() % 15);
  } while (map[Nabe.y][Nabe.x] == 1); //鍋にランダムな位置情報を与える


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, nabe_tex_id);
  glColor3d(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex2d((Nabe.x)*64, (Nabe.y)*64); //相対位置がおかしいかも？(-1~1指定の可能性がある)
  glTexCoord2d(0.0, 1.0);
  glVertex2d((Nabe.x)*64, (Nabe.y - 1)*64);
  glTexCoord2d(1.0, 1.0);
  glVertex2d((Nabe.x + 1)*64, (Nabe.y - 1)*64);
  glTexCoord2d(1.0, 0.0);
  glVertex2d((Nabe.x+1)*64, (Nabe.y)*64);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void draw_num(int num, double x, double y){
	char str[256];
	sprintf(str, "%d", num);
	glColor3d(1.0, 0.5, 0.5);
	glRasterPos2d(x, y);
	for(int i = 0; str[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}

void draw_char(const char* str, double x, double y){
	glColor3d(1.0, 0.5, 0.5);
	glRasterPos2d(x, y);
	for(size_t i = 0; i < strlen(str); i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}
