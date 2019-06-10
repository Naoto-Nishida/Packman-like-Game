#include"func.h"

void display(void){
	if(window_num == 0){ //メニュー画面
		glClear(GL_COLOR_BUFFER_BIT);
		//draw_char("INVADER GAME()", -100.0, 0.0);
		//draw_char("LEFT CLICK START", -100.0, -50.0);
		draw_menu();
		glFlush();

	}else if(window_num == 1){ //ゲーム画面
		glClear(GL_COLOR_BUFFER_BIT);
		line((Position){-320.0, GAME_OVER_LINE}, (Position){-300.0, GAME_OVER_LINE}); //目印
		line((Position){ 320.0, GAME_OVER_LINE}, (Position){ 300.0, GAME_OVER_LINE}); //目印
		draw_invader();
		draw_hodai(&hodai_vertex);
		glColor3d(1.0, 1.0, 0.0); //glColor3d()の位置は設計ミス でも敵と味方の光線の色は分けたい
		draw_ray(&ray_hodai);
		for(int i = 0; i < INV_RAY; i++){
			glColor3d(1.0, 0.0, 0.5);
			draw_ray(ray_inv + i);
		}
		draw_char("Point:", -320.0, -315.0); //点数表示位置
		draw_num(point, -260.0,-315.0); //点数表示(座標は微調整で)

		draw_char("HP:", 260.0, -315.0); //残基表示
		draw_num(hodai_life, 300.0, -315.0); //座標は微調整

		glFlush();

	}else{ //リザルト画面
		glClear(GL_COLOR_BUFFER_BIT);
		draw_char("Point:", -30.0, 25.0); //点数表示位置
		draw_num(point, 30.0, 25.0); //点数表示(座標は微調整で)
		glFlush();
	}
}
