#include"struct.h"

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


//定数
const int window_position_x = 0;
const int window_position_y = 0;
const int window_size_width = 640;
const int window_size_height = 640;
const char* const window_name = "PACMAN-Kanamori edition-";
const unsigned int sleep_milli_time = 15;

//グローバル変数らへんコピペしてない
unsigned int kanamori_tex_id; //金森先生
unsigned int enemy_tex_id_0;  //イバやん
unsigned int enemy_tex_id_1;  //ヤクザ
unsigned int enemy_tex_id_2;  //インテリヤクザ
unsigned int nabe_tex_id;	//牛膳鍋
unsigned int map_tex_id0; //map 0通路
unsigned int map_tex_id1; //map 1壁
unsigned int map_tex_id2; //map 2コインクーポン
unsigned int menu_tex_id;
unsigned int emono_tex_id; //獲物の金森先生

double prevTime, rapTime;

Kanamori kanamori;
Kanamori Emono;
Kanamori Nabe;
Enemy enemy[3];

int map[15][20] = { //y xの座標順なので注意...!! 0が通路、1が壁、2がエサ
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,2,2,2,2,2,2,2,1,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,2,2,1,0,0,0,0,0,1},
  {1,0,0,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1},
  {1,2,2,0,1,0,2,2,2,1,2,2,2,0,0,0,0,2,2,1},
  {1,2,2,0,1,0,2,2,2,1,2,2,2,0,0,0,0,2,2,1},
  {1,2,2,0,0,0,2,2,2,0,2,2,2,0,0,0,0,2,2,1},
  {1,2,2,0,0,0,1,1,1,1,1,1,1,1,0,0,0,2,2,1},
  {1,2,2,0,0,0,2,2,2,0,2,2,2,0,0,0,0,2,2,1},
  {1,2,2,0,0,0,2,2,2,1,2,2,2,0,1,0,0,2,2,1},
  {1,2,2,0,0,0,2,2,2,1,2,2,2,0,1,0,0,2,2,1},
  {1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,0,2,2,1},
  {1,0,0,0,0,1,2,2,2,2,2,2,2,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,2,2,2,2,2,2,2,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};


//ゲーム内容関連
unsigned int HP = 2; //ライフ
unsigned int point = 0; //点数
unsigned int gyunabecounter = 0; //牛前鍋吸収数
int coinNum = 0; //クーポン何枚とった？
unsigned int window_num = 0; //0:メニュー 1:ゲーム 2:リザルト //関数内でグローバル変数を書き換えても大丈夫か？？->OKnなはず

int main(int argc, char* argv[]){

  srand((unsigned char)time(NULL));

  Init_Kanamori(); //Init系はまとめてもいいかもね分割の意味があんまない
  Init_Enemy();
  Init_Emono();
  Init_Nabe();

  glutInit(&argc, argv);

  /*ウィンドウの位置とサイズ指定*/
  glutInitWindowPosition(window_position_x, window_position_y);
  glutInitWindowSize(window_size_width, window_size_height);

  /*ウィンドウ生成*/
  glutCreateWindow(window_name);

  /*テクスチャ読み込み*/
  load_tex("kanamori2.png", &kanamori_tex_id, 64, 64); //細かい画像を表示させたりできる！
  load_tex("furyo_shounen.png", &enemy_tex_id_0, 64, 64);
  load_tex("kurufuku_man.png", &enemy_tex_id_1, 64, 64);
  load_tex("yakuza_kowai.png", &enemy_tex_id_2, 64, 64);
  load_tex("nabe.png", &nabe_tex_id, 64, 64);
  load_tex("pacman_chip0.png", &map_tex_id0, 64, 64);
  load_tex("pacman_chip1.png", &map_tex_id1, 64, 64);
  load_tex("pacman_chip2.png", &map_tex_id2, 64, 64);
  load_tex("kanamori1.png", &emono_tex_id, 64, 64);
  load_tex("kanamori4.png", &menu_tex_id, 642, 681);

  /*背景色指定(黒)*/
  //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitDisplayMode(GLUT_RGBA);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  /*画面リサイズ時の処理*/
  glutReshapeFunc(reshape); //resizeの方でもいける？

  /*マウスの座標取得*/
  //	glutPassiveMotionFunc(mouse);
  //	glutMotionFunc(mouse);

  /*マウスのボタン入力取得*/
  //	glutMouseFunc(mouse_button);

  glutKeyboardFunc(keyboard);
  glutKeyboardFunc(special);

  glutIdleFunc(idle);

  /*描画*/
  glutDisplayFunc(display);

  /*sleep_milli_timeミリ秒後に再描画*/
  //glutTimerFunc(sleep_milli_time, motion, 0);
  sleep(80);

  /*ウィンドウが閉じるまでループ*/
  glutMainLoop();

  return 0;
}

/*
void resize(int w, int h){
glViewport(0, 0, w, h);
glLoadIdentity();
glOrtho(-w / 2.0, w / 2.0, -h / 2.0, h / 2.0, -1.0, 1.0);
}*/

void reshape(int w, int h)
{
  if (h < 1) return;

  w = window_size_width ;
  h = window_size_height ;

  glViewport(0, 0, w, h); /* ウィンドウの描画範囲を指定 */

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);

  glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}

void special(int key, int x, int y)
{
  window_num = 1; //ここでゲーム画面に映るはず！！！！
  switch (key)
  {
    case GLUT_KEY_UP:
    if (map[(kanamori.y + 1)][kanamori.x] != 1){
      kanamori.y += 1;
    }
    Judgement(); //通った道にコインがおいてあるか否か判定
    EnemyMove();
    if(!(Emono.x == 0 && Emono.y == 0)) EmonoMove(); //獲物が通路にいる時は動きまくるしくみ
    break;
    case GLUT_KEY_DOWN:
    if (map[(kanamori.y - 1)][kanamori.x] != 1){
      kanamori.y -= 1;
    }
    Judgement();
    EnemyMove();
    if(!(Emono.x == 0 && Emono.y == 0)) EmonoMove();
    break;
    case GLUT_KEY_RIGHT:
    if (map[kanamori.y][kanamori.x+1] != 1){
      kanamori.x += 1;
    }
    Judgement();
    EnemyMove();
    if(!(Emono.x == 0 && Emono.y == 0)) EmonoMove();
    break;
    case GLUT_KEY_LEFT:
    if (map[kanamori.y][kanamori.x-1] != 1){
      kanamori.x -= 1;
    }
    Judgement();
    EnemyMove();
    if(!(Emono.x == 0 && Emono.y == 0)) EmonoMove();
    break;
    default:
    EnemyMove();
    if(!(Emono.x == 0 && Emono.y == 0)) EmonoMove();
    break;
  }

  glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}


void idle(void)
{
  EnemyMove();
  display();
}

/* キーボード入力のためのコールバック関数 */
void keyboard(unsigned char key, int x, int y)
{
  window_num = 1;
  switch (key)
  {/*
    case 'w':
    if (map[(kanamori.y + 1)][kanamori.x] != 1) //めんどいからコイン取得とかの処理追加してへんよ
    kanamori.y += 1;
    break;
    case 'x':
    if map[(kanamori.y - 1)][kanamori.x] != 1)
    kanamori.y -= 1;
    break;
    case 'd':
    if map[kanamori.y][kanamori.x+1] != 1)
    kanamori.x += 1;
    break;
    case 'a':
    if map[kanamori.y][kanamori.x-1] != 1)
    kanamori.x -= 1;
    break;
*/
    case 'R': //Rを押したらタイトル画面に戻る？
    case 'r':
    window_num = 0;
    HP = 2;
    point = 0;
    gyunabecounter =0;
    coinNum = 0;

    break;
    case 'q':   /* キーボードの 'q' 'Q' 'ESC' を押すとプログラム終了 */
    case 'Q':
    case '\033':
    exit(-1);
    break;
    default:
    break;
  }

  glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}


//void display(void)
//{
/* ウィンドウを消去 … glClearColor で指定した色で塗りつぶし */
//	glClear(GL_COLOR_BUFFER_BIT);

//	if ( IsImageDataAllocated(&g_Image)) /* もし画像が読み込めていたら */
//	{
//		/* 座標 (g_ImagePosX, g_ImagePosY) の位置に、画像を表示 */
//		DrawImageData(&g_Image, g_ImagePosX, g_ImagePosY);
//	}

//	glutSwapBuffers(); //glFlushでも良さそう

//}

void display(void){
  if(window_num == 0){ //メニュー画面
    glClear(GL_COLOR_BUFFER_BIT);
    //draw_char("INVADER GAME()", -100.0, 0.0);
    //draw_char("LEFT CLICK START", -100.0, -50.0);
    draw_menu();
    glFlush();

  }else if(window_num == 1){ //ゲーム画面
    glClear(GL_COLOR_BUFFER_BIT);
    //line((Position){-320.0, GAME_OVER_LINE}, (Position){-300.0, GAME_OVER_LINE}); //目印
    //line((Position){ 320.0, GAME_OVER_LINE}, (Position){ 300.0, GAME_OVER_LINE}); //目印
    draw_map();
    draw_kanamori();

    draw_enemy(enemy_tex_id_0, enemy[0]);
    draw_enemy(enemy_tex_id_1, enemy[1]);
    draw_enemy(enemy_tex_id_2, enemy[2]);

    if(!(Emono.x == 0 && Emono.y == 0)) draw_emono();
    //glColor3d(1.0, 1.0, 0.0); //glColor3d()の位置は設計ミス でも敵と味方の光線の色は分けたい
  //  for(int i = 0; i < INV_RAY; i++){
    //  glColor3d(1.0, 0.0, 0.5);
      //draw_ray(ray_inv + i);
    //}
    draw_char("Point:", -320.0, -315.0); //点数表示位置
    draw_num(point, -260.0,-315.0); //点数表示(座標は微調整で)

    draw_char("HP:", 260.0, -315.0); //残基表示
    draw_num(HP, 300.0, -315.0); //座標は微調整

    if((rapTime = GetRapTime(prevTime))>= 1000*30){ //30秒後に牛膳鍋がランダムな位置に出現するしくみ
      prevTime = GetTime();
      draw_nabe();
    }

    if(coinNum <=0){
      window_num = 2;
    }

    sleep(80); //待ち時間設けることで早すぎないように。この位置におくか、自機の動き入力タイミングで動かすかはお好みで良いのか？
    glFlush();

  }else{ //リザルト画面
    rapTime = GetRapTime(prevTime);
    point -= rapTime/500 ; //30秒後からはもたついてると2ポイントづつ毎秒減点される。
    glClear(GL_COLOR_BUFFER_BIT);
    draw_char("Point:", -30.0, 25.0); //点数表示位置
    draw_char("Rを押せばもう一度遊べるよ", -60.0, 50.0);
    draw_num(point, 30.0, 25.0); //点数表示(座標は微調整で)
    glFlush(); //ランキングとセーブデータの実装がまだやな!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }
}
