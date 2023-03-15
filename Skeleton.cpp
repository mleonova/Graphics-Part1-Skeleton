#include "Skeleton.h"
#include "Tokenizer.h"
#include <fstream>
#include <iostream>

bool Skeleton::load(const char* file) {

	Tokenizer token;
	bool openfile = token.Open(file);
	bool success = token.FindToken("balljoint");

	root = new Joint;
	root->load(token);

	// Finish
	token.Close();
	return true;
}

void Skeleton::update() {
	root->update(glm::mat4(1.0f));
}

void Skeleton::draw(const glm::mat4& viewProjMtx, GLuint shader) {
	root->draw(viewProjMtx, shader);
}