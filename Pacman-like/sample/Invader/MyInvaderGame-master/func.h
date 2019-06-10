#ifndef FUNC_H
#define FUNC_H

#define _USE_MATH_DEFINES

#include"struct.h"
#include"define.h"
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<GL/glut.h>

extern Position mouse_position;
extern Position hodai_vertex;
extern Invader inv[INV_HEIGHT][INV_WIDTH];
extern Ray_Position ray_hodai;
extern Ray_Position ray_inv[INV_RAY];
extern const unsigned int sleep_milli_time;
extern const int window_size_width;
extern const int window_size_height;
extern unsigned int inv_tex_id_1;
extern unsigned int inv_tex_id_2;
extern unsigned int menu_tex_id;
extern unsigned int hodai_life;
extern unsigned int point;
extern unsigned int destroy;
extern unsigned int window_num;

//描画関数
void line(Position, Position);

//主要オブジェクト描画関数
void draw_hodai(Position*);
void draw_ray(Ray_Position *);
void draw_invader(void);

//文字描画関数
void draw_num(int, double, double);
void draw_char(const char *, double, double);

//メニュー描画
void draw_menu(void);

//初期化関数
void init_invader(void);
void init_ray(Ray_Position *);
int load_tex(const char*, unsigned int*, unsigned int, unsigned int);

//モーション系
void motion(int);

//システム
void resize(int, int);
void display(void);
void mouse(int, int);
void mouse_button(int, int, int, int);
uint32_t xorshift(void);

#endif //FUNC_H
