///////////////////////////////////////////////////////////////////////////////
//	ジャンピングゲーム

#include "el.h"

#define MAIN_SCREEN 1

#define ACCEL_X 0.6			// 加速度
#define MAX_SPEED 8			// 最高速度
#define JUMP_POWER 20		// ジャンプ力

void MainScreen(void);

DDOBJ jiki;		// 自機ビットマップ

///////////////////////////////////////////////////////////////////////////////
//	メイン関数

int elMain("ジャンピング");
{
	elWindow(640, 480, FALSE);
	elLoop()
	{
		elSetScreen(MAIN_SCREEN, MainScreen());
	}
	elExitMain();
}

///////////////////////////////////////////////////////////////////////////////
//	ウインドウ生成関数

void elCreate(void)
{
	elDraw::Screen(640, 480);
	jiki = elDraw::LoadObject("chr.bmp");
	elCallScreen(MAIN_SCREEN);
}

///////////////////////////////////////////////////////////////////////////////
//	キーボード関数

void elKeyboard(void)
{
	case VK_ESCAPE:
	{
		elDraw::Exit();
		break;
	}
	elExitKeyboard();
}

///////////////////////////////////////////////////////////////////////////////
//	イベント関数

long elEvent(void)
{
	elExitEvent();
}

///////////////////////////////////////////////////////////////////////////////
//	メイン画面

void MainScreen(void)
{
	static int jx = 160, jy = 280;		// 自機座標
	static double vx = 0.0, vy;			// 自機速度
	static bool jumpFlag = false;		// ジャンプ中なら true
	static int kl = FREE_KEY;			// 左キーの状態
	static int kr = FREE_KEY;			// 右キーの状態
	static int ks = FREE_KEY;			// スペースキーの状態
	static int mw[20] = {1000};			// マップの幅
	static int mnum = 1;				// マップの数
	static int mkt = 1;					// マップ先頭の種類(0:穴 1:地面)
	static bool overFlag = false;		// ゲームオーバーなら true
	static int score = 0;				// スコア
	int i;

	elDraw::Clear();

	// キー入力
	elSystem::GetKey(VK_LEFT, &kl);
	elSystem::GetKey(VK_RIGHT, &kr);
	elSystem::GetKey(VK_SPACE, &ks);
	// 左右移動
	if (kl != FREE_KEY) {
		vx -= ACCEL_X;
		if (vx < -MAX_SPEED) vx = -MAX_SPEED;
	} else if (kr != FREE_KEY) {
		vx += ACCEL_X;
		if (vx > MAX_SPEED) vx = MAX_SPEED;
	} else {
		if (vx < 0) vx++;
		else if (vx > 0) vx--;
	}
	jx += int(vx);
	if (jx < 0) {jx = 0; vx = 0;}
	else if (jx > 576) {jx = 576; vx = 0;}
	// ジャンプ
	if (!jumpFlag) {
		if (ks != FREE_KEY) {
			vy = -JUMP_POWER;
			jumpFlag = true;
		}
	} else {
		vy++;
		jy += int(vy);
		if (jy > 280) {
			jy = 280;
			jumpFlag = false;
		}
	}

	// マップ描画
	int mk = mkt;		// 現在のマップの種類
	int mx = 0;			// 現在のマップの左端座標
	for (i = 0; i < mnum; i++) {
		if (mk) elDraw::Box(mx, 344, mw[i] + mx, 360, RGB(255, 255, 200), RGB(100, 255, 150), 1);
		else if (!jumpFlag && mx <= jx && mw[i] + mx >= jx + 64) overFlag = true;
		mk = 1 - mk;
		mx += mw[i];
	}
	if (mx < 640) {
		int ml = score / 50;
		if (ml > 200) ml = 200;
		if (mk) mw[mnum] = 315 - ml - rand() % 100;
		else mw[mnum] = 64 + ml + rand() % 100;
		mnum++;
	}
	mw[0] = mw[0] - 4;
	if (mw[0] <= 0) {
		mw[1] += mw[0];
		for (i = 0; i < mnum - 1; i++) mw[i] = mw[i + 1];
		mnum--;
		mkt = 1 - mkt;
	}
	// 自機描画
	int y = 0;
	if (overFlag) y = 32;
	elDraw::Layer(jx, jy + y, jiki, 0, 0, 64, 64);

	// スコア表示
	SHOW2(0, 0, "SCORE:%d", score++);

	elDraw::Refresh();

	if (overFlag) {
		elSystem::Message("GAME OVER!");
		elDraw::Exit();
	}
}
