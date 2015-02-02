/*
 * IRestriction.h
 *
 *  Created on: Jan 28, 2015
 *      Author: lexected
 */

#ifndef IRESTRICTION_H_
#define IRESTRICTION_H_

#include "IXmlSerializable.h"

class IRestriction {
public:
	enum Way {
		In,
		Out,
		InOut
	};
	static std::string serializeWay(Way way);
	static Way deserializeWay(std::string str);
	
	IRestriction();
	IRestriction(glm::vec3 position, Way way);
	virtual ~IRestriction();
	
	glm::vec3 position;
	Way way;
	
	virtual glm::vec3 apply(glm::vec3& position, glm::vec3 displacement) = 0;
	
	virtual sph() = 0;
	virtual dsph() = 0;
	static IRestriction* getRestriction(TiXmlElement* element);
};

#endif /* IRESTRICTION_H_ */
