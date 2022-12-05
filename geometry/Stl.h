#ifndef STL_HPP
#define STL_HPP
#include <iostream>
#include <vector>
#include "../math/Direccion.h"
#include "../color/RGB.h"
#include "Primitive.h"
#include "../math/Punto.h"
#include "Triangulo.h"

class Triangulo;

class STL : public Primitive {
    public:
        std::vector<Triangulo> tris;
        
    STL();
    STL(const char* path, Punto center, float scale, BSDF emission);

    Intersect intersect(Ray r) override;

    private:
        std::vector<float> coordsSTL;
        std::vector<float> normalsSTL;
        std::vector<int> trisSTL;
        std::vector<int> solidRangesSTL;
};

std::ostream& operator << (std::ostream& os, const STL& obj);

#endif