#pragma once
#include "Ball.h"
#include <vector>

class Box {
public:
	float topWall, bottomWall, leftWall, rightWall;
	float r, g, b;

	std::vector<Ball*> balls;

	Box(float topWall = 1, float bottomWall = 1, float leftWall = 1, float rightWall = 1, float r = 1, float g = 1, float b = 1) {
		this->topWall = topWall;
		this->bottomWall = bottomWall;
		this->leftWall = leftWall;
		this->rightWall = rightWall;
		
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void Draw() {

		glColor3f(r, g, b);

		glBegin(GL_LINES);

			glVertex2f(leftWall, topWall);
			glVertex2f(rightWall, topWall);

			glVertex2f(rightWall, topWall);
			glVertex2f(rightWall, bottomWall);

			glVertex2f(rightWall, bottomWall);
			glVertex2f(leftWall, bottomWall);

			glVertex2f(leftWall, bottomWall);
			glVertex2f(leftWall, topWall);

		glEnd();

		for (int i = 0; i < balls.size(); i++) {
			balls[i]->Draw();
		}

	}

	void CalculateBalls() {

		for (int i = 0; i < balls.size(); i++) {
			balls[i]->WallCollision(topWall, bottomWall, leftWall, rightWall);
		}

		
		for (int i = 0; i < balls.size(); i++) {
			for (int j = i + 1; j < balls.size(); j++) {
				balls[i]->BallCollision(balls[j]);
			}
		}
		

		for (int i = 0; i < balls.size(); i++) {
			balls[i]->Calculate(balls, topWall, bottomWall, leftWall, rightWall);
		}

	}

	void AddBall(float radius = 0.1, bool infected = false, bool fixed = false, float r = 1, float g = 1, float b = 1) {
		Ball* ball = new Ball(balls, topWall, bottomWall, leftWall, rightWall, radius, infected, fixed, r, g, b);
		balls.push_back(ball);
	}

	void AddBalls(int balls, int fixed, float radius) {
		for (int i = 0; i < balls - 1; i++) {
			AddBall(radius, false, (i < fixed));
		}
		AddBall(radius, true);
	}

};