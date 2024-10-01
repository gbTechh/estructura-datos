#!/bin/bash

# Colores para la consola
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # Sin color

# Ruta del archivo o archivos que deseas monitorear
# WATCHED_FILES="*.cpp"
WATCHED_FILES="stack.cpp"

# Comando para compilar
# COMPILE_CMD="g++ -o output_program *.cpp"
COMPILE_CMD="g++ -o output_program stack.cpp"

# Monitorea cambios en los archivos
while inotifywait -e close_write $WATCHED_FILES; do
    echo -e "${YELLOW}Cambios detectados, compilando...${NC}"
    $COMPILE_CMD
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Compilación exitosa! Ejecutando el programa...${NC}"
        echo -e "${GREEN}----------------------------------------------${NC}"
        ./output_program
        echo -e "${GREEN}----------------------------------------------${NC}"
    else
        echo -e "${RED}Error en la compilación${NC}"
    fi
done
