#include "GenericTimer.h"
#include "struct.h"


void Init_Kanamori(){
	kanamori.x = 1;
	kanamori.y = 1;

	StartTimer();
	prevTime = GetTime();

	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 20; x++) {
			if (map[y][x] == 2) coinNum++;
		}
	}
}

void Init_Enemy(){
	for(int i=0; i<3; i++){
		enemy[i].x = 10;  //うまい具合に座標指定して！
		enemy[i].y = 15;
	}
}

void Init_Emono(){
	Emono.x = 15;
	Emono.y = 12;
}

void Init_Nabe(){
	Nabe.x=0;
	Nabe.y=0;
}

int IsCoin(){ //グローバルへんすうでkanamoriはあるから今回は引数で渡す必要ないね
	if(map[kanamori.y][kanamori.x] == 2){
		return 1;
	}
	else{
		return 0;
	}
}

int IsGyuzen(){
	if(kanamori.y == Nabe.y && kanamori.x == Nabe.x){
		return 1;
	}
	else{
		return 0;
	}
}

int IsEmono(){
	if(kanamori.y == Emono.y && kanamori.x == Emono.x){
		return 1;
	}
	else{
		return 0;
	}
}

//余裕があったら第３のヤクザを時間経過とともに出現させるようにしたい
void EnemyMove(){ //敵キャラに個性を出したい！のでforではやらない。(結局は確率の起こりやすさだからうまく変数設定したらやれるのかな)
	int ex, ey; //現在位置の確保用
	ex = enemy[0].x;
	ey = enemy[0].y;
	if(rand() %5 == 0){ //不良はだいたい適当なのでそのへんふらついてる感じ
		if(enemy[0].x > kanamori.x) enemy[0].x--;
		if(enemy[0].x < kanamori.x) enemy[0].x++;
		if(enemy[0].y > kanamori.y) enemy[0].y--;
		if(enemy[0].y < kanamori.y) enemy[0].y++;
	}
	else{
		enemy[0].x += rand() % 3 -1;
		enemy[0].y += rand() % 3 -1;
	}
	if(map[enemy[0].y][enemy[0].y] != 1){
		enemy[0].x = ex;
		enemy[0].y = ey;
	}


	ex = enemy[1].x;
	ey = enemy[1].y;
	if(rand() %3 == 0){ //黒服は大人だけど割と抜けてる感じなので(カイジとか的に)
		if(enemy[1].x > kanamori.x) enemy[1].x--;
		if(enemy[1].x < kanamori.x) enemy[1].x++;
		if(enemy[1].y > kanamori.y) enemy[1].y--;
		if(enemy[1].y < kanamori.y) enemy[1].y++;
	}
	else{
		enemy[1].x += rand() % 3 -1;
		enemy[1].y += rand() % 3 -1;
	}
	if(map[enemy[1].y][enemy[1].y] != 1){
		enemy[1].x = ex;
		enemy[1].y = ey;
	}

	ex = enemy[2].x;
	ey = enemy[2].y;
	if(rand() %3 == 0){ //ヤクザはやっぱり怖いので
		enemy[2].x += rand() % 3 -1;
		enemy[2].y += rand() % 3 -1;
	}
	else{
		if(enemy[2].x > kanamori.x) enemy[2].x--;
		if(enemy[2].x < kanamori.x) enemy[2].x++;
		if(enemy[2].y > kanamori.y) enemy[2].y--;
		if(enemy[2].y < kanamori.y) enemy[2].y++;
	}
	if(map[enemy[2].y][enemy[2].y] != 1){
		enemy[2].x = ex;
		enemy[2].y = ey;
	}
}

void EmonoMove(){
	int ex, ey; //現在位置の確保用
	ex = Emono.x;
	ey = Emono.y;
	if(rand() %2 == 0){ //獲物の金森先生はシャイなので逃げる
		if(Emono.x > kanamori.x) Emono.x++;
		if(Emono.x < kanamori.x) Emono.x--;
		if(Emono.y > kanamori.y) Emono.y++;
		if(Emono.y < kanamori.y) Emono.y--;
	}
	else{
		Emono.x += rand() % 3 -1;
		Emono.y += rand() % 3 -1;
	}
	if(map[Emono.y][Emono.y] != 1){
		Emono.x = ex;
		Emono.y = ey;
	}
}


void Judgement(){
	if(IsCoin()){
		point+=10;
		map[kanamori.y][kanamori.x] = 0;
		coinNum--;
	}
	if(IsGyuzen()){
		point+=200;
		map[kanamori.y][kanamori.x] = 0;
	}
	if(IsEmono()){
		point += 500;
		map[kanamori.y][kanamori.x] = 0;
		Emono.x =0;
		Emono.y = 0;
	}
}
