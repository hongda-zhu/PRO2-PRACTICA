/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

    /*El métode que he empleat pricipalment per simular la memoria es utilitzar procesos amb id -1, que simbolitzen els blocs ocupats. 
    Per tant, en el segon map de direcció-proces hi haura procesos amb identificador -1.
    */

Procesador::Procesador(const string &id_procesador, int memoria) {
    this->memoria = memoria;
    espacio_maximo = memoria;
    espacio_restante = memoria;
    blc_memoria_direccion.insert(make_pair(memoria, set<int>{0}));
    this->id_procesador = id_procesador;
}
