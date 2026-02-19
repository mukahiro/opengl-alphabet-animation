#include <stdio.h>
#include <GL/glut.h>
#define ROTATE_SPEED 0.5

int rightButton = 0;
int leftButton = 0;

GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat white[] = { 0.9, 0.9, 0.9, 1.0 };

/* 位置、サイズ、回転を指定して立方体を描写 */
void drawPart(double x, double y, double z, double sx, double sy, double sz, double angle = 0, double rx = 0, double ry = 0, double rz = 1) {
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(angle, rx, ry, rz);
	glScaled(sx, sy, sz);
	glutSolidCube(1.0);
	glPopMatrix();
}

/* 位置、サイズ、分割数を指定し球を描写 */
void drawSphere(double x, double y, double z, double radius, int slices, int stacks) {
	glPushMatrix();
	glTranslated(x, y, z);
	glutSolidSphere(radius, slices, stacks);
	glPopMatrix();
}

/* XZ平面上にメッシュの壁を描写 */
void drawWall(double z, double size, int divisions) {
	double step = size / divisions;
	double start = -size / 2.0;

	glPushMatrix();
	glTranslated(0, 0, z);
	glNormal3d(0.0, 0.0, 1.0);

	for (int i = 0; i < divisions; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= divisions; j++) {
			glVertex3d(start + i * step, start + j * step, 0);
			glVertex3d(start + (i + 1) * step, start + j * step, 0);
		}
		glEnd();
	}
	glPopMatrix();
}

/* 描画処理 */
void display() {
	static double leftAngle = 0;
	static double rightAngle = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// 視点の設定
	gluLookAt(0.0, -1.5, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// ライト位置・向き
	GLfloat light0_pos[] = { -1.0, 0.0, 3.0, 1.0 };
	GLfloat light0_dir[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_dir);

	GLfloat light1_pos[] = { 1.0, 0.0, 3.0, 1.0 };
	GLfloat light1_dir[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);

	GLfloat light2_pos[] = { 0.0, 2.0, 3.0, 1.0 };
	GLfloat light2_dir[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_dir);

	// 後ろの壁
	drawWall(-2.0, 10.0, 200);

	// 飾り付きM
	glPushMatrix();
	glTranslatef(-1.0, 0, 0);
	glRotatef(leftAngle, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	drawPart(-0.6, 0.0, 0.0, 0.3, 2.0, 0.5); // 左縦
	drawPart(0.6, 0.0, 0.0, 0.3, 2.0, 0.5); // 右縦
	drawPart(-0.25, 0.4, 0.0, 0.3, 1.2, 0.5, 30); // 左斜
	drawPart(0.25, 0.4, 0.0, 0.3, 1.2, 0.5, -30); // 右斜
	drawPart(-0.6, 1.0, 0.0, 0.5, 0.1, 0.55); // 左上
	drawPart(-0.6, -1.0, 0.0, 0.5, 0.1, 0.55); // 左下
	drawPart(0.6, 1.0, 0.0, 0.5, 0.1, 0.55); // 右上
	drawPart(0.6, -1.0, 0.0, 0.5, 0.1, 0.55); // 右下
	drawSphere(0.0, 0.0, 0.0, 0.32, 20, 20); // 中心点
	glPopMatrix();

	// 飾り付きK
	glPushMatrix();
	glTranslatef(1.0, 0, 0);
	glRotatef(rightAngle, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
	drawPart(-0.5, 0.0, 0.0, 0.3, 2.0, 0.5); // 縦
	drawPart(0.1, 0.45, 0.0, 0.3, 1.4, 0.5, -40); // 上斜
	drawPart(0.1, -0.45, 0.0, 0.3, 1.4, 0.5, 40); // 下斜
	drawPart(-0.6, 1.0, 0.0, 0.5, 0.1, 0.55); // 左上
	drawPart(-0.6, -1.0, 0.0, 0.5, 0.1, 0.55); // 左下
	drawPart(0.6, 1.0, 0.0, 0.5, 0.1, 0.55); // 右上
	drawPart(0.6, -1.0, 0.0, 0.5, 0.1, 0.55); // 右下
	drawSphere(-0.4, 0.0, 0.0, 0.35, 20, 20); // 分岐点
	glPopMatrix();

	glutSwapBuffers();

	if (leftButton) {
		if ((leftAngle += ROTATE_SPEED) >= 360) {
			leftAngle -= 360;
		}
	}
	if (rightButton) {
		if ((rightAngle -= ROTATE_SPEED) <= 0) {
			rightAngle += 360;
		}
	}
}

/* アイドル時の処理 */
void idle(void) {
	glutPostRedisplay();
}

/* リサイズ時の処理 */
void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (double)w / (double)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

/* マウス入力時の処理 */
void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_RIGHT_BUTTON:
		rightButton = (state == GLUT_DOWN);
		break;
	case GLUT_LEFT_BUTTON:
		leftButton = (state == GLUT_DOWN);
		break;
	default:
		break;
	}

	if (rightButton || leftButton) {
		glutIdleFunc(idle); // アニメーション開始
	}
	else {
		glutIdleFunc(0); // アニメーション停止
	}
}

/* キーボード入力時の処理 */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		exit(0);
	default:
		break;
	}
}

/* 初期化時の処理 */
void init(void) {
	glClearColor(0.05, 0.05, 0.05, 1.0); // 背景は暗く
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);

	// ライトの色・広がり
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 20.0);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 20.0);
}

/* メイン関数 */
int main(int argc, char* argv[]) {
	glutInitWindowSize(600, 450);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}