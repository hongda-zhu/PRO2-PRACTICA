/** @file Area_Espera.hh
    @brief Area Espera
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
 *  @brief FALTA EXPLICACION
*/
class Area_Espera {
    private:
    map <string, Prioridad> prioridades_data;

    public:

    // Constructoras
 
    Area_Espera();
    /** @brief Creadora de Area de espera.
     * \pre <em>cierto</em>
     * \post se devuelve una instancia de area de espera;
    */

    // Modificadoras

    void alta_proceso_espera(const string &id_prioridad, Proceso &job);
    /** @brief Modificadora de Area de Espera para un nuevo instante de proceso en la lista de espera en la area de espera
     * \pre Requiere un id valido de la prioridad y un instante de proceso.
     * \post Se añade este instante de proceso a la prioridad indicada por el id de la prioridad
    */

    void alta_prioridad(const string &id_prioridad);
    /** @brief Modificadora de Area de Espera para añadir un segmento nuevo de prioridad
     * \pre <em>cierto<em>
     * \post Se añade el segmento nuevo de la prioridad en el prioridad_data, cuando la prioridad que queremos dar la alta ya existe nos imprime un error
    */

   void baja_prioridad(const string &id_prioridad);
    /** @brief Modificadora de Area de Espera para eliminar un segmento existente de prioridad
     * \pre <em>cierto<em>
     * \post Se elimina el segmento existente de la prioridad en el prioridad_data, cuando la prioridad que queremos dar la alta no existe nos imprime o cuando tiene procesos pendinetes un error
    */

   void enviar_procesos_cluster(int& n, Cluster& c);
    /** @brief Modificadora de Area de Espera que envia n procesos por orden de prioridad al cluster.
    * \pre <em>cierto<em>
    * \post Se envian los n procesos siguiendo por el orden de prioridad situado en la area de espera a los procesadores del cluster, se actualiza los numeros de procesos rechazados e procesos aceptados de cada clase de Prioridad y se vuelven aquellos procesos rechazados como si fuesen nuevos.
    */

    // Consultores

    bool exist_prioridad(string id_prioridad) const;
     /** @brief Consultora que indica que si existe una prioridad con el id indicado en la area de espera
     * \pre Requiere un id valido de una prioridad .
     * \post El resultado indica si la prioridad <em>id_prioridad</em> existe (true) o no (false)
    */

   bool exist_job_prioridad(Proceso job, string id_prioridad) const;
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