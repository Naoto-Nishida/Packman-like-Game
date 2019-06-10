#include"func.h"

void motion(int value){

	if(window_num == 0){ //メニュー画面時初期化
		hero_life = 3;
		point = 0;
		destroy = 0;
		init_ichigen();
	}

	/*砲台の位置更新*/
	hodai_vertex.x = -window_size_width / 2 + mouse_position.x;

	/*インベーダーの位置更新*/
	static int inv_move_flag = 0; //インベーダーの左右の動きのフラグ(0:左へ 1:右へ)
	if(inv_move_flag == 0){
		for(int i = 0; i < INV_HEIGHT; i++){
			for(int j = 0; j < INV_WIDTH; j++){
				inv[i][j].x -= 1.0; //インベーダーの移動スピード
			}
		}
	}else if(inv_move_flag == 1){
		for(int i = 0; i < INV_HEIGHT; i++){
			for(int j = 0; j < INV_WIDTH; j++){
				inv[i][j].x += 1.0; //インベーダーの移動スピード
			}
		}
	}

	//端まで行ったときの動作
	if(inv[0][0].x <= -(window_size_width / 2) && inv_move_flag == 0){
		inv_move_flag = 1;
		for(int i = 0; i < INV_HEIGHT; i++){
			for(int j = 0; j < INV_WIDTH; j++){
				inv[i][j].y -= 32.0; //下がる距離
			}
		}
	}else if(inv[0][0].x >= 0.0 && inv_move_flag == 1){
		inv_move_flag = 0;
		for(int i = 0; i < INV_HEIGHT; i++){
			for(int j = 0; j < INV_WIDTH; j++){
				inv[i][j].y -= 32.0; //下がる距離
			}
		}
	}

	/*砲台の光線の位置更新*/
	if(ray_hodai.flag == FALSE){
		ray_hodai.begin_x = hodai_vertex.x;
	}else{
		ray_hodai.begin_y += 15.0;//光線の速度設定
	}

	/*砲台の光線の描画範囲外時処理*/
	if(ray_hodai.begin_y >= (window_size_height / 2.0)){
		init_ray(&ray_hodai);
	}

	/*インベーダーの光線*/
	for(int i = 0; i < INV_RAY; i++){
		static double speed[INV_RAY];
		int h = xorshift() % 5; //高さランダム
		int w = xorshift() % 10; //横ランダム
		if(ray_inv[i].flag == FALSE && inv[h][w].status == TRUE){ //インベーダーのランダムな位置がTRUEであれば描写
			ray_inv[i].begin_y = inv[h][w].y - 32.0;
			ray_inv[i].begin_x = inv[h][w].x + 16.0; //インベーダーの最下層のみから発射inv4層目 invは左上座標なので中心から+16

			int tmp = xorshift() % 11; //スピード上限
			while(tmp < 5.0){ //スピード下限
				tmp = xorshift() % 11; //スピード上限
			}
			speed[i] = tmp;//スピードランダム*/

			ray_inv[i].flag = TRUE; //光線描画
		}else if(ray_inv[i].flag == TRUE){
			ray_inv[i].begin_y -= speed[i];
		}

		/*光線の描画外範囲処理*/
		if(ray_inv[i].begin_y <= hodai_vertex.y - 20){ //砲台の下よりちょっとで光線削除 画面最下でもいいが点数表示のため
			ray_inv[i].begin_y = window_size_height / 4.0;
			ray_inv[i].flag = FALSE;
		}
	}

	/*当たり判定(ray_hodai)*/
	for(int i = 0; i < INV_HEIGHT; i++){
		for(int j = 0; j < INV_WIDTH; j++){
			if(inv[i][j].x - ray_hodai.begin_x <= 0.0 && inv[i][j].x - ray_hodai.begin_x >= -32.0 && inv[i][j].y - ray_hodai.begin_y <= 32.0 && inv[i][j].status == TRUE){
				inv[i][j].status = FALSE;
				point += 100; //得点
				destroy++; //インベーダー撃退数
				init_ray(&ray_hodai);
			}
		}
	}

	/*当たり判定(ray_inv)*/
	for(int i = 0; i < INV_RAY; i++){
		if(ray_inv[i].begin_y <= hodai_vertex.y && fabs(hodai_vertex.x - ray_inv[i].begin_x) <= 10.0){
			hodai_life--;
			ray_inv[i].begin_y = window_size_height / 4.0;
			ray_inv[i].flag = FALSE;
		}
	}

	for(int i = 0; i < INV_HEIGHT; i++){
		for(int j = 0; j < INV_WIDTH; j++){
			if(inv[i][j].status == TRUE && inv[i][j].y <= GAME_OVER_LINE){ //インベーダーが目印のy座標へ到達したらゲーム終了
				window_num = 2;
			}
		}
	}

	if(hodai_life <= 0 || destroy >= 50){ //リザルト画面へ
		window_num = 2;
	}

	/*再描画*/
	glutPostRedisplay();

	/*再実行*/
	glutTimerFunc(sleep_milli_time, motion, 0);
}
