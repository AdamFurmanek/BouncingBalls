#include <iostream>
#include <GL/glut.h>
#include "Box.h"

Box* box;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	box->Draw();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}

void Timer(int parameter)
{
	box->CalculateBalls();
	glutTimerFunc(15, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	srand(time(0));

	box = new Box(0.95, -0.95, -0.95, 0.95);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);
	box->AddBall(0.02);

	glutTimerFunc(15, Timer, 1);

	glutMainLoop();
}