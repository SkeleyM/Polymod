#include <OrbitalCameraController.h>

#include <iostream>

#include <glm/gtc/matrix_access.hpp>

OrbitalCameraController::OrbitalCameraController(Camera* camera) {
	this->camera = camera;

	this->orbit_radius = 5.0f;
	this->orbit_speed = 0.005f;
	this->euler_rotation = Vector3(0.0, 0.0, 0.0);
	this->orbit_origin = Vector3(0.0, 0.0, 0.0);
}

void OrbitalCameraController::rotate_from_screen_xy(float dx, float dy) {
	this->euler_rotation.x += dx * this->orbit_speed;
	this->euler_rotation.y += dy * this->orbit_speed;

	// Prevent gimbal locking
	this->euler_rotation.y = glm::clamp(
		this->euler_rotation.y,
		glm::radians(-89.0f),
		glm::radians(89.0f)
	);
}

void OrbitalCameraController::update() {
	// Equation of a sphere
	Vector3 test = Vector3(
		sin(this->euler_rotation.x) * cos(this->euler_rotation.y),
		sin(this->euler_rotation.y),
		cos(this->euler_rotation.x) * cos(this->euler_rotation.y)
	) * this->orbit_radius;

	this->camera->transform.set_position(test + this->orbit_origin);

	// Make the camera face the origin
	this->camera->look_at(this->orbit_origin);
}

void OrbitalCameraController::set_orbit_origin(Vector3 origin) {
	this->orbit_origin = origin;
}

void OrbitalCameraController::set_orbit_speed(float speed) {
	this->orbit_speed = speed;
}

void OrbitalCameraController::set_orbit_radius(float radius) {
	this->orbit_radius = radius;
}

Vector3 OrbitalCameraController::get_orbit_origin() {
	return this->orbit_origin;
}

float OrbitalCameraController::get_orbit_speed() {
	return this->orbit_speed;
}

float OrbitalCameraController::get_orbit_radius() {
	return this->orbit_radius;
}
