#pragma once
#include <EMath.h>

class Transform {
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform();

	void translate(Vector3 translation);
	void set_rotation(Vector3 rotation);
	void set_scale(Vector3 scale);

	// Used to translate and transform during rendering.
	Matrix4x4 get_matrix();
};