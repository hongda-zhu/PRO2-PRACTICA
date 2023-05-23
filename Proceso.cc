/** @file Proceso.cc
    @brief  Codigo de la clase de Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {}

void Proceso:: read () {
    // Lee todos los datos por el canal de la entrada
    cin >> id >> size >> left_time;
}

int Proceso:: retrieve_id () const {
    // Devuelve el id de proceso
    return id;
}
int Proceso:: retrieve_size () const {
    // Devuelve el tamaño de proceso
    return size;
}

int Proceso:: retrieve_time () const {
    // Devuelve el tiempo restante de proceso
    return left_time;
}

void Proceso::actualizar_proceso (int t) {
    // Actualiza el tiempo restante respecto el valor t
    left_time -= t;
}

void Proceso:: print() const {
    // Imprime todos los parametros implicitos del Proceso
    cout << id << ' ' << size << ' ' << left_time << endl; 
}
    