#include "Obj.h"

Intersect Obj::intersect(Ray r) {

    Intersect interseccion;
    interseccion._intersect = false;
    interseccion._t = INFINITY;
    

    for (int i = 0; i < _loader.LoadedMeshes.size(); i++)
        {
            // Copy one of the loaded meshes to be our current mesh
            objl::Mesh curMesh = _loader.LoadedMeshes[i];

            // Go through every 3rd index and print the
            //    triangle that these indices represent
            for (int j = 0; j < curMesh.Indices.size(); j += 3)
            {

                objl::Vertex coordX = curMesh.Vertices[curMesh.Indices[j]];
                objl::Vertex coordY = curMesh.Vertices[curMesh.Indices[j + 1]];
                objl::Vertex coordZ = curMesh.Vertices[curMesh.Indices[j + 2]];
                Punto x(coordX.Position.X,coordX.Position.Y,coordX.Position.Z);
                Punto y(coordY.Position.X,coordY.Position.Y, coordY.Position.Z);
                Punto z(coordZ.Position.X, coordZ.Position.Y, coordZ.Position.Z);
                float v[4][4] = {{_ejeX.getX(),_ejeY.getX(),_ejeZ.getX(),_centro.getX()},{_ejeX.getY(),_ejeY.getY(),_ejeZ.getY(),_centro.getY()},{_ejeX.getZ(),_ejeY.getZ(),_ejeZ.getZ(),_centro.getZ()},{0,0,0,1}};
                Matrix4 T(v);

                CoordenadasHomogeneas wx(x);
                CoordenadasHomogeneas wy(y);
                CoordenadasHomogeneas wz(z);
                x = wx.cambioBase(T).punto();
                y = wy.cambioBase(T).punto();
                z = wz.cambioBase(T).punto();

                Triangulo t(x,y,z);
                Intersect it = t.intersect(r);
                if(it._intersect && it._t < interseccion._t && it._t > 0){
                    interseccion = it;

                    
                }
            }

        }
    interseccion._emision = this->getEmision();
    return interseccion;
}