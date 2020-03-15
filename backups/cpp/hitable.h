#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include "aabb.h"
#include <float.h>

class Material;
class Texture;

struct HitRecord{
    float t;  
    float u;
    float v;
    vec3 p;
    vec3 normal;
    Material *mat_ptr;
};


class Hitable{
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
    virtual bool bounding_box(float t0, float t1, AABB& box) const = 0;

    virtual ~Hitable() {};
};


class FlipNormals: public Hitable{
public:
    FlipNormals(Hitable* p): ptr(p) {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const{
        if(ptr->hit(r, t_min, t_max, rec)){
            rec.normal = -rec.normal;
            return true;
        }else{
            return false;
        }
    }
    virtual bool bounding_box(float t0, float t1, AABB& box) const{
        return ptr->bounding_box(t0, t1, box);
    }

    Hitable* ptr;
};


#endif