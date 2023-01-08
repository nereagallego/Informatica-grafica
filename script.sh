make -f Makefile1
./Prueba

git add -A
git commit -m "convergencia materiales"
git push

make -f Makefile2
./Prueba1

git add -A
git commit -m "color bleeding"
git push 

make -f Makefile3
./Prueba2

git add -A
git commit -m "convergencia luz"
git push

make -f Makefile
./main textura.ppm
git add -A
git commit -m "imagenes pruebas"
git push 