#include"func.h"

void mouse(int x, int y){
	mouse_position.x = x;
	mouse_position.y = y;
}

void mouse_button(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ray_hodai.flag == FALSE){
		ray_hodai.flag = TRUE;
	} //光線のフラグtrue

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && window_num == 0){ //ゲーム画面へ
		window_num = 1;
	}else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && window_num == 2){ //リザからスタート画面へ
		window_num = 0;
	}
}
