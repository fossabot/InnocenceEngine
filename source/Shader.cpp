#include "Shader.h"
#include "GameObject.h"

std::vector<std::string> Shader::split(const std::string& data, char marker)
{
	std::vector<std::string> elems;

	const char* cstr = data.c_str();
	unsigned int strLength = (unsigned int)data.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == marker)
				break;
			end++;
		}

		elems.push_back(data.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

Shader::Shader()
{
	init();
}


Shader::~Shader()
{
}

void Shader::init()
{
	_name = "defalutShader";
	_program = glCreateProgram();
	if (_program == 0)
	{
		std::cout << "Shader creation failed: memory location invaild" << std::endl;
	}
}

void Shader::bind()
{
	glUseProgram(_program);
}

void Shader::addUniform(std::string uniform)
{
	int uniformLocation = glGetUniformLocation(_program, uniform.data());

	if (uniformLocation == 0xFFFFFFFF) {
		std::cout << "Error : Uniform lost: " + uniform << std::endl;
	}

	_uniforms.insert(std::pair<std::string, int>(uniform, uniformLocation));
}


void Shader::addVertexShader(std::string text)
{
	addProgram(loadShader(text), GL_VERTEX_SHADER);
	std::cout << "Vertex shader " + text + " has been loaded." << std::endl;
}

void Shader::addGeometryShader(std::string text)
{
	addProgram(loadShader(text), GL_GEOMETRY_SHADER);
	std::cout << "Geometry shader " + text + " has been loaded." << std::endl;
}

void Shader::addFragmentShader(std::string text)
{
	addProgram(loadShader(text), GL_FRAGMENT_SHADER);
	std::cout << "Fragment shader " + text + " has been loaded." << std::endl;
}

void Shader::setAttribLocation(std::string attributeName, int location)
{
	glBindAttribLocation(_program, location, attributeName.data());
}

void Shader::addProgram(std::string text, int type)
{
	
	int shader = glCreateShader(type);
	if (shader == 0) {
		std::cout << "Shader creation failed: memory location invaild when adding shader" << std::endl;
	}

	char const * sourcePointer = text.c_str();
	//std::cout << sourcePointer << std::endl;
	glShaderSource(shader, 1, &sourcePointer, NULL);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	glGetShaderiv(_program, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(_program, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0) {
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(_program, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}

	glAttachShader(_program, shader);
	glLinkProgram(_program);

	//glValidateProgram(_program);

	glDetachShader(_program, shader);
	glDeleteShader(shader);
}

void Shader::setUniformi(std::string uniformName, int value)
{
	glUniform1i(_uniforms.find(uniformName)->second, value);
}

void Shader::setUniformf(std::string uniformName, float value)
{
	glUniform1f(_uniforms.find(uniformName)->second, value);
}

void Shader::setUniform(std::string uniformName, const Vec3f& value)
{
	glUniform3f(_uniforms.find(uniformName)->second, value.getX(), value.getY(), value.getZ());
}

void Shader::setUniform(std::string uniformName, const Mat4f& value)
{
	std::vector<float> buffer(4 * 4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			buffer.push_back(value.getElem(i, j));
		}
	}
	std::reverse(buffer.begin(), buffer.end());
	glUniformMatrix4fv(_uniforms.find(uniformName)->second, 1, true, buffer.data());
}

void Shader::updateUniforms(GameObject * gameObject, Material * material)
{
}

const std::string & Shader::getName()
{
	return _name;
}

void Shader::setName(const std::string & name)
{
	_name = name;
}

std::string Shader::loadShader(const std::string & fileName)
{
	std::ifstream file;
	file.open(("C:/Users/zhanghang.SNAIL/Documents/Visual Studio 2015/Projects/InnocenceEngine-C-/res/shaders/" + fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			if (line.find("#include") == std::string::npos)
			{
				output.append(line + "\n");
			}
			else
			{
				std::string includeFileName = Shader::split(line, ' ')[1];
				includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

				std::string toAppend = loadShader(includeFileName);
				output.append(toAppend + "\n");
			}
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

ForwardAmbientShaderWrapper::ForwardAmbientShaderWrapper()
{
	init();
	setName("ForwardAmbientShaderWrapper");
	addVertexShader("forward-ambient-vertex.sf");
	addFragmentShader("forward-ambient-fragment.sf");

	setAttribLocation("position", 0);
	setAttribLocation("texCoord", 1);

	addUniform("MVP");
	addUniform("ambientIntensity");
}


ForwardAmbientShaderWrapper::~ForwardAmbientShaderWrapper()
{
}


void ForwardAmbientShaderWrapper::updateUniforms(GameObject* gameObject, Material * material)
{
	//fprintf(stdout, "child updateUniforms.\n");
	Mat4f worldMatrix = gameObject->caclTransformation();
	//Mat4f projectedMatrix = gameObject->getRenderingEngine()->getMainCamera()->getViewProjection() * (worldMatrix);
	//material->getTexture("diffuse").bind();
	//setUniform("MVP", projectedMatrix);
	setUniform("ambientIntensity", gameObject->getRenderingEngine()->getAmbientLight());
}

BasicShaderWrapper::BasicShaderWrapper()
{
	init();
	setName("BasicShaderWrapper");
	addVertexShader("basicVertex.sf");
	addFragmentShader("basicFragment.sf");

	//setAttribLocation("position", 0);
}

BasicShaderWrapper::~BasicShaderWrapper()
{
}

void BasicShaderWrapper::updateUniforms(GameObject * gameObject, Material * material)
{
	Mat4f worldMatrix = gameObject->caclTransformation();
	//Mat4f projectedMatrix = gameObject->getRenderingEngine()->getMainCamera()->getViewProjection() * (worldMatrix);
	//setUniform("transform", projectedMatrix);
	//setUniform("color", gameObject->getRenderingEngine()->getAmbientLight());
}
