#ifndef MESH_H_
#define MESH_H_

#include "Vertex.h"

using namespace Vertexf;

class Mesh
{
private:
	void CalculateNormals ( Vertex3f* vetices, int vertSize, int* indices, int indexSize );
	
	unsigned int m_vbo;
	unsigned int m_ibo;
	int m_size;

public:
	Mesh ( );
	~Mesh ( );

	void addVertices ( Vertex3f* vertices, int vertSize, int* indices, int indexSize, bool calcnorm = true );
	void Draw ( );

};

#endif//MESH_H_