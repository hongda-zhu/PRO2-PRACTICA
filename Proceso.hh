/** @file Proceso.hh
    @brief Especificación de la clase Proceso.
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Proceso
    @brief Representa un proceso a ejecutar.

    Son tareas, procesos, para ejecutar. Tienen un identificador, memoria
    requierida y tiempo de ejecución. Dispone de operaciones para consultar cada datos de
    un proceso. Permite leer y escribir los datos de cada proceso.
*/
class Proceso {


    private:
    int left_time;
    int memory_position;

    public:


    //Constructoras

    int id;
    /** @brief Tiempo de ejecución del proceso*/
    int time;
    /** @brief Tamano que ocupa el proceso*/
    int size;

    Proceso();
    /** @brief Creadora de Proceso.
    * \pre <em>cierto</em>
    * \post Devuelve un instante de proceso vacio.
    */

    Proceso(int id, int size, int time);
    /** @brief Creadora de Proceso.
    * \pre requiere un id, tamaño y tiempo valido para la creación de proceso.
    * \post Devuelve un instante de proceso con valor de id, tamaño y tiempo.
    */

    //Modificadora


    //Lectura y escriptura

};

#endif