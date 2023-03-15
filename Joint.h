#pragma once
#include <vector>
#include "Cube.h"
#include "DOF.h"
#include "Tokenizer.h"
using namespace std;


class Joint {
private:
	glm::vec3 offset, boxmin, boxmax;
	DOF x, y, z;
	vector<Joint*> children;
	Cube* cube;
	glm::mat4 matrix_local, matrix_world;

public:
	Joint();
	bool load(Tokenizer &token);
	void addChild(Joint &joint);
	void update(glm::mat4 parent);
	void draw(const glm::mat4& viewProjMtx, GLuint shader);
};
