#include <Transform.h>

// Required to use any 'gtx' extensions, like eulerAngleXYZ
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform() {
	this->position = Vector3(0.0f);
	this->rotation = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
	this->scale = Vector3(1.0f);
}

void Transform::translate(Vector3 translation) {
	this->position += translation;
}

void Transform::set_rotation_euler(Vector3 rotation) {
	this->rotation = Quaternion(glm::radians(rotation));
}

void Transform::set_rotation_euler_radians(Vector3 rotation) {
	this->rotation = Quaternion(rotation);
}

void Transform::set_rotation_quaternion(Quaternion quaternion) {
	this->rotation = quaternion;
}

void Transform::set_scale(Vector3 scale) {
	this->scale = scale;
}

void Transform::set_position(Vector3 position) {
	this->position = position;
}

Matrix4x4 Transform::get_matrix() {
	Matrix4x4 translation_matrix = glm::translate(Matrix4x4(1.0f), this->position);
	Matrix4x4 rotation_matrix = glm::toMat4(this->rotation);
	Matrix4x4 scale_matrix = glm::scale(Matrix4x4(1.0f), this->scale);

	// Multiplying all 3 tranformation matrices forms the final matrix used for transformation
	return translation_matrix * rotation_matrix * scale_matrix;
}

Vector3 Transform::forward() {
	// This is a 4 component vector, the final component can be ignored.
	Matrix4x4 rotation_matrix = glm::eulerAngleXYZ(
		this->rotation.x,
		this->rotation.y,
		this->rotation.z
	);

	Vector4 forward_vector = rotation_matrix * Vector4(0.0, 0.0, -1.0, 1.0f);
	return glm::normalize(Vector3(forward_vector));
}