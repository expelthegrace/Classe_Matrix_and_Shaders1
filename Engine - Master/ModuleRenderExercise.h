#ifndef __ModuleRenderExercise_h__
#define __ModuleRenderExercise_h__

#include "Module.h"
#include "MathGeoLib.h"

class ModuleRenderExercise : public Module
{
public:
    ModuleRenderExercise();
    ~ModuleRenderExercise();

	bool            Init    ();
	update_status   Update  ();
	bool            CleanUp ();

	void UpdateMatrix();

	math::float4x4 projectionMatrix;
	math::float4x4 viewMatrix;
private:
    unsigned vbo        = 0;

};

#endif /* __ModuleRenderExercise_h__ */
