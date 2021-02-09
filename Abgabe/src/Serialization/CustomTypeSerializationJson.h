#pragma once

#include "nlohmannJSON/json.hpp"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/quaternion.hpp"

namespace glm
{
	//Vec2
	void to_json(nlohmann::json& json, const vec2& vector)
	{
		json = nlohmann::json{ {"x", vector.x}, {"y", vector.y} };
	}

	void from_json(const nlohmann::json& json, vec2& vector)
	{
		vector.x = json.at("x").get<float>();
		vector.y = json.at("y").get<float>();
	}

	//Vec3
	void to_json(nlohmann::json& json, const vec3& vector)
	{
		json = nlohmann::json{ {"x", vector.x}, {"y", vector.y}, {"z", vector.z} };
	}

	void from_json(const nlohmann::json& json, vec3& vector)
	{
		vector.x = json.at("x").get<float>();
		vector.y = json.at("y").get<float>();
		vector.z = json.at("z").get<float>();
	}

	//Vec4
	void to_json(nlohmann::json& json, const vec4& vector)
	{
		json = nlohmann::json{ {"x", vector.x}, {"y", vector.y}, {"z", vector.z}, {"w", vector.w} };
	}

	void from_json(const nlohmann::json& json, vec4& vector)
	{
		vector.x = json.at("x").get<float>();
		vector.y = json.at("y").get<float>();
		vector.z = json.at("z").get<float>();
		vector.w = json.at("w").get<float>();
	}

	//Quat
	void to_json(nlohmann::json& json, const quat& quaternion)
	{
		json = nlohmann::json{ {"qw", quaternion.w}, {"qx", quaternion.x}, {"qy", quaternion.y}, {"qz", quaternion.z} };
	}

	void from_json(const nlohmann::json& json, quat& quaternion)
	{
		quaternion.w = json.at("qw").get<float>();
		quaternion.x = json.at("qx").get<float>();
		quaternion.y = json.at("qy").get<float>();
		quaternion.z = json.at("qz").get<float>();
	}
}