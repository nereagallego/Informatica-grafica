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
TRANSFORMPPM=Transformppm
RGB=RGB
TONE=ToneMapping
#---------------------------------------------------------
#directorio y clase para manejo de logs
all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o ${RGB}.o ${TRANSFORMPPM}.o ${TONE}.o
	${CC} ${EJEC}.o ${RGB}.o ${TRANSFORMPPM}.o ${TONE}.o -o ${EJEC} ${CPPFLAGS}

#---------------------------------------------------------
# compilar
${RGB}.o: ${RGB}.h ${RGB}.cpp 
	${CC} -c ${RGB}.cpp -o ${RGB}.o ${CPPFLAGS}

${TRANSFORMPPM}.o: ${TRANSFORMPPM}.h ${TRANSFORMPPM}.cpp
	${CC} -c ${TRANSFORMPPM}.cpp -o ${TRANSFORMPPM}.o ${CPPFLAGS}

${EJEC}.o: ${EJEC}.cpp 
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}

${TONE}.o: ${TONE}.h ${TONE}.cpp
	${CC} -c ${TONE}.cpp -o ${TONE}.o ${CPPFLAGS}
#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${EJEC}.o ${TRANSFORMPPM}.o ${RGB}.o ${EJEC}
