/*
 * MassGravitation.h
 *
 *  Created on: Jan 6, 2015
 *      Author: lexected
 */

#ifndef MASSGRAVITATION_H_
#define MASSGRAVITATION_H_

#include "IGravitation.h"

class MassGravitation: public IGravitation {
public:
	MassGravitation();
	MassGravitation(glm::vec3 position, float mass);
	virtual ~MassGravitation();
	
	glm::vec3 getForce(float mass, glm::vec3 position);
	
	glm::vec3 position;
	float mass;
	
	serialization();
};

#endif /* MASSGRAVITATION_H_ */
