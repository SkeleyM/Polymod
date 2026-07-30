#pragma once
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

using Vector4 = glm::vec4;
using Vector3 = glm::vec3;
using Vector2 = glm::vec2;
using Quaternion = glm::quat;
using Matrix4x4 = glm::mat4x4;