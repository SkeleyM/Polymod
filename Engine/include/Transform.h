#pragma once
#include <EMath.h>

class Transform {
public:
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;

	Transform();

	void translate(Vector3 translation);
	void set_rotation_euler(Vector3 rotation);
	void set_rotation_euler_radians(Vector3 rotation);
	void set_rotation_quaternion(Quaternion quaternion);
	void set_scale(Vector3 scale);
	void set_position(Vector3 position);

	// Used to translate and transform during rendering.
	Matrix4x4 get_matrix();
	Vector3 forward();
};