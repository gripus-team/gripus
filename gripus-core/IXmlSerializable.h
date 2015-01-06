#pragma once

#include <tinyxml.h>
#include <string>
#include <glm/glm.hpp>

#include <string>
#include <sstream>

class IXmlSerializable {
public:
	virtual ~IXmlSerializable() = default;

#define sph()				void serialize(TiXmlElement* myElement)
#define dsph()				void deserialize(TiXmlElement* myElement)
#define serialization()		sph();dsph()

	virtual sph() = 0;
	virtual dsph() = 0;

#define sdph(cls)			void cls ::serialize(TiXmlElement* myElement)
#define dsdph(cls)			void cls ::deserialize(TiXmlElement* myElement)

	static std::string serializeVector(glm::vec3 vector) {
		return std::to_string(vector.x) + " " + std::to_string(vector.y) + " " + std::to_string(vector.z);
	}
	static std::string serializeVector(glm::vec2 vector) {
		return std::to_string(vector.x) + " " + std::to_string(vector.y);
	}
	static glm::vec3 deserializeVector(std::string vector) {
		glm::vec3 vec;
		std::stringstream ss(vector);
		ss >> vec.x;
		ss >> vec.y;
		ss >> vec.z;

		return vec;
	}
	static glm::vec2 deserializeVector2(std::string vector) {
		glm::vec2 vec;
		std::stringstream ss(vector);
		ss >> vec.x;
		ss >> vec.y;

		return vec;
	}
	static std::string serializeMatrix3x2(glm::mat3x2 matrix) {
		return	std::to_string(matrix[0][0]) + " " + std::to_string(matrix[0][1]) + " " +
			std::to_string(matrix[1][0]) + " " + std::to_string(matrix[1][1]) + " " +
			std::to_string(matrix[2][0]) + " " + std::to_string(matrix[2][1]);
	}
	static glm::mat3x2 deserializeMatrix3x2(std::string matrix) {
		glm::mat3x2 mat;
		std::stringstream ss(matrix);
		ss >> mat[0][0] >> mat[0][1];
		ss >> mat[1][0] >> mat[1][1];
		ss >> mat[2][0] >> mat[2][1];

		return mat;
	}
	static std::string serializeMatrix4x4(glm::mat4 matrix) {
		std::string string;
		for (int i = 0; i < 16; i++) {
			string += std::to_string(matrix[i/4][i%4]) + " ";
		}
		string = string.substr(0, string.length() - 1);

		return string;
	}
	static glm::mat4 deserializeMatrix4x4(std::string matrix) {
		glm::mat4 mat;
		std::stringstream ss(matrix);
		for (int i = 0; i < 16; i++) {
			ss >> mat[i / 4][i % 4];
		}

		return mat;
	}
protected:
	IXmlSerializable() = default;
};
