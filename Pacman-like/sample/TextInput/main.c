#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

int g_WindowWidth = 800;    /* ウィンドウの横幅 */
int g_WindowHeight = 300;   /* ウィンドウの縦幅 */

int g_MessageStartX = 20;
int g_MessageStartY = 260;

const int g_MaxLineCount = 32;

int g_KeyboardInputCount = 0;

#define BUFSIZE 8192
char g_MessageBuffer[BUFSIZE];

/* 初期化処理 */
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);   /* ウィンドウを消去するときの色を設定 */
}

void DisplayString(const char *str, int xi, int yi)
{
	int i, yStart = yi;

	glRasterPos2i(xi,yStart);

	for (i=0; str[i] != '\0'; i++)
	{
		if (str[i] == '\r')
		{
			yStart -= 24;
			glRasterPos2i(xi,yStart);
		}
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
		}
	}

	glRasterPos2i(0, 0);
}

/* 表示処理のためのコールバック関数 */
void display(void)
{
	/* ウィンドウを消去 … glClearColor で指定した色で塗りつぶし */
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(0,0,0);
	DisplayString("Input: ", g_MessageStartX, g_MessageStartY+24);
	DisplayString(g_MessageBuffer, g_MessageStartX, g_MessageStartY);

	glutSwapBuffers();
}

void idle(void)
{
	display();
}


/* キーボード入力のためのコールバック関数 */
void keyboard(unsigned char key, int x, int y)
{
	if (g_KeyboardInputCount > 0 && key == 8) /* key == 8 ... Backspace */
	{
		g_KeyboardInputCount--;
		g_MessageBuffer[g_KeyboardInputCount] = '\0';
	}
	else 
	{
/*
		if (key == '\r')
			g_MessageBuffer[g_KeyboardInputCount] = '\n';
		else
			g_MessageBuffer[g_KeyboardInputCount++] = key;

		if (g_KeyboardInputCount == MAX_LINE_COUNT)
			g_MessageBuffer[g_KeyboardInputCount] = '\n';
*/
		if (g_KeyboardInputCount > 0 && g_KeyboardInputCount % g_MaxLineCount == 0)
			g_MessageBuffer[g_KeyboardInputCount++] = '\r';

		g_MessageBuffer[g_KeyboardInputCount++] = key;

		if (g_KeyboardInputCount > BUFSIZE-1)
			g_KeyboardInputCount = BUFSIZE-1;

		g_MessageBuffer[g_KeyboardInputCount] = '\0';
	}

	glutPostRedisplay();    /* ウィンドウ描画関数を呼ぶ */
}

/* マウス入力のためのコールバック関数 */
void mouse(int button, int state, int x, int _y)
{
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
	glutCreateWindow("Text Message");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();

	return 0;
}

