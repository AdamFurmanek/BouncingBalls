#pragma once

#include <vector>
#include <iostream>

#define PI 3.14159265358979323846

class Ball {
public:
	float positionX, positionY;
	float motionX, motionY;
	float radius;
	float mass;
	float r, g, b;
	bool fixed;
	bool infected;

	Ball(std::vector<Ball*> balls, float topWall, float bottomWall, float leftWall, float rightWall, float radius, bool infected, bool fixed, float r, float g, float b) {

		this->radius = radius;
		this->fixed = fixed;
		this->infected = infected;

		mass = (pow(radius, 3) * PI * 3 / 4);

		for (int i = 0; i < 1000; i++) { //Tysi¹c prób odnalezienia pustej przestrzeni.
			positionX = (float)(rand() % 1000) / 1000;
			positionY = (float)(rand() % 1000) / 1000;

			positionX = leftWall + radius + (rightWall - leftWall - 2 * radius) * positionX;
			positionY = bottomWall + radius + (topWall - bottomWall - 2 * radius) * positionY;

			bool again = false;

			for (int j = 0; j < balls.size(); j++) {
				float length1 = abs((this->positionX) - (balls[j]->positionX));
				float length2 = abs((this->positionY)-(balls[j]->positionY));
				if ((sqrtf(length1 * length1 + length2 * length2) <= this->radius + balls[j]->radius))
					again = true;
			}

			if (!again)
				break;
		}

		motionX = (float)(rand() % 1000) / 1000;
		motionY = (float)(rand() % 1000) / 1000;

		motionX = 2 * motionX - 1;
		motionY = 2 * motionY - 1;

		motionX /= 100;
		motionY /= 100;

		this->r = r;
		this->g = g;
		this->b = b;
	}

	void Draw() {

		glPushMatrix();
		glTranslatef(positionX, positionY, 0);

		//glColor3f(r, g, b);
		if(infected)
			glColor3f(1, 0, 0);
		else
			glColor3f(0, 1, 0);

		glutSolidSphere(radius, 50, 50);

		glPopMatrix();
	}

	void Calculate(std::vector<Ball*> balls, float topWall, float bottomWall, float leftWall, float rightWall) {
		if (fixed) {
			motionX = 0;
			motionY = 0;
		}

		positionX += motionX;
		positionY += motionY;
	}

	void WallCollision(float topWall, float bottomWall, float leftWall, float rightWall) {

		if (positionX - radius + motionX <= leftWall)
			motionX = abs(motionX);
		if(positionX + radius + motionX >= rightWall)
			motionX = -abs(motionX);
		if (positionY - radius + motionY <= bottomWall)
			motionY = abs(motionY);
		if (positionY + radius + motionY >= topWall)
			motionY = -abs(motionY);
	}

	void BallCollision(Ball* ball) {
		float m1 = this->mass;
		float m2 = ball->mass;
		float R = 1;
		float x1 = this->positionX;
		float y1 = this->positionY;
		float x2 = ball->positionX;
		float y2 = ball->positionY;
		float &vx1 = this->motionX;
		float &vy1 = this->motionY;
		float &vx2 = ball->motionX;
		float &vy2 = ball->motionY;

		float length1 = abs((x1 + vx1) - (x2 + vx2));
		float length2 = abs((y1 + vy1) - (y2 + vy2));
		if (!(sqrtf(length1 * length1 + length2 * length2) <= this->radius + ball->radius))
			return;

		float  m21, dvx2, a, x21, y21, vx21, vy21, fy21, sign, vx_cm, vy_cm;

		m21 = m2 / m1;
		x21 = x2 - x1;
		y21 = y2 - y1;
		vx21 = vx2 - vx1;
		vy21 = vy2 - vy1;

		vx_cm = (m1 * vx1 + m2 * vx2) / (m1 + m2);
		vy_cm = (m1 * vy1 + m2 * vy2) / (m1 + m2);

		a = y21 / x21;
		dvx2 = -2 * (vx21 + a * vy21) / ((1 + a * a) * (1 + m21));

		if (!fixed) {

		vx1 = vx1 - m21 * dvx2;
		vy1 = vy1 - a * m21 * dvx2;
		vx1 = (vx1 - vx_cm) * R + vx_cm;
		vy1 = (vy1 - vy_cm) * R + vy_cm;

		vx2 = vx2 + dvx2;
		vy2 = vy2 + a * dvx2;
		vx2 = (vx2 - vx_cm) * R + vx_cm;
		vy2 = (vy2 - vy_cm) * R + vy_cm;

		}
		else {
			float vx1N = vx1 - m21 * dvx2;
			float vy1N = vy1 - a * m21 * dvx2;
			vx1N = (vx1N - vx_cm) * R + vx_cm;
			vy1N = (vy1N - vy_cm) * R + vy_cm;

			vx2 = vx2 + dvx2;
			vy2 = vy2 + a * dvx2;
			vx2 = (vx2 - vx_cm) * R + vx_cm - vx1N;
			vy2 = (vy2 - vy_cm) * R + vy_cm - vy1N;
		}

		if (this->infected)
			ball->infected = true;
		if (ball->infected)
			this->infected = true;

		return;

	}

};