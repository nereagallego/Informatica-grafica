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
CPPFLAGS = -fno-stack-protector -std=c++11 # opciones compilación  # opciones de "linkado"
#---------------------------------------------------------
# vars
EJEC = main
#---------------------------------------------------------
# directorio y clase para semáforos
PUNTO=Punto
DIRECCION=Direccion
MATRIZ=Matrix4
COORD=CoordenadasHomogeneas
ESFERA=Esfera
#---------------------------------------------------------
#directorio y clase para manejo de logs

all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o
	${CC} ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${ESFERA}.o -o ${EJEC} ${CPPFLAGS} ${LDFLAGS}

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

${EJEC}.o: ${EJEC}.cpp 
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}

${ESFERA}.o: ${ESFERA}.cpp 
	${CC} -c ${ESFERA}.cpp ${CPPFLAGS}

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${EJEC}.o ${PUNTO}.o ${DIRECCION}.o ${MATRIZ}.o ${COORD}.o ${EJEC} ${ESFERA}.o
