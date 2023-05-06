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

    /** @brief Creadora por Area de espera.
     * \pre <em>cierto</em>
     * \post se devuelve una instancia de area de espera;
    */
    Area_Espera();

    void alta_prioridad(string id_prioridad);
    /** @brief Creadora de un segmento de prioridad
     * \pre Requiere un id de prioridad válido
     * \post Crea o 
    */

    // Modificadoras



    // Consultores

    bool exist_prioridad(string id_prioridad) const;
     /** @brief Consultora que indica si una prioridad tiene procesos en espera.
     * \pre Requiere un id de prioridad válido.
     * \post El resultado indica si la prioridad <em>id_prioridad</em> existe o no
    */

   // Lectura y escriptura
   void imprimir_area_espera() const;
    /** @brief Escriptura de la area de espera.
     * \pre <em>cierto<em
     * \post Se devuelve en el orden decreciente todos los instantes de priorideades existentes junto con sus nums de rechazos y aceptados
    */

};


#endif