/*
 * SphereRestriction.h
 *
 *  Created on: Jan 28, 2015
 *      Author: lexected
 */

#ifndef SPHERERESTRICTION_H_
#define SPHERERESTRICTION_H_

#include "IRestriction.h"

class SphereRestriction: public IRestriction {
public:
	SphereRestriction();
	SphereRestriction(glm::vec3 position, IRestriction::Way way, float radius);
	virtual ~SphereRestriction();
	
	float radius;
	
	glm::vec3 apply(glm::vec3& position, glm::vec3 displacement);
	
	serialization();
};

#endif /* SPHERERESTRICTION_H_ */
