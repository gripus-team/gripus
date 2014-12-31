#include "IGravitation.h"

#include "UniformGravitation.h"
#include "PointGravitation.h"
#include "PlanarGravitation.h"

IGravitation* IGravitation::getGravitation(TiXmlElement* myElement) {
	std::string str(myElement->Attribute("type"));
	if (str == "uniform") {
		return new UniformGravitation();
	} else if (str == "point") {
		return new PointGravitation();
	} else if (str == "planar") {
		return new PlanarGravitation();
	} else {
		return new UniformGravitation();
	}
}