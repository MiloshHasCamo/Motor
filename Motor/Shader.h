#ifndef SHADER_H_
#define SHADER_H_

#ifndef _WIN32
#include <Windows.h>
#endif//_WIN32

#include "GLEW.h"

#include <unordered_map>
#include "FileUtillities.h"
#include "Math.h"
#include "Matrial.h"

#pragma comment ( lib, "glew32.lib" )

class BaseShader
{
protected:
	Log* log;

public:
	BaseShader();

    virtual ~BaseShader();

	virtual bool LoadProgram() = 0;

	virtual void FreeProgram();

	bool Bind();

	void Unbind();

	GLuint getProgramID();

	GLuint LoadShaderFile ( string path, GLenum shaderType );

protected:
	void PrintProgramLog ( GLuint program );

	void PrintShaderLog ( GLuint shader );

	GLuint m_ProgramID;
};

class Shader
{
public:
	 Shader ( );
	~Shader ( );

	void Bind ( );
	void addUniform ( const std::string& uniform );
	void addVertexShaderFromFile   ( const std::string& text );
	void addGeometryShaderFromFile ( const std::string& text );
	void addFragmentShaderFromFile ( const std::string& text );
	void addVertexShader   ( const std::string& text );
	void addGeometryShader ( const std::string& text );
	void addFragmentShader ( const std::string& text );
	void CompileShader ( );

	virtual void UpdateUniforms ( const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material );

	void setUniformi ( const std::string& name, int value );
	void setUniformf ( const std::string& name, float value );

private:
	Log* log;
	GLuint m_program;
	std::unordered_map<std::string, int> m_uniforms;
	std::vector<int> m_Shaders;

	void addProgram ( const std::string& text, GLenum type );
};

#endif//SHADER_H_