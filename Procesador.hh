/** @file Procesador.hh
    @brief Especificación de la clase Procesador.
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#include <vector>
#endif

/** @class Procesador
    @brief Hace referencia a un procesador.

    Estan identificados por un identificador unico. Dispone de operaciones para anadir o 
    eliminar un proceso al procesador, compactar la memoria de un procesador, avanzar el reloj
    de un procesador. Tambíen permite hacer consultas sobre si un procesador está ocupado, 
    la memoria disponible y la existencia de un proceso. Por ultimo, tiene operaciones de 
    lectura y escriptura para leer los datos de un procesador y escribir los procesos de estos.
*/
class Procesador {

    private:
    
    void update_max_espacio_actual();
    int espacio_maximo;
    int memoria;
    int espacio_restante;
    /*Aquest primer map serveix guardar els blocs de memoria lliure, on la clau es el tamany del bloc de
    memoria lliure i el set es per guardar la posició de memoria per on comença el bloc*/
    map <int, set<int>> blc_memoria_direccion;
    /*Aquest map serveix guardar les posicions de memoria i els procesos en sí.*/
    map<int,Proceso> direccion_tareas_datos;
    /*Aquest ultim serveix per guardar els id dels procesos i la posició de memoria per on comencen*/
    map<int,int> tareas_direccion;

    public:

    string id_procesador;

    //Constructoras

    /** @brief Creadora de Procesador
     * \pre Requiere el id de procesador y su tamano de la memoria
     * \post Devuelve un instante de procesador con su id y su tamano de memoria
    */
    Procesador(const string &id_procesador, int memoria);

    //Modificadoras


    //Consultora


    //Lectura y escriptura



};
#endif