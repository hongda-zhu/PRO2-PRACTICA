/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad.
*/

#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <list>
#include <set>
#endif 


/** @class Prioridad
 *  @brief Esta clase hace referencia a una prioridad, un contenedor de procesos con una 
 *  etiqueta formado por un string. Dispone de un conjunto de operaciones que permite anadir
 *  y eliminar procesos de una prioridad. Permite consultar el proceso mas antiguo, el numero
 *  de procesos acceptados y rechazados, el numero de procesos pendientes, si existe un proceso
 *  concreto. Por ultimo dispone de una operacion de escriptura que imprime todos los procesos
 * de una prioridad.
*/
class Prioridad {

    
    private:
    int n_procesos;
    int n_accepted;
    int n_rejected;
    list <Proceso> prcs;
    set<int> id_procesos;

    public:

    // Constructoras

    /** @brief Creadora de Prioridad
     * 
    * \pre <em>cierto</em>
    * \post El resultado es una prioridad identificado como el parametro <em>id_prioridad</em>
    *  sin procesos.
    */
    Prioridad ();

    // Modificadora

    // Consultoras

    //Escriptura

    /** @brief Escriptura de de los procesos existentes de la prioridad selecionada.
    * \pre <em>cierto</em>
    * \post Se escribe los procesos correspondientes de los procesos aceptados y rechazados de la prioridad selecionada.
    */
    void print_procesos () const;

};

#endif