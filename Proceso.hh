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
    int id;
    /** @brief Tamano que ocupa el proceso*/
    int size;

    public:

    //Constructoras



    Proceso();
    /** @brief Creadora de Proceso.
    * \pre <em>cierto</em>
    * \post Devuelve un instante de proceso vacio.
    */

    //Modificadora

    // Consultora
    int retrieve_id();
    /** @brief Consultora de Proceso.
    * \pre <em>cierto</em>
    * \post devuleve el id de proceso.
    */

    int retrieve_size();
    /** @brief Consultora de Proceso.
    * \pre <em>cierto</em>
    * \post devuleve el tamano que ocupa la memoria de proceso.
    */


    //Lectura y escriptura´
    void read ();
    /** @brief Lectura de Proceso.
    * \pre <em>cierto</em>
    * \post lee el id, tiempo y tamano para formular el proceso.
    */


};

#endif