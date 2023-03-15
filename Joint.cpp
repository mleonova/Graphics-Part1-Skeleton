#include <iostream>
#include "Joint.h"
#include "Tokenizer.h"
#include "Window.h"

Joint::Joint() {
	boxmin = glm::vec3(-0.1f, -0.1f, -0.1f);
	boxmax = glm::vec3(0.1f, 0.1f, 0.1f);
	x.value = 0;
	y.value = 0;
	z.value = 0;
	x.min = -100000;
	x.max = 100000;
	y.min = -100000;
	y.max = 100000;
	z.min = -100000;
	z.max = 100000;
	offset = glm::vec3(0.0f, 0.0f, 0.0f);
	//cube = new Cube(boxmin, boxmax);
}

bool Joint::load(Tokenizer &token) {

	token.FindToken("{");

	while (1) {
		char temp[256];
		token.GetToken(temp);

		if (strcmp(temp, "offset") == 0) {

			offset.x = token.GetFloat();

			offset.y = token.GetFloat();

			offset.z = token.GetFloat();
		}
		else if (strcmp(temp, "boxmin") == 0) {
			boxmin.x = token.GetFloat();

			boxmin.y = token.GetFloat();

			boxmin.z = token.GetFloat();
		}
		else if (strcmp(temp, "boxmax") == 0) {
			boxmax.x = token.GetFloat();

			boxmax.y = token.GetFloat();

			boxmax.z = token.GetFloat();
		}
		else if (strcmp(temp, "rotxlimit") == 0) {
			x.min = token.GetFloat();

			x.max = token.GetFloat();
		}
		else if (strcmp(temp, "rotylimit") == 0) {
			y.min = token.GetFloat();

			y.max = token.GetFloat();
		}
		else if (strcmp(temp, "rotzlimit") == 0) {
			z.min = token.GetFloat();

			z.max = token.GetFloat();
		}
		else if (strcmp(temp, "pose") == 0) {
			x.value = token.GetFloat();

			if (x.value >= x.max) {
				x.value = x.max;
			}

			if (x.value <= x.min) {
				x.value = x.min;
			}

			y.value = token.GetFloat();
			if (y.value >= y.max) {
				y.value = y.max;
			}

			if (y.value <= y.min) {
				y.value = y.min;
			}
			
			z.value = token.GetFloat();
			if (z.value >= z.max) {
				z.value = z.max;
			}

			if (z.value <= z.min) {
				z.value = z.min;
			}	
		}
		else if (strcmp(temp, "balljoint") == 0) {
			Joint* jnt = new Joint;
			jnt->load(token);
			addChild(*jnt);
		}
		else if (strcmp(temp, "}") == 0) return true;
		else {
			token.SkipLine(); // Unrecognized token
		}
	}

	std::cout << "Returning" << std::endl;
}

void Joint::addChild(Joint &joint)
{
	children.push_back(&joint);
}

void Joint::update(glm::mat4 parent) {
	cube = new Cube(boxmin, boxmax);

	matrix_local = glm::translate(offset) * glm::rotate(z.value, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(y.value, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(x.value, glm::vec3(1.0f, 0.0f, 0.0f));

	matrix_world = parent * matrix_local;

	for (int i = 0; i < children.size(); i++) {
		children[i]->update(matrix_world);
	}
}

void Joint::draw(const glm::mat4& viewProjMtx, GLuint shader) {
	
	cube->draw(viewProjMtx * matrix_world, shader);
	
	for (int i = 0; i < children.size(); i++) {
		children[i]->draw(viewProjMtx, shader);
	}
}

