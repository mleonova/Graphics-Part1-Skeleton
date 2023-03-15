#pragma once
#include "Joint.h"
#include <map>
#include <iostream>
using namespace std;

class Skeleton {
private:
	Joint* root;
	map<string, Joint*> joints;

public:
	bool load(const char* file);
	void update();
	void draw(const glm::mat4& viewProjMtx, GLuint shader);
};