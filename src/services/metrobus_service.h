#ifndef METROBUS_SERVICE_H
#define METROBUS_SERVICE_H

#include <Arduino.h>

#define MAX_LINEAS 7

struct MetrobusData {
    int linea;
    bool servicioNormal;
    bool hayAfectaciones;
    String estado;
    String estaciones;
    String info;
};

void updateMetrobus();
MetrobusData* getMetrobusData();

#endif