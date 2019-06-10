#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "ImageData.h"
#include "ImageIO.h"

int g_WindowWidth = 512;    /* ウィンドウの横幅 */
int g_WindowHeight = 512;   /* ウィンドウの縦幅 */

#define IMAGE_FILE "lenna128x128.ppm"

ImageData g_Image;
int g_ImagePosX = 256;
int g_ImagePosY = 0;
int g_CursorDelta = 10;

enum MouseOperation
{
	NO_OPERATION,
	DRAGGING_IMAGE
};

int g_DraggingImage = NO_OPERATION;


/* 初期化処理 */
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);   /* ウィンドウを消去するときの色を設定 */

	InitImageData(&g_Image);

	if ( LoadPPMImage(IMAGE_FILE, &g_Image) )
	{
		FlipImageData(&g_Image);
	}
}

/* 表示処理のためのコールバック関数 */
void display(void)
{
	/* ウィンドウを消去 … glClearColor で指定した色で塗りつぶし */
	glClear(GL_COLOR_BUFFER_BIT);

	if ( IsImageDataAllocated(&g_Image))
	{
		DrawImageData(&g_Image, g_ImagePosX, g_ImagePosY);
	}

	glutSwapBuffers();
}

void idle(void)
{
	display();
}

/* キーボード入力のためのコールバック関数 */
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		g_ImagePosY += g_CursorDelta;
		if (g_WindowHeight - g_Image.height <= g_ImagePosY )
			g_ImagePosY = g_WindowHeight - g_Image.height;
		break;
	case 'x':
		g_ImagePosY -= g_CursorDelta;
		if (g_ImagePosY < 0)
			g_ImagePosY = 0;
		break;
	case 'd':
		g_ImagePosX += g_CursorDelta;
		if (g_WindowWidth - g_Image.width <= g_ImagePosX)
			g_ImagePosX = g_WindowWidth - g_Image.width;
		break;
	case 'a':
		g_ImagePosX -= g_CursorDelta;
		if (g_ImagePosX < 0)
			g_ImagePosX = 0;
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

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		g_ImagePosY += g_CursorDelta;
		if (g_WindowHeight - g_Image.height <= g_ImagePosY )
			g_ImagePosY = g_WindowHeight - g_Image.height;
		break;
	case GLUT_KEY_DOWN:
		g_ImagePosY -= g_CursorDelta;
		if (g_ImagePosY < 0)
			g_ImagePosY = 0;
		break;
	case GLUT_KEY_RIGHT:
		g_ImagePosX += g_CursorDelta;
		if (g_WindowWidth - g_Image.width <= g_ImagePosX)
			g_ImagePosX = g_WindowWidth - g_Image.width;
		break;
	case GLUT_KEY_LEFT:
		g_ImagePosX -= g_CursorDelta;
		if (g_ImagePosX < 0)
			g_ImagePosX = 0;
		break;
	default:
		break;
	}

	glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}

/* マウス入力のためのコールバック関数 */
void mouse(int button, int state, int x, int _y)
{
	int y = g_WindowHeight - _y;

	if (state == GLUT_DOWN)
	{
		g_DraggingImage = DRAGGING_IMAGE;

		printf("mouse: (%d,%d) clicked\n", x, y);

		g_ImagePosX = x;
		g_ImagePosY = y;

		if (g_ImagePosX < 0)
			g_ImagePosX = 0;
		else if (g_WindowWidth - g_Image.width <= g_ImagePosX)
			g_ImagePosX = g_WindowWidth - g_Image.width;

		if (g_ImagePosY < 0)
			g_ImagePosY = 0;
		else if (g_WindowHeight - g_Image.height <= g_ImagePosY )
			g_ImagePosY = g_WindowHeight - g_Image.height;
	}
	else if (state == GLUT_UP)
	{
		g_DraggingImage = NO_OPERATION;
	}

	glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}

void motion(int x, int _y)
{
	if (g_DraggingImage == DRAGGING_IMAGE)
	{
		int y = g_WindowHeight - _y;

		printf("motion: (%d,%d) clicked\n", x, y);

		g_ImagePosX = x;
		g_ImagePosY = y;

		if (g_ImagePosX < 0)
			g_ImagePosX = 0;
		else if (g_WindowWidth - g_Image.width <= g_ImagePosX)
			g_ImagePosX = g_WindowWidth - g_Image.width;

		if (g_ImagePosY < 0)
			g_ImagePosY = 0;
		else if (g_WindowHeight - g_Image.height <= g_ImagePosY )
			g_ImagePosY = g_WindowHeight - g_Image.height;
	}

	glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}

/* ウィンドウサイズが変更されたときのためのコールバック関数 */
void reshape(int w, int h)
{
	if (h < 1) return;

	g_WindowWidth = w;
	g_WindowHeight = h;

	glViewport(0, 0, w, h); /* ウィンドウの描画範囲を指定 */

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(g_WindowWidth, g_WindowHeight);
	glutCreateWindow("Animation");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();

	return 0;
}
