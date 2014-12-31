#include "Settings.h"


Settings::Settings()
	: time(new Time()), precision(new Precision()), projection(new Projection()), view(new View()), speed(new Speed()) {
		
}
Settings::Settings(Time* time, Precision* precision, Projection* projection, View* view, Speed* speed)
	: time(time), precision(precision), projection(projection), view(view), speed(speed) {
		
}
Settings::~Settings() {
	//so far there's nothing to destroy, and I doubt there'll ever be something
}

sdph(Settings) {
	TiXmlElement te("time");
	this->time->serialize(&te);
	myElement->InsertEndChild(te);

	TiXmlElement pe("precision");
	this->precision->serialize(&pe);
	myElement->InsertEndChild(pe);

	TiXmlElement ce("projection");
	this->projection->serialize(&ce);
	myElement->InsertEndChild(ce);

	TiXmlElement ve("view");
	this->view->serialize(&ve);
	myElement->InsertEndChild(ve);

	TiXmlElement se("speed");
	this->speed->serialize(&se);
	myElement->InsertEndChild(se);
}
dsdph(Settings) {
	TiXmlElement* elem = myElement->FirstChildElement("time");
	if (elem)
		this->time->deserialize(elem);

	elem = myElement->FirstChildElement("precision");
	if (elem)
		this->precision->deserialize(elem);

	elem = myElement->FirstChildElement("projection");
	if (elem)
		this->projection->deserialize(elem);

	elem = myElement->FirstChildElement("view");
	if (elem)
		this->view->deserialize(elem);

	elem = myElement->FirstChildElement("speed");
	if (elem)
		this->speed->deserialize(elem);
}