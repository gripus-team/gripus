#include <iostream>
#include <random>
#include <cmath>
#include <cfloat>

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct vec { 
	float x, y, z; 
};
inline float magnitude(vec v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
inline vec cross(vec v1, vec v2) {
	vec ret;
	ret.x = v1.y*v2.z - v1.z*v2.y;
	ret.y = v1.z*v2.x - v1.x*v2.z;
	ret.z = v1.x*v2.y - v1.y*v2.x;
	return ret;
}
inline vec unit(vec v) {
	float magnitude = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	vec ret { v.x/magnitude, v.y/magnitude, v.z/magnitude };
	return ret;
}

struct pair {
	vec* v1, *v2;
	float dist;
};

vec* find_nearest(std::vector<vec>& vecs, vec* v1, vec* v2, vec* avoid) {
	float min_avg = FLT_MAX;
	vec* nearest = nullptr;
	for(vec & f : vecs) {
		if(&f == v1 || &f == v2 || &f == avoid)
			continue;
		
		float dist1 = sqrt((v1->x-f.x)*(v1->x-f.x) + (v1->y-f.y)*(v1->y-f.y) + (v1->z-f.z)*(v1->z-f.z));
		float dist2 = sqrt((v2->x-f.x)*(v2->x-f.x) + (v2->y-f.y)*(v2->y-f.y) + (v2->z-f.z)*(v2->z-f.z));
		float avg = (dist1 + dist2) / 2;
		if(avg < min_avg) {
			min_avg = avg;
			nearest = &f;
		}
	}
	
	return nearest;
}
void find_fan(std::vector<vec> & vecs, vec* v, std::vector<pair> & pairs, std::vector<float> & space_angles, std::vector<float> & triangle_angles) {
	float min_dist = FLT_MAX;
	vec* min_vec = nullptr;
	for(vec & f: vecs) {
		if(&f == v)
			continue;
		
		float dist = sqrt((v->x-f.x)*(v->x-f.x) + (v->y-f.y)*(v->y-f.y) + (v->z-f.z)*(v->z-f.z));
		if(dist < min_dist) {
			min_dist = dist;
			min_vec = &f;
		} 
	}
	
	//we've found the nearest vector, now fan around v starting at min_vec
	vec* operated, *curr = min_vec, *prev = min_vec;
	std::vector<vec*> newly;
	while(operated = find_nearest(vecs, v, curr, prev)) {
		if(std::find_if(pairs.begin(), pairs.end(), 
						[v, operated](pair & p) -> 
							bool { return (p.v1==v && p.v2==operated || p.v1==operated && p.v2==v); }) == pairs.end()) {
			newly.push_back(operated);
			
			pair p;
			p.v1 = v;
			p.v2 = operated;
			p.dist = sqrt((p.v1->x-p.v2->x)*(p.v1->x-p.v2->x)
							+ (p.v1->y-p.v2->y)*(p.v1->y-p.v2->y)
							+ (p.v1->z-p.v2->z)*(p.v1->z-p.v2->z));
			pairs.push_back(p);
			
			p.v1 = curr;
			p.dist = sqrt((p.v1->x-p.v2->x)*(p.v1->x-p.v2->x)
						+ (p.v1->y-p.v2->y)*(p.v1->y-p.v2->y)
						+ (p.v1->z-p.v2->z)*(p.v1->z-p.v2->z));
			pairs.push_back(p);
			
			vec side2 { curr->x - v->x, curr->y - v->y, curr->z - v->z };
			vec side3 { operated->x - v->x, operated->y - v->y, operated->z - v->z };
			float ms2 = magnitude(side2);
			float ms3 = magnitude(side3);
			vec sd { side2.x - side3.x, side2.y - side3.y, side2.z - side3.z };
			float msd = magnitude(sd);
			/* cos(gamma) = (a^2 + b^2 - (a-b)^2)/(2 * a * b) */
			float gamma = acos((ms2*ms2 + ms3*ms3 - msd*msd) / (2*ms2*ms3));
			triangle_angles.push_back(gamma);

			if(prev!=curr) {
				vec side1 { prev->x - v->x, prev->y - v->y, prev->z - v->z };
				
				vec c1 = cross(side2, side1);
				vec c2 = cross(side3, side2);
				
				c1 = unit(c1);
				c2 = unit(c2);
				
				vec cd { c1.x - c2.x, c1.y - c2.y, c1.z - c2.z}; //cross distance
				
				/* cos(alpha) = 1 - d^2/2 */
				float cdmag = magnitude(cd);
				float alpha = acos(1 - cdmag*cdmag/2);
				space_angles.push_back(alpha);
			}
		}
		
		if(operated==min_vec)
			break;
		else {
			prev = curr;
			curr = operated;
		}
	}
	
	for(vec* nv : newly)
		find_fan(vecs, nv, pairs, space_angles, triangle_angles);
}

int main(int argc, char** argv) {
	if(argc!=1) {
		std::cerr << "Invalid command line" << std::endl;
		std::cerr << "Usage: analyser" << std::endl;
		std::cerr << std::endl;
	}
	
	std::vector<vec> vecs;
	std::string line;
	while(std::getline(std::cin, line)) {
		auto pos = line.find("position=\"");
		pos += 10;
		
		vec v;
		
		std::stringstream ss(line.substr(pos));
		ss >> v.x >> v.y >> v.z;
		
		vecs.push_back(v);
	}
	
	float ix = vecs[0].x, iy = vecs[0].y, iz = vecs[0].z;
	int min_i = 0; float min_dist = FLT_MAX;
	for(int i = 1;i < vecs.size();i++) {
		vec & v = vecs[i];
		
		ix += v.x;
		iy += v.y;
		iz += v.z;
		
		float d = sqrt((v.x-vecs[0].x)*(v.x-vecs[0].x) + (v.y-vecs[0].y)*(v.y-vecs[0].y) + (v.z-vecs[0].z)*(v.z-vecs[0].z));
		if(d < min_dist) {
			min_dist = d;
			min_i = i;
		}
	}
	std::cout << "Balance vector: (" << ix << ", " << iy << ", " << iz << "), magnitude " << sqrt(ix*ix + iy*iy + iz*iz) << std::endl;
	
	std::vector<pair> pairs;
	std::vector<float> angles; std::vector<float> triangle_angles;
	find_fan(vecs, &vecs[0], pairs, angles, triangle_angles);
	
	float distance_sum = 0.f;
	for(pair & p: pairs) {
		distance_sum += p.dist;
	}
	float distance_avg = (distance_sum / (float)pairs.size());
	std::cout << "Avg. distance: " << distance_avg << std::endl;
	
	float distance_dev = 0.f;
	for(pair & p: pairs) {
		distance_dev += fabs(p.dist - distance_avg);
	}
	std::cout << "Std. deviation: " << (distance_dev / (float)pairs.size()) << std::endl;
	
	/* SPACE ANGLES (alpha between planes) */
	float angle_sum = 0.f;
	for(float alpha : angles) {
		angle_sum += alpha;
	}
	float angle_avg = (angle_sum / (float)angles.size());
	std::cout << "Avg. space angle: " << angle_avg << std::endl;
	
	float angle_dev = 0.f;
	for(float alpha : angles) {
		angle_dev += fabs(alpha - angle_avg);
	}
	std::cout << "Std. deviation: " << (angle_dev / (float)angles.size()) << std::endl;

	/* INTERNAL CIRCLE ANGLE (gamma between sides) */
	angle_sum = 0.f;
	for(float alpha : triangle_angles) {
		angle_sum += alpha;
	}
	angle_avg = (angle_sum / (float)triangle_angles.size());
	std::cout << "Avg. internal angle: " << angle_avg << std::endl;
	
	angle_dev = 0.f;
	for(float alpha : triangle_angles) {
		angle_dev += fabs(alpha - angle_avg);
	}
	std::cout << "Std. deviation: " << (angle_dev / (float)triangle_angles.size()) << std::endl;
	
	return 0;
}
