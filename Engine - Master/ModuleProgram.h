#pragma once
#include "Module.h"
class ModuleProgram :
	public Module
{
public:
	ModuleProgram();
	virtual ~ModuleProgram();

	bool            Init();
	update_status   Update();
	bool            CleanUp();

};

