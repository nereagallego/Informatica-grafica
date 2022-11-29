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
CPPFLAGS = -std=c++17 -g# opciones compilación  # opciones de "linkado"
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
PHOTONMAPPER=./photonmapping
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
PHOTONMAPPING=${PHOTONMAPPER}/photonmapping
KDTREE=${PHOTONMAPPER}/kdtree
RAND=${MATH}/rand
#---------------------------------------------------------
#directorio y clase para manejo de logs
all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o  ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${RAY}.o ${PLANO}.o ${TRI}.o ${CAMERA}.o ${LUZ}.o ${BSDF}.o  ${KDTREE}.o ${RAND}.o ${PHOTONMAPPING}.o 
	${CC} ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${RAY}.o ${PLANO}.o ${TRI}.o ${CAMERA}.o ${LUZ}.o ${BSDF}.o ${KDTREE}.o ${RAND}.o ${PHOTONMAPPING}.o -o ${EJEC} ${CPPFLAGS} ${LDFLAGS}

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

${KDTREE}.o: ${KDTREE}.h ${KDTREE}.cpp 
	${CC} -c ${KDTREE}.cpp -o ${KDTREE}.o ${CPPFLAGS}

${RAND}.o: ${RAND}.h ${RAND}.cpp 
	${CC} -c ${RAND}.cpp -o ${RAND}.o ${CPPFLAGS}

${PHOTONMAPPING}.o: ${PHOTONMAPPING}.h ${PHOTONMAPPING}.cpp 
	${CC} -c ${PHOTONMAPPING}.cpp -o ${PHOTONMAPPING}.o ${CPPFLAGS}

${EJEC}.o: ${EJEC}.cpp 
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}
#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${EJEC} ${ESFERA}.o ${TRANSFORMPPM}.o ${RGB}.o ${EJEC} ${RAY}.o ${PLANO}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${TRI}.o ${CAMERA}.o ${LUZ}.o ${BSDF}.o ${KDTREE}.o  ${PHOTONMAPPING}.o ${RAND}.o
