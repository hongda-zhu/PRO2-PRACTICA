/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad
*/

#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <vector>
#include <set>
#endif 


/** @class Prioridad
 *  @brief FALTA EXPLICACION
*/
class Prioridad {

    
    private:
    int n_procesos;
    int n_accepted;
    int n_rejected;
    vector <Proceso> jobs;
    set<int> id_jobs;

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
    void alta_proceso_espera(Proceso &Job);
    /** @brief Modificadora para un nuevo instante de proceso en la lista de espera en la area de espera
     * \pre Requiere un id valido de la prioridad y un instante de proceso.
     * \post Se añade este instante de proceso a la prioridad indicada por el id de la prioridad
    */ 

    // Consultoras
    void retrieve_procesos () const;
   /** @brief Lectura de la area de espera
    * \pre 
    * \post Se imprime los proceso pendientes con sus informaciones detalladas por orden decreciente de antiguedad; Además debe imprimir los datos de procesos aceptados/rechazados de esta prioridad
   */

    int retrieve_jobs_size () const;

    // Escriptura


};

#endif