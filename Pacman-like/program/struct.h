#ifndef STRUCT_H
#define STRUCT_H

#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<GL/glut.h>
#include <time.h>
#include <unistd.h>
#include "glpng.h"
#include "GenericTimer.h"




typedef struct Kanamori{ //HPグローバル変数で実装したから分ける必要なかった。。。
  int x;
  int y;
  //int HP;
}Kanamori;

typedef struct Enemy{
  int x;
  int y;
} Enemy;


//定数
extern const int window_position_x ;
extern const int window_position_y ;
extern const int window_size_width ;
extern const int window_size_height ;
extern const char* const window_name ;
extern const unsigned int sleep_milli_time ;

//グローバル変数らへんコピペしてない
extern unsigned int kanamori_tex_id; //金森先生
extern unsigned int enemy_tex_id_0;  //イバやん
extern unsigned int enemy_tex_id_1;  //ヤクザ
extern unsigned int enemy_tex_id_2;  //インテリヤクザ
extern unsigned int nabe_tex_id;	//牛膳鍋
extern unsigned int map_tex_id0; //map 0通路
extern unsigned int map_tex_id1; //map 1壁
extern unsigned int map_tex_id2; //map 2コインクーポン
extern unsigned int menu_tex_id;
extern unsigned int emono_tex_id; //獲物の金森先生

extern double prevTime, rapTime;

extern Kanamori kanamori;
extern Kanamori Emono;
extern Kanamori Nabe;
extern Enemy enemy[3];

extern int map[15][20] ;


//ゲーム内容関連
extern unsigned int HP ; //ライフ
extern unsigned int point ; //点数
extern unsigned int gyunabecounter ; //牛前鍋吸収数
extern int coinNum ; //クーポン何枚とった？
extern unsigned int window_num ; //0:メニュー 1:ゲーム 2:リザルト //関数内でグローバル変数を書き換えても大丈夫か？？->OKnなはず


void display();
void keyboard(unsigned char key, int x, int y);
void idle();
void special(int key, int x, int y);
void reshape(int x, int y);


void draw_num(int, double, double);
void draw_char(const char *, double, double);
void draw_map();
void draw_menu();
void draw_kanamori();
void draw_emono();
void draw_enemy();
void draw_nabe();


int load_tex(const char*, unsigned int*, unsigned int, unsigned int);


void EmonoMove();
void EnemyMove();
void Judgement();
int IsCoin();
int IsGyuzen();
int IsEmono();

void Init_Nabe();
void Init_Emono();
void Init_Enemy();
void Init_Kanamori();
#endif
