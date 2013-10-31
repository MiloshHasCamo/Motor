#include "Mesh.h"
#include "GLEW.h"
#include "Vector.h"

using namespace Vectorf;

Mesh::Mesh ( )
{
	glGenBuffers ( 1, &m_vbo );
	glGenBuffers ( 1, &m_ibo );
	m_size = 0;
}

Mesh::~Mesh ( )
{
	glDeleteBuffers ( 1, &m_vbo );
	glDeleteBuffers ( 1, &m_ibo );
}

void Mesh::addVertices ( Vertex3f* vertices, int vertSize, int* indices, int indexSize, bool calcnorm )
{
	m_size = indexSize;

	if ( calcnorm )
	{
		this->CalculateNormals ( vertices, vertSize, indices, indexSize );
	}

	glBindBuffer ( GL_ARRAY_BUFFER, m_vbo );
	glBufferData ( GL_ARRAY_BUFFER, vertSize * sizeof ( Vertex3f ), vertices, GL_STATIC_DRAW );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof ( int ), indices, GL_STATIC_DRAW );
}

void Mesh::Draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3f), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3f), (GLvoid*)sizeof(Vector3f));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3f), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::CalculateNormals ( Vertex3f* vertices, int vertSize, int* indices, int indexSize )
{
	for(int i = 0; i < indexSize; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		Vector3f v1 = vertices[i1].getPosition ( ) - vertices[i0].getPosition ( );
		Vector3f v2 = vertices[i2].getPosition ( ) - vertices[i0].getPosition ( );

		Vector3f& normal = *v1.Cross ( v2 )->Normalize ( );

		vertices[i0].setNormal ( vertices[i0].getNormal ( ) + normal );
		vertices[i1].setNormal ( vertices[i1].getNormal ( ) + normal );
		vertices[i2].setNormal ( vertices[i2].getNormal ( ) + normal );
	}

	for(int i = 0; i < vertSize; i++)
		vertices[i].getNormal ( ).Normalize();
}