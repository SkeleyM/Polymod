#include <Transform.h>

// Required to use any 'gtx' extensions, like eulerAngleXYZ
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform() {
	this->position = Vector3(0.0f);
	this->rotation = Vector3(0.0f);
	this->scale = Vector3(1.0f);
}

void Transform::translate(Vector3 translation) {
	this->position += translation;
}

void Transform::set_rotation(Vector3 rotation) {
	this->rotation = rotation;
}

void Transform::set_scale(Vector3 scale) {
	this->scale = scale;
}

Matrix4x4 Transform::get_matrix() {
	Matrix4x4 translation_matrix = glm::translate(Matrix4x4(1.0f), this->position);
	Matrix4x4 rotation_matrix = glm::eulerAngleXYZ(
		this->rotation.x, 
		this->rotation.y, 
		this->rotation.z
	);
	Matrix4x4 scale_matrix = glm::scale(Matrix4x4(1.0f), this->scale);

	// Multiplying all 3 tranformation matrices forms the final matrix used for transformation
	return translation_matrix * rotation_matrix * scale_matrix;
}