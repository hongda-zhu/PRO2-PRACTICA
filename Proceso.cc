/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {}
Proceso::Proceso(int id, int size, int time) {
    this->id = id;
    this->size = size;
    this->time = time;
}