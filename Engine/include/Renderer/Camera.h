#pragma once
#include <Transform.h>

class Camera {
private:
	float fov;
	float near_plane;
	float far_plane;
public:
	Transform transform;
	Matrix4x4 projection_matrix;

	Camera(float fov, float near_plane, float far_plane);

	Matrix4x4 get_view_matrix();
	Matrix4x4 get_projection_matrix();
	Vector3 to_view_space(Vector3 world_space);
	void look_at(Vector3 position);

	float get_fov() { return fov; }
	float get_near_plane() { return near_plane; }
	float get_far_plane() { return far_plane; }
};