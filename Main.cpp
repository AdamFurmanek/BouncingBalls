#include <iostream>
#include <GL/glut.h>
#include "Box.h"

Box* box1;
Box* box2;
Box* box3;
Box* box4;
Box* box5;
Box* box6;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0, 0.5, 0);

	box1->Draw();
	glTranslatef(0.5, 0, 0);
	box2->Draw();
	glTranslatef(0.5, 0, 0);
	box3->Draw();

	glTranslatef(-1.0, -0.5, 0);

	box4->Draw();
	glTranslatef(0.5, 0, 0);
	box5->Draw();
	glTranslatef(0.5, 0, 0);
	box6->Draw();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (float)w/1500 * 2000, (float)h/1000 * 2000);
}

void Timer(int parameter)
{
	box1->CalculateBalls();
	box2->CalculateBalls();
	box3->CalculateBalls();
	box4->CalculateBalls();
	box5->CalculateBalls();
	box6->CalculateBalls();

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
	glutInitWindowSize(1500, 1000);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	srand(time(0));

	box1 = new Box(-0.5, -1, -1, -0.5);
	box1->AddBalls(100, 5, 0.005);

	box2 = new Box(-0.5, -1, -1, -0.5);
	box2->AddBalls(100, 20, 0.005);

	box3 = new Box(-0.5, -1, -1, -0.5);
	box3->AddBalls(100, 40, 0.005);

	box4 = new Box(-0.5, -1, -1, -0.5);
	box4->AddBalls(100, 60, 0.005);

	box5 = new Box(-0.5, -1, -1, -0.5);
	box5->AddBalls(100, 80, 0.005);

	box6 = new Box(-0.5, -1, -1, -0.5);
	box6->AddBalls(100, 95, 0.005);

	glutTimerFunc(15, Timer, 1);

	glutMainLoop();
}
