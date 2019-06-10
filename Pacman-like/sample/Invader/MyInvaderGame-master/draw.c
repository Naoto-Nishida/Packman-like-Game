#include"func.h"

void line(Position begin, Position end){
	glColor3d(0.0, 1.0, 1.0);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2d(begin.x, begin.y);
	glVertex2d(end.x, end.y);
	glEnd();
}

void draw_hodai(Position* ptr_struct){
	glColor3d(0.5, 1.0, 0.5);
	glBegin(GL_TRIANGLES);
	glVertex2d(ptr_struct->x, ptr_struct->y);
	glVertex2d(ptr_struct->x + 10, ptr_struct->y - 7.5); // 砲台(三角形)の大きさ決め
	glVertex2d(ptr_struct->x - 10, ptr_struct->y - 7.5); // マジックナンバー使ってるので要修正
	glEnd();
}

void draw_ray(Ray_Position* ptr_struct){
	if(ptr_struct->flag == TRUE){
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex2d(ptr_struct->begin_x, ptr_struct->begin_y);
		glVertex2d(ptr_struct->begin_x, ptr_struct->begin_y + 10); // 光線の長さ指定(10)
		glEnd();
	}//右クリックが押されたら描写
}

void draw_invader(void){
	for(int i = 0; i < INV_HEIGHT; i++){
		for(int j = 0; j < INV_WIDTH; j++){
			if(inv[i][j].status == TRUE && i % 2 == 0){
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, inv_tex_id_1);
				glColor3d(0.0, 1.0, 0.5);
				glBegin(GL_QUADS);
				glTexCoord2d(0.0, 0.0);
				glVertex2d(inv[i][j].x, inv[i][j].y);
				glTexCoord2d(0.0, 1.0);
				glVertex2d(inv[i][j].x, inv[i][j].y - 32);
				glTexCoord2d(1.0, 1.0);
				glVertex2d(inv[i][j].x + 32, inv[i][j].y - 32);
				glTexCoord2d(1.0, 0.0);
				glVertex2d(inv[i][j].x + 32, inv[i][j].y);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}else if(inv[i][j].status == TRUE && i % 2 == 1){
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, inv_tex_id_2);
				glColor3d(1.0, 0.5, 1.0);
				glBegin(GL_QUADS);
				glTexCoord2d(0.0, 0.0);
				glVertex2d(inv[i][j].x, inv[i][j].y);
				glTexCoord2d(0.0, 1.0);
				glVertex2d(inv[i][j].x, inv[i][j].y - 32);
				glTexCoord2d(1.0, 1.0);
				glVertex2d(inv[i][j].x + 32, inv[i][j].y - 32);
				glTexCoord2d(1.0, 0.0);
				glVertex2d(inv[i][j].x + 32, inv[i][j].y);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
		}
	}
}

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

void draw_num(int num, double x, double y){
	char str[256];
	sprintf(str, "%d", num);
	glColor3d(1.0, 0.5, 0.5);
	glRasterPos2d(x, y);
	for(int i = 0; str[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void draw_char(const char* str, double x, double y){
	glColor3d(1.0, 0.5, 0.5);
	glRasterPos2d(x, y);
	for(size_t i = 0; i < strlen(str); i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}
