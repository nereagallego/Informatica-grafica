#include "Stl.h"
#include "stl_reader.hpp"



using namespace std;

STL::STL(const char* path, Punto center, float scale, RGB emission)
{
    stl_reader::ReadStlFile(path, coordsSTL, normalsSTL, trisSTL, solidRangesSTL);

    Direccion translation = center - Punto(0,0,0);
    const size_t numTris = trisSTL.size() / 3;
    for(size_t itri = 0; itri < numTris; ++itri) {
        Punto p[3];
        for(size_t icorner = 0; icorner < 3; ++icorner) {
            float* c = &coordsSTL[3 * trisSTL[3 * itri + icorner]];
            p[icorner] = Punto(c[0]*scale,c[1]*scale,c[2]*scale)+translation;
        }
        tris.push_back(Triangulo(p[0],p[1],p[2],emission));
    }
    // for (Triangle t:tris) {
    //     cout << t << endl;
    // }
    // cout << tris.size() << endl;
}

Intersect STL::intersect(Ray r) {
    float old_distance = INFINITY;
    Intersect res;
    for (Triangulo t: tris) {
        Intersect local_res = t.intersect(r);
        if(local_res._intersect){
            float new_distance = local_res._t;
            if(new_distance < old_distance){
                res = local_res;
            }
        }
    }
    return res;
}
