#include "ModuleProgram.h"
#include "GL/glew.h"


ModuleProgram::ModuleProgram()
{
}


ModuleProgram::~ModuleProgram()
{
}

bool  ModuleProgram::Init() {
	char* dataVS = nullptr;
	FILE* file = nullptr;

	fopen_s(&file, "Default.vs", "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		char* dataVS = (char*)malloc(size + 1);
		fread(dataVS, 1, size, file);
		dataVS[size] = 0;
		fclose(file);
	}

	char* dataFS = nullptr;
	file = nullptr;

	fopen_s(&file, "Default.fs", "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		char* dataFS = (char*)malloc(size + 1);
		fread(dataFS, 1, size, file);
		dataFS[size] = 0;
		fclose(file);
	}
	GLuint vsShader = glCreateShader(GL_VERTEX_SHADER);	GLuint fsShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vsShader,1,&dataVS,0);	glShaderSource(fsShader, 1, &dataFS, 0);
	glCompileShader(vsShader);
	glCompileShader(fsShader);

	GLint params;
	glGetShaderiv(vsShader, GL_COMPILE_STATUS, &params);
	//glGetShaderInfoLog(vsShader,;

	return true;
}

update_status ModuleProgram::Update() {

	return UPDATE_CONTINUE;
}

bool  ModuleProgram::CleanUp() {

	return true;
}