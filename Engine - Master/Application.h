#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
<<<<<<< HEAD
class ModuleProgram;
class ModuleImgui;
class ModuleCamera;
=======
>>>>>>> parent of 3ce6007... Shaders: compilen, falta el attach

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
    ModuleRenderExercise* exercise = nullptr;
<<<<<<< HEAD
	ModuleProgram* program = nullptr;
	ModuleImgui* imgui = nullptr;
	ModuleCamera* camera = nullptr;
=======
>>>>>>> parent of 3ce6007... Shaders: compilen, falta el attach

private:

	std::list<Module*> modules;

};

extern Application* App;
