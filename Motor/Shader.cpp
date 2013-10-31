#include "Shader.h"
#include <cassert>
#include <memory>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

static void checkShaderError ( int shader, int flag, bool isProgram, const string& errorMessage );
static shared_ptr<string> loadShader ( const string& fileName );

Shader::Shader ( )
{
	log = new Log ( "ShaderLog" );
	m_program = glCreateProgram();

	if ( m_program == 0 ) 
	{
        log->Writeln ( "Error creating shader program\n" );
    }
}

Shader::~Shader()
{
	for(vector<int>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); ++it) 
	{
		glDetachShader(m_program,*it);
		glDeleteShader(*it);
	}
	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram ( m_program );
}

void Shader::addUniform ( const string& uniform )
{
	int location = glGetUniformLocation(m_program, uniform.c_str());

	assert ( location != GL_INVALID_VALUE );
}

void Shader::addVertexShaderFromFile(const string& text)
{
	addVertexShader(*loadShader(text));
}

void Shader::addGeometryShaderFromFile(const string& text)
{
	addGeometryShader(*loadShader(text));
}

void Shader::addFragmentShaderFromFile(const string& text)
{
	addFragmentShader(*loadShader(text));
}

void Shader::addVertexShader(const string& text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(const string& text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::addFragmentShader(const string& text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::addProgram ( const string& text, GLuint type )
{
	int shader = glCreateShader(type);

	if(shader == 0)
	{
		fprintf(stderr, "Error creating shader type %d\n", type);
		exit(1);
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();//strlen(text.c_str());

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) 
	{
        GLchar InfoLog[1024];

        glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", shader, InfoLog);

        exit(1);
    }

	glAttachShader(m_program, shader);
	m_Shaders.push_back(shader);
}

void Shader::CompileShader ( )
{
    glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Invalid shader program");
}

void Shader::UpdateUniforms(const Matrix4f& worldMatrix, const Matrix4f& projectedMatrix, Material& material)
{

}

void Shader::setUniformi(const string& name, int value)
{
	glUniform1i(m_uniforms.at(name), value);
}

void Shader::setUniformf(const string& name, float value)
{
	glUniform1f(m_uniforms.at(name), value);
}

static void checkShaderError(int shader, int flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
    GLchar error[1024] = { 0 };

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(!success)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		fprintf(stderr, "%s: '%s'\n", errorMessage, error);
	}
}

static shared_ptr<string> loadShader(const string& fileName)
{
	ifstream file;
	file.open(fileName);

	shared_ptr<string> output(new string());
	string line;
	Log* log = new Log ( "ShaderLog" );

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output->append(line + "\n");
		}
	} else {
		log->Writeln ( "Unable to load shader" );
	}
	delete log;
	return output;
};

BaseShader::BaseShader()
{
	log = new Log ( "ShaderLog" );
    m_ProgramID = NULL;
}

BaseShader::~BaseShader()
{
    //Free program if it exists
    FreeProgram();
}

void BaseShader::FreeProgram()
{
    //Delete program
    glDeleteProgram( m_ProgramID );
}

bool BaseShader::Bind()
{
	//Use shader
	glUseProgram( m_ProgramID );

	//Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
		log->Writeln ( "Error binding shader! %s\n" );
		PrintProgramLog ( m_ProgramID );
        return false;
    }

	return true;
}

GLuint BaseShader::LoadShaderFile ( string path, GLenum shaderType )
{
	GLuint shaderID = 0;
	string shaderString;
	ifstream sourceFile ( path.c_str ( ) );

	if ( sourceFile )
	{
		shaderString.assign ( ( istreambuf_iterator < char > ( sourceFile ) ), istreambuf_iterator < char > ( ) );
		
		shaderID = glCreateShader ( shaderType );
		
		const GLchar* shaderSource = shaderString.c_str ( );
		glShaderSource ( shaderID, 1, ( const GLchar** ) &shaderSource, NULL );

		glCompileShader ( shaderID );

		GLint shaderComplied = GL_FALSE;
		glGetShaderiv ( shaderID, GL_COMPILE_STATUS, &shaderComplied );

		if ( shaderComplied != GL_TRUE )
		{
			log->Writeln ( "Unable to Compile shader!!" );
			log->Writeln ( (char*)&shaderID );
			PrintShaderLog ( shaderID );
			glDeleteShader ( shaderID );
			shaderID = 0;
		}
	} else {
		log->Writeln ( "Unable to Open shader file" );
	}
	return shaderID;
}

void BaseShader::Unbind()
{
    //Use default program
	glUseProgram( NULL );
}

GLuint BaseShader::getProgramID()
{
	return m_ProgramID;
}

void BaseShader::PrintProgramLog( GLuint program )
{
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			log->Writeln ( infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	} else {
		log->Writeln ( "is not a program\n" );
	}
}

void BaseShader::PrintShaderLog( GLuint shader )
{
	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			log->Writeln ( infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	} else {
		log->Writeln ( "is not a shader\n" );
	}
}
