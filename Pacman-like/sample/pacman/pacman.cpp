///////////////////////////////////////////////////////////////////////////////
//	�p�b�N�}���I�ȃQ�[��

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dsound.lib")

#include "el.h"

#define MAIN_SCREEN 1

void MainScreen(void);

DDOBJ jiki, chip, teki;
DSOBJ eat;
int esaNum = 0;

int map[15][20] = {
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

///////////////////////////////////////////////////////////////////////////////
//	���C���֐�

int elMain("�p�b�N�}���I�ȃQ�[��");
{
	elWindow(640, 480, FALSE);
	elLoop()
	{
		elSetScreen(MAIN_SCREEN, MainScreen());
	}
	elExitMain();
}

///////////////////////////////////////////////////////////////////////////////
//	�E�C���h�E�����֐�

void elCreate(void)
{
	elDraw::Screen(640, 480);
	// �G�T�̐��𐔂���
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 20; x++) {
			if (map[y][x] == 2) esaNum++;
		}
	}
	// �摜�E�����ǂݍ���
	jiki = elDraw::LoadObject("jiki.bmp");
	chip = elDraw::LoadObject("chip.bmp");
	teki = elDraw::LoadObject("teki.bmp");
	eat = elSound::LoadObject("eat.wav");
	elMusic::Play("bgm.mid");
	elCallScreen(MAIN_SCREEN);
}

///////////////////////////////////////////////////////////////////////////////
//	�L�[�{�[�h�֐�

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
//	�C�x���g�֐�

long elEvent(void)
{
	elExitEvent();
}

///////////////////////////////////////////////////////////////////////////////
//	���C�����

void MainScreen(void)
{
	static int mx = 1, my = 1;
	static int md = 0;
	static int ma = 0;
	static int ex = 18, ey = 13;
	static int score = 0;
	elDraw::Clear();
	// ���@�ړ�
	int kx = mx, ky = my;
	switch (PushKey) {
		case VK_LEFT: kx--; md = 2; break;
		case VK_RIGHT: kx++; md = 0; break;
		case VK_UP: ky--; md = 3; break;
		case VK_DOWN: ky++; md = 1; break;
	}
	if (map[ky][kx] != 1) {
		mx = kx; my = ky;
	}
	if (map[my][mx] == 2) {
		map[my][mx] = 0;
		score += 10;
		esaNum--;
		elSound::Play(eat);
	}
	ma = 1 - ma;
	// �G�ړ�
	kx = ex; ky = ey;
	if (rand() % 3 == 0) {
		if (kx > mx) kx--;
		if (kx < mx) kx++;
		if (ky > my) ky--;
		if (ky < my) ky++;
	} else {
		kx += rand() % 3 - 1;
		ky += rand() % 3 - 1;
	}
	if (map[ky][kx] != 1) {
		ex = kx; ey = ky;
	}
	// �}�b�v�`��
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 20; x++) {
			elDraw::Layer(x * 32, y * 32, chip, map[y][x] * 32, 0, map[y][x] * 32 + 32, 32);
		}
	}
	// ���@�`��
	elDraw::Layer(mx * 32, my * 32, jiki, md * 32, ma * 32, md * 32 + 32, ma * 32 + 32);
	// �G�`��
	elDraw::Layer(ex * 32, ey * 32, teki, 0, 0, 32, 32);
	SHOW2(0, 0, "SCORE:%d", score);
	elDraw::Refresh();
	Sleep(80);
	if (esaNum <= 0) {
		MESG("�Q�[���N���A�I");
		elDraw::Exit();
	}
	if (mx == ex && my == ey) {
		MESG("�Q�[���I�[�o�[");
		elDraw::Exit();
	}
}
