#include "camera.h"

#include "application.h"
#include "main/includes.h"
#include <iostream>

Camera::Camera()
{
	view_matrix.SetIdentity();
	SetOrthographic(-1,1,1,-1,-1,1);
}

Vector3 Camera::GetLocalVector(const Vector3& v)
{
	Matrix44 iV = view_matrix;
	if (iV.Inverse() == false)
		std::cout << "Matrix Inverse error" << std::endl;
	Vector3 result = iV.RotateVector(v);
	return result;
}

Vector3 Camera::ProjectVector(Vector3 pos, bool& negZ)
{
	Vector4 pos4 = Vector4(pos.x, pos.y, pos.z, 1.0);
	Vector4 result = viewprojection_matrix * pos4;
	negZ = result.z < 0;
	if (type == ORTHOGRAPHIC)
		return result.GetVector3();
	else
		return result.GetVector3() / result.w;
}

void Camera::Rotate(float angle, const Vector3& axis)
{
	Matrix44 R;
	R.SetRotation(angle, axis);
	Vector3 new_front = R * (center - eye);
	center = eye + new_front;
	UpdateViewMatrix();
}

void Camera::Move(Vector3 delta)
{
	Vector3 localDelta = GetLocalVector(delta);
	eye = eye - localDelta;
	center = center - localDelta;
	UpdateViewMatrix();
}

void Camera::SetOrthographic(float left, float right, float top, float bottom, float near_plane, float far_plane)
{
	type = ORTHOGRAPHIC;

	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->near_plane = near_plane;
	this->far_plane = far_plane;

	UpdateProjectionMatrix();
}

void Camera::SetPerspective(float fov, float aspect, float near_plane, float far_plane)
{
	type = PERSPECTIVE;

	this->fov = fov;
	this->aspect = aspect;
	this->near_plane = near_plane;
	this->far_plane = far_plane;

	UpdateProjectionMatrix();
}

void Camera::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// Reset Matrix (Identity)
	view_matrix.SetIdentity();

	// Comment this line to create your own projection matrix!
	//SetExampleViewMatrix();
	
	Vector3 Forward = center-eye;

	Forward.Normalize();
	Vector3 Right = up.Cross(Forward);
	Right.Normalize();

	Vector3 UP = Forward.Cross(Right);

	view_matrix.m[0] = Right.x;
	view_matrix.m[1] = Right.y;
	view_matrix.m[2] = Right.z;
	view_matrix.m[3] = -(Right.x*eye.x + Right.y*eye.y + Right.z*eye.z);

	view_matrix.m[4] = UP.x;
	view_matrix.m[5] =UP.y;
	view_matrix.m[6] = UP.z;
	view_matrix.m[7] = -(UP.x * eye.x + UP.y * eye.y + UP.z * eye.z);

	view_matrix.m[8] = Forward.x;
	view_matrix.m[9] = Forward.y;
	view_matrix.m[10] = Forward.z;
	view_matrix.m[11] = -(Forward.x * eye.x + Forward.y * eye.y + Forward.z * eye.z);

	//view_matrix.SetFrontAndOrthonormalize(Forward);

	// Remember how to fill a Matrix4x4 (check framework slides)
	// Careful with the order of matrix multiplications, and be sure to use normalized vectors!
	
	// Create the view matrix rotation
	// ...
	// view_matrix.M[3][3] = 1.0;

	// Translate view matrix
	// ...

	UpdateViewProjectionMatrix();
}

// Create a projection matrix
void Camera::UpdateProjectionMatrix()
{
	// Reset Matrix (Identity)
	projection_matrix.SetIdentity();

	// Comment this line to create your own projection matrix!
	//SetExampleProjectionMatrix();

	// Remember how to fill a Matrix4x4 (check framework slides)
	
	if (type == PERSPECTIVE) {
		float f = 1 / std::tan(fov / 2);
		projection_matrix.m[0] = f /aspect;
		projection_matrix.m[5] = f;
		projection_matrix.m[10] = (far_plane+near_plane) / (near_plane-far_plane);
		projection_matrix.m[11] = 2*far_plane*near_plane / (near_plane - far_plane);
		projection_matrix.m[14] = -1;
		
	}
	else if (type == ORTHOGRAPHIC) {
		projection_matrix.m[0] = 2 / (right - left);
		projection_matrix.m[3] = -(right+left) / (right - left);
		projection_matrix.m[5] = 2 / (top-bottom);
		projection_matrix.m[7] = -(top+bottom) / (top-bottom);
		projection_matrix.m[10] = 2 / (far_plane-near_plane);
		projection_matrix.m[11] = -(far_plane+near_plane) / (far_plane-near_plane);
	} 

	UpdateViewProjectionMatrix();
}

void Camera::UpdateViewProjectionMatrix()
{
	viewprojection_matrix = projection_matrix * view_matrix;
}

Matrix44 Camera::GetViewProjectionMatrix()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	return viewprojection_matrix;
}

// The following methods have been created for testing.
// Do not modify them.

void Camera::SetExampleViewMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, view_matrix.m );
}

void Camera::SetExampleProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (type == PERSPECTIVE)
		gluPerspective(fov, aspect, near_plane, far_plane);
	else
		glOrtho(left,right,bottom,top,near_plane,far_plane);

	glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix.m );
	glMatrixMode(GL_MODELVIEW);
}
