#define _USE_MATH_DEFINES

#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<GL/glut.h>

#include"struct.h"
#include"func.h"
#include"define.h"

//定数
const int window_position_x = 0;
const int window_position_y = 0;
const int window_size_width = 640;
const int window_size_height = 640;
const char* const window_name = "RUSHING INTO 1限!!";
const unsigned int sleep_milli_time = 15;

//グローバル変数
Position hodai_vertex = {0.0, -250.0}; //砲台(三角形)の一番上の頂点..y座標は
Position mouse_position = {0.0, 0.0};
Ray_Position ray_hodai = {FALSE, 0.0, 0.0};
Ray_Position ray_inv[INV_RAY] = {{FALSE, 0.0, 160.0}, {FALSE, 0.0, 160.0}, {FALSE, 0.0, 160.0}};
Invader inv[INV_HEIGHT][INV_WIDTH];
unsigned int inv_tex_id_1;
unsigned int inv_tex_id_2;
unsigned int menu_tex_id;

//ゲーム内容関連
unsigned int hero_life = 3; //ライフ
unsigned int point = 0; //点数
unsigned int destroy = 0; //金森先生破壊数
unsigned int window_num = 0; //0:メニュー 1:ゲーム 2:リザルト

int main(int argc, char* argv[]){

	init_invader();
	init_ray(&ray_hodai);

	glutInit(&argc, argv);

	/*ウィンドウの位置とサイズ指定*/
	glutInitWindowPosition(window_position_x, window_position_y);
	glutInitWindowSize(window_size_width, window_size_height);

	/*ウィンドウ生成*/
	glutCreateWindow(window_name);

	/*テクスチャ読み込み*/
	load_tex("data/Copied_Asc_color.ppm", &inv_tex_id_1, 4, 4); //細かい画像を表示させたりできる！
	load_tex("data/71i-GSPlL8L._SY355_.ppm", &inv_tex_id_2, 355, 355);
	load_tex("data/71i-GSPlL8L._SY355_.ppm", &menu_tex_id, 355, 355);

	/*背景色指定(黒)*/
	glutInitDisplayMode(GLUT_RGBA);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/*画面リサイズ時の処理*/
	glutReshapeFunc(resize);

	/*マウスの座標取得*/
	glutPassiveMotionFunc(mouse);
	glutMotionFunc(mouse);

	/*マウスのボタン入力取得*/
	glutMouseFunc(mouse_button);

	/*描画*/
	glutDisplayFunc(display);

	/*sleep_milli_timeミリ秒後に再描画*/
	glutTimerFunc(sleep_milli_time, motion, 0);

	/*ウィンドウが閉じるまでループ*/
	glutMainLoop();

	return 0;
}
