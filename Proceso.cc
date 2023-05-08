/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {}

void Proceso:: read () {
    cin >> id >> size >> left_time;
}

int Proceso:: retrieve_id () {
    return id;
}
int Proceso:: retrieve_size () {
    return size;
}

int Proceso:: retrieve_time () {
    return left_time;
}