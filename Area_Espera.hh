/** @file Area_Espera.hh
    @brief Especificación de la clase Area de Espera.
*/

#ifndef Area_Espera_HH
#define Area_Espera_HH

#include "Cluster.hh"
#include "Prioridad.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#endif 

/** @class Area_Espera
 *  @brief Hace referencia a la area de espera de los procesos.
 *  Contiene procesos que se quieren tratar en el cluster classificados por prioridad.
 *  Puede usarse para crear o destruir una prioridad, poner un proceso en espera, dar de
 *  alta a procesos al cluster, consultar la existencia de prioridades y procesos, consultar
 *  si una prioridad tiene tareas pendientes y dispone de operaciones d'escriptura para una
 *  o todas las prioridades.
*/
class Area_Espera {
    private:
    map <string, Prioridad> prioridades_data;


    public:

    // Constructoras

 
    Area_Espera();
    /** @brief Creadora por Area de espera.
     * \pre <em>cierto</em>
     * \post se devuelve una instancia de area de espera;
    */

    // Modificadoras

    void alta_proceso_espera(const string &id_prioridad, Proceso &job);
    /** @brief Modificadora para un nuevo instante de proceso en la lista de espera en la area de espera
     * \pre Requiere un id valido de la prioridad y un instante de proceso.
     * \post Se añade este instante de proceso a la prioridad indicada por el id de la prioridad
    */

    void alta_prioridad(string id_prioridad);
    /** @brief Modificadora para un segmento nuevo de prioridad
     * \pre Requiere un id de prioridad válido
     * \post Se añade el segmento nuevo de la prioridad en el prioridad_data
    */


    // Consultores

    bool exist_prioridad(string id_prioridad) const;
     /** @brief Consultora que indica que si existe una prioridad con el id indicado en la area de espera
     * \pre Requiere un id valido de una prioridad .
     * \post El resultado indica si la prioridad <em>id_prioridad</em> existe (true) o no (false)
    */

   bool exist_process_prioridad(Proceso job, string id_prioridad) const;
    /** @brief Consultora que indica que si existe un proceso en una prioridad del id indicado.
     * \pre Requiere un id valido de una prioridad y un proceso determinado.
     * \post El resultado indica si el proceso existe en la prioridad <em>id_prioridad</em> existe(true) o no(false).
    */

   // Lectura y escriptura

   void imprimir_area_espera() const;
    /** @brief Escriptura de la area de espera.
     * \pre <em>cierto<em>
     * \post Se devuelve en el orden decreciente todos los instantes de priorideades existentes junto con sus nums de rechazos y aceptados
    */

   void imprimir_prioridad(string id_prioridad) const; 
   /** @brief Escriptura de la area de espera
    * \pre <em>cierto<em>
    * \post Se devuelve un error en el caso cuando no existe el <em>id_prioridad<em>. Pero si existe esta prioridad, se imprime los proceso pendientes con sus informaciones detalladas por orden decreciente de antiguedad; Además debe imprimir los datos de procesos aceptados/rechazados de esta prioridad
   */

};


#endif