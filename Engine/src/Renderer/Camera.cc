#include <Engine.h>
#include <Renderer/Camera.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <EMath.h>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float near_plane, float far_plane) {
	Engine* engine_instance = Engine::get_instance();

	// Get the aspect ratio from the window dimensions.
	float aspect_ratio = engine_instance->get_aspect_ratio();
	this->projection_matrix = glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
}

Matrix4x4 Camera::get_view_matrix() {
	return this->transform.get_matrix();
}

Matrix4x4 Camera::get_projection_matrix() {
	return this->projection_matrix;
}

void Camera::look_at(Vector3 position) {
	auto look_at_origin = glm::lookAt(
		this->transform.position,
		position,
		Vector3(0.0, 1.0f, 0.0f)
	);
	Quaternion camera_orientation = glm::quat_cast(glm::inverse(look_at_origin));
	this->transform.set_rotation_quaternion(camera_orientation);
}