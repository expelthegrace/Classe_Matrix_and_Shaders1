#include "Application.h"

#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"

#include "GL/glew.h"
#include "SDL.h"
#include "ModuleCamera.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

void ModuleRenderExercise::UpdateMatrix() {

}

bool ModuleRenderExercise::Init()
{
	math::float4 point1 = math::float4(-1, -1, 0, 1);
	math::float4 point2 = math::float4(1, -1, 0, 1);
	math::float4 point3 = math::float4(0, 1, 0, 1);
/*
	math::float4 point1 = App->camera->projectionMatrix * App->camera->viewMatrix * math::float4(-1, -1, 0, 1);
	math::float4 point2 = App->camera->projectionMatrix *  App->camera->viewMatrix * math::float4(1, -1, 0, 1);
	math::float4 point3 = App->camera->projectionMatrix *  App->camera->viewMatrix * math::float4(0, 1, 0, 1);

	
	float vertex_buffer_data[] = {
		point1.x / point1.w, point1.y / point1.w, point1.z / point1.w,
		point2.x / point2.w, point2.y / point2.w, point2.z / point2.w,
		point3.x / point3.w, point3.y / point3.w, point3.z / point3.w,
	};
	*/
	// ^aixo no fa falta si els shaders em multipliquen per les matrius (tot i que lo del w no entenc si es necessari)


	float vertex_buffer_data[] = {
		point1.x , point1.y , point1.z ,
		point2.x, point2.y, point2.z,
		point3.x , point3.y , point3.z,
	};
	// falta multiplicar cada vertex ^ per la project view matrix


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;


}

update_status ModuleRenderExercise::Update()
{
	//eliminar un cop tingui shaders
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((GLfloat*) &App->camera->projectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat*) &App->camera->viewMatrix);
	//

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
            0,                  // attribute 0
            3,                  // number of componentes (3 floats)
            GL_FLOAT,           // data type
            GL_FALSE,           // should be normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );

    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    if(vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
    }

	return true;
}

