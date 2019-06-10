///////////////////////////////////////////////////////////////////////////////
//	�W�����s���O�Q�[��

#include "el.h"

#define MAIN_SCREEN 1

#define ACCEL_X 0.6			// �����x
#define MAX_SPEED 8			// �ō����x
#define JUMP_POWER 20		// �W�����v��

void MainScreen(void);

DDOBJ jiki;		// ���@�r�b�g�}�b�v

///////////////////////////////////////////////////////////////////////////////
//	���C���֐�

int elMain("�W�����s���O");
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
	jiki = elDraw::LoadObject("chr.bmp");
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
	static int jx = 160, jy = 280;		// ���@���W
	static double vx = 0.0, vy;			// ���@���x
	static bool jumpFlag = false;		// �W�����v���Ȃ� true
	static int kl = FREE_KEY;			// ���L�[�̏��
	static int kr = FREE_KEY;			// �E�L�[�̏��
	static int ks = FREE_KEY;			// �X�y�[�X�L�[�̏��
	static int mw[20] = {1000};			// �}�b�v�̕�
	static int mnum = 1;				// �}�b�v�̐�
	static int mkt = 1;					// �}�b�v�擪�̎��(0:�� 1:�n��)
	static bool overFlag = false;		// �Q�[���I�[�o�[�Ȃ� true
	static int score = 0;				// �X�R�A
	int i;

	elDraw::Clear();

	// �L�[����
	elSystem::GetKey(VK_LEFT, &kl);
	elSystem::GetKey(VK_RIGHT, &kr);
	elSystem::GetKey(VK_SPACE, &ks);
	// ���E�ړ�
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
	// �W�����v
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

	// �}�b�v�`��
	int mk = mkt;		// ���݂̃}�b�v�̎��
	int mx = 0;			// ���݂̃}�b�v�̍��[���W
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
	// ���@�`��
	int y = 0;
	if (overFlag) y = 32;
	elDraw::Layer(jx, jy + y, jiki, 0, 0, 64, 64);

	// �X�R�A�\��
	SHOW2(0, 0, "SCORE:%d", score++);

	elDraw::Refresh();

	if (overFlag) {
		elSystem::Message("GAME OVER!");
		elDraw::Exit();
	}
}
