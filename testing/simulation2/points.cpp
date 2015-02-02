#include <iostream>
#include <random>
#include <cmath>
#include <cfloat>

int main(int argc, char** argv) {
	if(argc!=4) {
		std::cerr << "Invalid command line" << std::endl;
		std::cerr << "Usage: random <number_of_points> <cube_diameter> <charge>" << std::endl;
		std::cerr << std::endl;
	}
	
	std::random_device rdx, rdy, rdz;
	std::default_random_engine mt1(rdx()), mt2(rdy()), mt3(rdz());
	float val = std::stof(argv[2])/1.73205080757f; //that crazy constant is just the sqrt(3)
	std::uniform_real_distribution<float> dist1(-val, std::nextafter(+val, FLT_MAX));
	std::uniform_real_distribution<float> dist2(-val, std::nextafter(+val, FLT_MAX));
	std::uniform_real_distribution<float> dist3(-val, std::nextafter(+val, FLT_MAX));
	
	int points = std::stoi(argv[1]);
	float xsum = 0.f, ysum = 0.f, zsum = 0.f;
	for(int i = 0;i < points;i++) {
		float x, y, z;
		x = dist1(mt1);
		y = dist2(mt2);
		z = dist3(mt3);
		
		xsum += x;
		ysum += y;
		zsum += z;
		
		std::cout << "<object id=\"e" << i << "\"	mesh=\"charge\"	mass=\"1\"	position=\"";
		std::cout << std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) <<"\"";
		std::cout << " charge=\"" << argv[3] << "\" />" << std::endl;
	}
	
	std::cout << std::endl;
	std::cout << "Sums: x="<< xsum << ", y=" << ysum << ", z=" << zsum << std::endl;
	std::cout << "Avgs: x="<< xsum/points << ", y=" << ysum/points << ", z=" << zsum/points << std::endl;

	return 0;
}
