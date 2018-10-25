#ifndef _CAMERA_
#define _CAMERA_

#include "Module.h"
#include "MathGeoLib.h"

class ModuleCamera :
	public Module
{
public:
	ModuleCamera();
	virtual ~ModuleCamera();

	bool Init();
	void PintaGrid();

	update_status Update();

	Frustum frustum;

	float camSpeed;

	math::float3 cameraPos;

	math::float4x4 LookAt(math::float3 & target, math::float3 & eye, math::float3 & up);
	math::float4x4 CalcProjection();

	math::float4x4 viewMatrix;
	math::float4x4 projectionMatrix;
};

#endif