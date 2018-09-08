#include <math.h>
#include "intersections.h"
#include <stdio.h>

//if there is no intersection, this function should return 0
//Otherwise, populate 'intersection' with the point of intersection and return 1
int ray_sphere_intersection(ray_t observer, sphere_t obj, vector_t *intersection) {
  
  //linear term inside the norm
  vector_t h_term = observer.dir;
  //constant term inside the norm
  vector_t const_term = difference(observer.start,obj.center);
  
  //quadratic term in the expansion
  double a = dot_product(h_term,h_term);
  //linear term in the expansion
  double b = 2*dot_product(h_term,const_term);
  //constant term in the expansion
  double c = dot_product(const_term,const_term) - obj.radius*obj.radius;

  double discriminant = b*b - 4*a*c;

  //make sure the equation has real roots
  if (discriminant < 0.) return 0;
  //find the smallest positive h
  double h;
  if ((-1*b - sqrt(discriminant))/(2*a) > 0) h = (-1*b - sqrt(discriminant))/(2*a); //sphere in front of us
  else if ((-1*b + sqrt(discriminant))/(2*a) > 0) h = (-1*b + sqrt(discriminant))/(2*a); //we are inside the sphere
  else return 0; //no positive roots, so the sphere is behind us

  vector_t solution = scaled_sum(1.,observer.start,h,observer.dir);

  copy_vector(solution,intersection);
  return 1;  
}

//if there is no intersection, this function should return 0
//Otherwise, populate 'intersection' with the point of intersection and return 1
int ray_disk_intersection(ray_t observer, disk_t obj, vector_t *intersection) {
  if (dot_product(obj.normal, observer.dir) != 0) {
      vector_t n = obj.normal; vector_t c = obj.center;
      vector_t s = observer.start;  vector_t d = observer.dir;
      double t = (dot_product(n, difference(c, s)) / (dot_product(n, d)));
      if (t >= 0) {
	double r = obj.radius;
	vector_t p = sum(s, scalar_product(t, d));
	if (magnitude(difference(p, c)) < r) {
	  copy_vector(p, intersection);
	  return 1;
	}
      }
    }
    
	   
		  
  return 0;
}

//if there is no intersection, this function should return 0
//Otherwise, populate 'intersection' with the point of intersection and return 1
int ray_cylinder_intersection(ray_t observer, cylinder_t obj, vector_t *intersection) {
 if (cross_product(obj.axis, observer.dir) != 0) {
    vector_t a = obj.axis; vector_t c = obj.center; double r = obj.radius; double h = obj.height;
      vector_t s = observer.start;  vector_t d = observer.dir;
     
	   
		  
  return 0;
}

 int ray_cone_intersection(ray_t observer, cone_t obj, vector_t *intersection){
      vector_t n = obj.axis; vector_t c = obj.vertex;
      vector_t s = observer.start;  vector_t d = observer.dir;
      double t = (dot_product(n, difference(c, s)) / (dot_product(n, d)));
      if (t >= 0) {
	double r = obj.radius;
	vector_t p = sum(s, scalar_product(t, d));
	if (magnitude(difference(p, c)) < r) {
	  copy_vector(p, intersection);
	  return 1;
	
      }
    }
    
	   
		  
  return 0;
}
