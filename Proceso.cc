/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {}

void Proceso:: read () {
    cin >> id >> size >> left_time;
}

int Proceso:: retrieve_id () const {
    return id;
}
int Proceso:: retrieve_size () const {
    return size;
}

int Proceso:: retrieve_time () const {
    return left_time;
}

void Proceso::actualizar_proceso (int t) {
    left_time -= t;
}

void Proceso:: print() const {
    cout << id << ' ' << size << ' ' << left_time << endl; 
}
    