#include "Prioridad.hh"

Prioridad:: Prioridad() {
    n_procesos = 0;
    n_accepted = 0;
    n_rejected = 0;
}

void Prioridad:: retrieve_procesos () const {
    cout << n_accepted << ' ' << n_rejected << endl;
}