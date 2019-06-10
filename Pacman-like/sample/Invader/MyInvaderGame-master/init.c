#include"func.h"

void init_ichigen(void){
	/*
	for(int i = 0; i < INV_HEIGHT; i++){
		for(int j = 0; j < INV_WIDTH; j++){
			inv[i][j].status = TRUE;
			inv[i][j].x = (window_size_width / INV_WIDTH / 2) * j;
			inv[i][j].y = (window_size_height / 2) - (window_size_height / INV_HEIGHT / 4) * i;
		}
	}
	*/
	
}

void init_ray(Ray_Position *ptr_struct){
	ptr_struct->begin_x = 0.0;
	ptr_struct->begin_y = hodai_vertex.y;
	ptr_struct->flag = FALSE;
}
