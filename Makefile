#*****************************************************************
# File:   Makefile
# Author: Nerea Gallego Sánchez y Victor Gallardo Sánchez
# Date:   septiembre 2022
# Coms:   Ejecutar "make" para compilar 
#         Ejecutar "make clean" para limpiar (borrar lo que genere)
#*****************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # compilador
#---------------------------------------------------------
# opciones compilación y enlazado ("linkado")
CPPFLAGS = -std=c++11 -g# opciones compilación  # opciones de "linkado"

CIMGFLAGS= -std=c++11 -g -O2 -L/usr/X11R6/lib -lm -lpthread -lX11


LDFLAGS  = -pthread
#---------------------------------------------------------
# vars
EJEC = main
#---------------------------------------------------------
# directorio y clase para semáfo
COLOR=./color
GEO=./geometry
IMAGE=./image
MATH=./math
SCENE=./scene
MATERIAL=./material
PUNTO=${MATH}/Punto
DIRECCION=${MATH}/Direccion
MATRIZ=${MATH}/Matrix4
COORD=${MATH}/CoordenadasHomogeneas
ESFERA=${GEO}/Esfera
RGB=${COLOR}/RGB
TONE=${IMAGE}/ToneMapping
TRANSFORM=${IMAGE}/Imagen
RAY=${GEO}/Ray
PLANO=${GEO}/Plano
TRI=${GEO}/Triangulo
PRIMITIVE=${GEO}/Primitive
CAMERA=${SCENE}/Camera
LUZ=${SCENE}/Light
BSDF=${SCENE}/BSDF
RAND=${MATH}/rand
STL=${GEO}/Stl
TEXTURES=${MATERIAL}/Texturas
SIMPLE=${MATERIAL}/SimpleBSDF
PRIMITIVE=${GEO}/Primitive
INTERSECT=${GEO}/Intersect
OBJ = ${GEO}/Obj
#---------------------------------------------------------
#directorio y clase para manejo de logs
all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o  ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${RAY}.o ${PLANO}.o ${TRI}.o ${CAMERA}.o ${LUZ}.o ${BSDF}.o ${RAND}.o ${STL}.o ${TEXTURES}.o ${PRIMITIVE}.o ${INTERSECT}.o ${SIMPLE}.o ${OBJ}.o
	${CC} ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${RAY}.o ${PLANO}.o ${TRI}.o ${CAMERA}.o ${LUZ}.o ${BSDF}.o ${RAND}.o ${STL}.o ${TEXTURES}.o  ${PRIMITIVE}.o ${INTERSECT}.o ${SIMPLE}.o ${OBJ}.o -o ${EJEC} ${CIMGFLAGS} ${LDFLAGS}

#---------------------------------------------------------
# compilar
${PUNTO}.o: ${PUNTO}.h ${PUNTO}.cpp
	${CC} -c ${PUNTO}.cpp -o ${PUNTO}.o ${CPPFLAGS}

${DIRECCION}.o: ${DIRECCION}.h ${DIRECCION}.cpp
	${CC} -c ${DIRECCION}.cpp -o ${DIRECCION}.o ${CPPFLAGS}

${MATRIZ}.o: ${MATRIZ}.h ${MATRIZ}.cpp
	${CC} -c ${MATRIZ}.cpp -o ${MATRIZ}.o ${CPPFLAGS}

${COORD}.o: ${COORD}.h ${COORD}.cpp
	${CC} -c ${COORD}.cpp -o ${COORD}.o ${CPPFLAGS}

${RGB}.o: ${RGB}.h ${RGB}.cpp
	${CC} -c ${RGB}.cpp -o ${RGB}.o ${CPPFLAGS}

${TONE}.o: ${TONE}.h ${TONE}.cpp
	${CC} -c ${TONE}.cpp -o ${TONE}.o ${CPPFLAGS}

${TRANSFORM}.o: ${TRANSFORM}.h ${TRANSFORM}.cpp
	${CC} -c ${TRANSFORM}.cpp -o ${TRANSFORM}.o ${CPPFLAGS}

${RAY}.o: ${RAY}.h ${RAY}.cpp ${PRIMITIVE}.h
	${CC} -c ${RAY}.cpp -o ${RAY}.o ${CPPFLAGS}

${PLANO}.o: ${PLANO}.h ${PLANO}.cpp ${PRIMITIVE}.h
	${CC} -c ${PLANO}.cpp -o ${PLANO}.o ${CPPFLAGS}

${ESFERA}.o: ${ESFERA}.h ${ESFERA}.cpp ${PRIMITIVE}.h
	${CC} -c ${ESFERA}.cpp -o ${ESFERA}.o ${CPPFLAGS}

${TRI}.o:  ${TRI}.h ${TRI}.cpp
	${CC} -c ${TRI}.cpp -o ${TRI}.o ${CPPFLAGS}

${CAMERA}.o:  ${CAMERA}.h ${CAMERA}.cpp
	${CC} -c ${CAMERA}.cpp -o ${CAMERA}.o ${CPPFLAGS} ${LDFLAGS}

${LUZ}.o: ${LUZ}.h ${LUZ}.cpp
	${CC} -c ${LUZ}.cpp -o ${LUZ}.o ${CPPFLAGS}

${BSDF}.o: ${BSDF}.h ${BSDF}.cpp
	${CC} -c ${BSDF}.cpp -o ${BSDF}.o ${CPPFLAGS}

${RAND}.o: ${RAND}.h ${RAND}.cpp
	${CC} -c ${RAND}.cpp -o ${RAND}.o ${CPPFLAGS}

${STL}.o: ${STL}.h ${STL}.cpp
	${CC} -c ${STL}.cpp -o ${STL}.o ${CPPFLAGS}

${TEXTURES}.o: ${TEXTURES}.h ${TEXTURES}.cpp
	${CC} -c ${TEXTURES}.cpp -o ${TEXTURES}.o ${CPPFLAGS}

${SIMPLE}.o: ${SIMPLE}.h ${SIMPLE}.cpp
	${CC} -c ${SIMPLE}.cpp -o ${SIMPLE}.o ${CPPFLAGS}

${PRIMITIVE}.o: ${PRIMITIVE}.h ${PRIMITIVE}.cpp ${BSDF}.o
	${CC} -c ${PRIMITIVE}.cpp -o ${PRIMITIVE}.o ${CPPFLAGS}

${INTERSECT}.o: ${INTERSECT}.h ${INTERSECT}.cpp
	${CC} -c ${INTERSECT}.cpp -o ${INTERSECT}.o ${CPPFLAGS}

${OBJ}.o: ${OBJ}.h ${OBJ}.cpp
	${CC} -c ${OBJ}.cpp -o ${OBJ}.o ${CPPFLAGS}


${EJEC}.o: ${EJEC}.cpp 
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}
#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${EJEC} ${ESFERA}.o ${TRANSFORMPPM0}.o ${RGB}.o ${EJEC} ${RAY}.o ${PLANO}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${TRI}.o ${CAMERA}.o ${LUZ}.o ${BSDF}.o ${RAND}.o ${STL}.o ${TEXTURES}.o ${SIMPLE}.o ${PRIMITIVE}.o ${INTERSECT}.o ${OBJ}.o
