#pragma once

#include "IXmlSerializable.h"

#include "Time.h"
#include "Precision.h"
#include "Projection.h"
#include "View.h"
#include "Speed.h"

class Settings : public IXmlSerializable
{
public:
	Settings();
	Settings(Time* time, Precision* precision, Projection* projection, View* view, Speed* speed);
	~Settings();

	Time* time;
	Precision* precision;
	Projection* projection;
	View* view;
	Speed* speed;

	serialization();
};

