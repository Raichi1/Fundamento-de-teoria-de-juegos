#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>

Sprite::Sprite() {
	vboID = 0;
}

void Sprite::init(float x, float y, int width, int height, string texturePath) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}
	/*
	float vertexData[12];
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;

	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width;
	vertexData[9] = y;

	vertexData[10] = x + width;
	vertexData[11] = y + height;*/
	texture = ResourceManager::getTexture(texturePath);
	Vertex vertexData[6];
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(0.0f, 0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);

	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x, y + height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);
	for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(255, 255, 0, 100);
	}
	vertexData[2].setColor(255, 0, 255, 255);
	vertexData[3].setColor(0, 255, 255, 255);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);//Carga la información
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);//Procesa la información
	glBindBuffer(GL_ARRAY_BUFFER, 0);//Libera la información almacenada
}
void Sprite::draw() {
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);//
	//
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);//Recibe 6 valores (inicio,tamaño(x,y), data type, normalizar)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));


	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES,0,6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//Limpia en memoria
}

Sprite::~Sprite() {
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}