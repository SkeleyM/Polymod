#pragma once
#include <EMath.h>
#include <Renderer/Camera.h>

class OrbitalCameraController {
private:
	float orbit_radius;
	float orbit_speed;
	Vector3 euler_rotation;
	Vector3 orbit_origin;

	Camera* camera;
public:
	OrbitalCameraController(Camera* camera);

	void rotate_from_screen_xy(float dx, float dy);
	void update();

	void set_orbit_origin(Vector3 origin);
	void set_orbit_speed(float speed);
	void set_orbit_radius(float radius);
	Vector3 get_orbit_origin();
	float get_orbit_speed();
	float get_orbit_radius();
};