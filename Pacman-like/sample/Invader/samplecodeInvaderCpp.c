#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
using namespace std;

#define WIDTH 640                       //画面の横幅
#define HEIGHT 480                      //画面の縦幅
#define PI 3.14159265358979             //円周率

//////////////////////////////////////////////////////////

int invcop;                             //インベーダーの複製の座標
static float invxm = 0;                 //インベーダーの移動値
static int invym = 0;                   //端に行くごとに下がる値
int il1,il2,il3,il4,il5,il6,il7,il8;    //インベーダーの生死判定
static int inv_Bx;                      //インベーダー弾のx座標
static float inv_By = 80;               //インベーダーの弾のy座標
int invr = 20;                          //インベーダーの半径
int inv_Bcop;                           //インベーダーの弾の複製の座標
int sei = 0;                            //常に正になる値
int b1,b2,b3,b4,b5,b6,b7,b8;            //インベーダーの弾の発射条件

//////////////////////////////////////////////////////////

int uxm;                                //ユニットの移動値
int ul;                                 //ユニットの生死判定
int bull;                               //ユニットの弾のキーボード
static int unitx = 312, unity = 300;    //ユニットのx座標
static int unit_Bx;                     //ユニット弾のx座標
static int unit_By = 408;               //ユニットの弾のy座標

//////////////////////////////////////////////////////////

//1ブロック
void Quad(int x,int y){
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x,y+4);
    glVertex2f(x+4,y+4);
    glVertex2f(x+4,y);
    glEnd();
}

//弾
void Point(int x,int y,float size){
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2i(x , y);
    glEnd();
}

//////////////////////////////////////////////////////////

//インベーダーのクラス
class Inv{
public:
    void inv();
    void copy();
};

//インベーダーの形
void Inv::inv(){
    for(int n = 0; n <= 20; n += 20){       //インベーダーの横一列
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+48+invcop+invxm,44+invym);
    }
    for(int n = 0; n <= 12; n += 12){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+52+invcop+invxm,48+invym);
    }
    for(int n = 0; n <= 20; n += 4){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+48+invcop+invxm,52+invym);
    }
    for(int n = 0; n <= 28; n += 4){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+44+invcop+invxm,56+invym);
    }
    for(int n = 0; n <= 12; n += 12){
        glColor4f(0.0f,0.0f,0.0f,1.0f);
        Quad(n+52+invcop+invxm,56+invym);
    }
    for(int n = 0; n <= 36; n += 4){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+40+invcop+invxm,60+invym);
    }
    for(int n = 0; n <= 36; n += 4){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+40+invcop+invxm,64+invym);
    }
    for(int n = 0; n <= 28; n += 28){
        glColor4f(0.0f,0.0f,0.0f,1.0f);
        Quad(n+44+invcop+invxm,64+invym);
    }
    for(int n = 0; n <= 8; n += 8){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+40+invcop+invxm,68+invym);
    }
    for(int n = 0; n <= 8; n += 8){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+68+invcop+invxm,68+invym);
    }
    for(int n = 0; n <= 12; n += 12){
        glColor4f(1.0f,0.0f,0.0f,1.0f);
        Quad(n+52+invcop+invxm,72+invym);
    }
    glFlush();
}

//インベーダーを8体描画する引数
void Inv::copy(){
    static GLboolean isUp;
    if (invxm > 0)isUp = GL_FALSE;              //インベーダーのx座標の移動値
    else if (invxm <= -40)isUp = GL_TRUE;
    invxm += (isUp == GL_TRUE ? 0.4 : -0.4);
    if(invxm > 0){                              //y座標の移動値
        invym += 20;
    }else if(invxm <= -40){
        invym += 20;
    }
    if(il1 == 1){                               //死んでいると描画しないように

    }else{
        invcop = 0;
        inv();
    }
    if(il2 == 2){

    }else{
        invcop = 80;
        inv();
    }
    if(il3 == 3){

    }else{
        invcop = 160;
        inv();
    }
    if(il4 == 4){

    }else{
        invcop = 240;
        inv();
    }
    if(il5 == 5){

    }else{
        invcop = 320;
        inv();
    }
    if(il6 == 6){

    }else{
        invcop = 400;
        inv();
    }
    if(il7 == 7){

    }else{
        invcop = 480;
        inv();
    }
    if(il8 == 8){

    }else{
        invcop = 560;
        inv();
    }
}

//////////////////////////////////////////////////////////

//ユニットのクラス
class Unit{
public:
    void unit();
};

//ユニットを描画する引数
void Unit::unit(){
    if(uxm == 1){                           //ユニットの移動値
        if(unitx < 586 || unity < 594){
        unitx+=4; unity+=4;
        }
    }else if(uxm == 2){
        if(unitx > 8 || unity > 0){
        unitx-=4; unity-=4;
        }
    }
    if(ul == 1){                            //死んでいると描画しないように
        exit(0);
    }else{
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        for(int n = 0; n <= 16; n += 4){
            Quad(n+unitx,408);
        }
        for(int n = 0; n <= 16; n += 4){
            Quad(n+unitx,412);
        }
        for(int n = 0; n <= 16; n += 4){
            Quad(n+unitx,416);
        }
        for(int n = 0; n <= 40; n += 4){
            Quad(n+unity,420);
        }
        for(int n = 0; n <= 40; n += 4){
            Quad(n+unity,424);
        }
        for(int n = 0; n <= 40; n += 4){
            Quad(n+unity,428);
        }
        for(int n = 0; n <= 40; n += 4){
            Quad(n+unity,432);
        }
        glFlush();
    }
}

//////////////////////////////////////////////////////////

//ユニットの弾のクラス
class Bullet{
public:
    void bullet();
};

//弾の描画、当たり判定
void Bullet::bullet(){
    int y2 = 60;                                //インベーダーの中心のy座標
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    if(bull == 3 && ul != 1){                   //死んでいると発射しないように
        if(unit_By == 408){                     //弾の発射時のみユニットのx座標をとる
            unit_Bx = unitx+8;
        }
        unit_By -= 12;                          //弾の速度
        Point(unit_Bx, unit_By, 4);
        if((unit_Bx-(60+invxm))*(unit_Bx-(60+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il1 = 1;
        }
        if((unit_Bx-(140+invxm))*(unit_Bx-(140+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il2 = 2;
        }
        if((unit_Bx-(220+invxm))*(unit_Bx-(220+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il3 = 3;
        }
        if((unit_Bx-(300+invxm))*(unit_Bx-(300+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il4 = 4;
        }
        if((unit_Bx-(380+invxm))*(unit_Bx-(380+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il5 = 5;
        }
        if((unit_Bx-(460+invxm))*(unit_Bx-(460+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il6 = 6;
        }
        if((unit_Bx-(540+invxm))*(unit_Bx-(540+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il7 = 7;
        }
        if((unit_Bx-(620+invxm))*(unit_Bx-(620+invxm))+(unit_By-(y2+invym))*(unit_By-(y2+invym)) <= (invr*invr)){
            il8 = 8;
        }
        if(unit_By < 0){                        //弾が画面外に出た時元の位置に
            unit_By = 408;
            bull = 0;
        }
    }
}

//////////////////////////////////////////////////////////

//インベーダーの弾のクラス
class Ibullet{
public:
    void ibullet();
    void shot();
};

void Ibullet::ibullet(){                        //弾の描画、当たり判定
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    if(sei == 0){
        if(inv_By == 80){                       //弾の発射時のみユニットのx座標をとる
            inv_Bx = invxm+60;
        }
        Point(inv_Bx+inv_Bcop, inv_By+invym, 4);
        if((inv_Bx+inv_Bcop-unitx-10)*(inv_Bx+inv_Bcop-unitx-10)+(inv_By+invym-420)*(inv_By+invym-420) <= (20*20)){
            ul = 1;
        }
    }
}

//弾の条件、複製
void Ibullet::shot(){
    inv_By += 10;                               //弾の速度
    if(inv_By > 480){                           //2分の1の確率で発射する
            b1 = rand() % 2 + 1;
            b2 = rand() % 2 + 1;
            b3 = rand() % 2 + 1;
            b4 = rand() % 2 + 1;
            b5 = rand() % 2 + 1;
            b6 = rand() % 2 + 1;
            b7 = rand() % 2 + 1;
            b8 = rand() % 2 + 1;
            inv_By = 80;
            sei = 0;
    }
    if(il1 == 1){                               //死んでいると発射しないように

    }else if(b1 == 1){
        inv_Bcop = 0;
        ibullet();
    }
    if(il2 == 2){

    }else if(b2 == 1){
        inv_Bcop = 80;
        ibullet();
    }
    if(il3 == 3){

    }else if(b3 == 1){
        inv_Bcop = 160;
        ibullet();
    }
    if(il4 == 4){

    }else if(b4 == 1){
        inv_Bcop = 240;
        ibullet();
    }
    if(il5 == 5){

    }else if(b5 == 1){
        inv_Bcop = 320;
        ibullet();
    }
    if(il6 == 6){

    }else if(b6 == 1){
        inv_Bcop = 400;
        ibullet();
    }
    if(il7 == 7){

    }else if(b7 == 1){
        inv_Bcop = 480;
        ibullet();
    }
    if(il8 == 8){

    }else if(b8 == 1){
        inv_Bcop = 560;
        ibullet();
    }
    if(il1 == 1 && il2 == 2 && il3 == 3 && il4 == 4 && il5 == 5 && il6 == 6 && il7 == 7 && il8 == 8){
        exit(0);
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Inv i;
    Unit u;
    Bullet b;
    Ibullet ib;
    i.copy();
    u.unit();
    b.bullet();
    ib.shot();
    glutSwapBuffers();
}

void Idle() {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case ' ': bull = 3;                 //[ ]を押すと弾を発射する
            glutPostRedisplay();
            break;
    }
}

void Skey(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT: uxm = 2;        //[←]を押すと左に動く
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: uxm = 1;       //[→]を押すと右に動く
            glutPostRedisplay();
            break;
    }
}

void Supkey(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT: uxm = 0;        //[←]を離すと止まる
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: uxm = 0;       //[→]を離すと止まる
            glutPostRedisplay();
            break;
    }
}

void Init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
}

int main(int argc, char *argv[]){
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("test");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Skey);
    glutSpecialUpFunc(Supkey);
    glutIdleFunc(Idle);
    Init();
    glutMainLoop();
    return 0;
}
