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
CPPFLAGS = -std=c++11 # opciones compilación  # opciones de "linkado"
#---------------------------------------------------------
# vars
EJEC = main
#---------------------------------------------------------
# directorio y clase para semáfo
P1_LIB=./p1
PUNTO=${P1_LIB}/Punto
DIRECCION=${P1_LIB}/Direccion
MATRIZ=${P1_LIB}/Matrix4
COORD=${P1_LIB}/CoordenadasHomogeneas
ESFERA=${P1_LIB}/Esfera
P2_LIB=./p2
RGB=${P2_LIB}/RGB
TONE=${P2_LIB}/ToneMapping
TRANSFORM=${P2_LIB}/Transformppm
P3_LIB=./p3
RAY=${P3_LIB}/Ray
PLANO=${P3_LIB}/Plano
#---------------------------------------------------------
#directorio y clase para manejo de logs
all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o  ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${RAY}.o ${PLANO}.o
	${CC} ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o ${RAY}.o ${PLANO}.o -o ${EJEC} ${CPPFLAGS}

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

${ESFERA}.o: ${ESFERA}.h ${ESFERA}.cpp 
	${CC} -c ${ESFERA}.cpp -o ${ESFERA}.o ${CPPFLAGS}

${RGB}.o: ${RGB}.h ${RGB}.cpp
	${CC} -c ${RGB}.cpp -o ${RGB}.o ${CPPFLAGS}

${TONE}.o: ${TONE}.h ${TONE}.cpp
	${CC} -c ${TONE}.cpp -o ${TONE}.o ${CPPFLAGS}

${TRANSFORM}.o: ${TRANSFORM}.h ${TRANSFORM}.cpp
	${CC} -c ${TRANSFORM}.cpp -o ${TRANSFORM}.o ${CPPFLAGS}

${RAY}.o: ${RAY}.h ${RAY}.cpp
	${CC} -c ${RAY}.cpp -o ${RAY}.o ${CPPFLAGS}

${PLANO}.o: ${PLANO}.h ${PLANO}.cpp
	${CC} -c ${PLANO}.cpp -o ${PLANO}.o ${CPPFLAGS}

${EJEC}.o: ${EJEC}.cpp 
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}
#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${EJEC} ${ESFERA}.o ${TRANSFORMPPM}.o ${RGB}.o ${EJEC} ${RAY}.o ${PLANO}.o ${RGB}.o ${TONE}.o ${TRANSFORM}.o
