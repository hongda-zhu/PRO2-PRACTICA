/** @file Prioridad.hh
    @brief  Especificación de la clase Prioridad
*/

#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <list>
#include <set>
#endif 


/** @class Prioridad
 *  @brief 
 *  Representa la información de una prioridad donde cada prioridad está formado por una lista de procesos (tal lista puede ser vacio).
 *  La clase de Prioridad dispone un conjunto de operaciones que permite agregar y eliminar procesos correspondientes. También dispone modificadores que permite modificar los numeros de procesos enviados aceptados y rechazados. Por el último, dispone varias operaciones de escriptura que permite imprimir el estado de los procesos existentes y las informaciones relevantes del parametro implicito.
*/
class Prioridad {

    // Descripción: contiene un conjunto de procesos pendiente y informaciones relevantes de una prioridad
    
    private:
    /** @brief numero de envios aceptados de procesos*/
    int n_accepted;
    /** @brief numero de envios rechazados de procesos*/
    int n_rejected;
    /** @brief listado de procesos de la prioridad*/
    list <Proceso> jobs;
    /** @brief listado de identificadores de procesos de la prioridad ordenado por el orden creciente*/
    set<int> id_jobs;

    public:

    // Constructoras

    /** @brief Creadora de Prioridad
    * \pre <em>cierto</em>
    * \post El resultado es una prioridad identificado como el parametro <em>id_prioridad</em> situado en el conjunto de la area de espera
    *  \coste Constante
    */
    Prioridad ();

    // Modificadora
    /** @brief Modificadora de Prioridad para un nuevo instante de proceso en la lista de espera en la area de espera
     * \pre Requiere un id valido de la prioridad y un instante de proceso.
     * \post Se añade este instante de proceso a la prioridad indicada por el id de la prioridad
     * \coste Logaritmico
    */ 
    void alta_proceso_espera(Proceso &Job);

    // Modificadora
    /** @brief Modificadora de Prioridad para actualizar los n_aceptados e los n_rechazados
     * \pre <em>cierto</em>
     * \post Los valores mencionados se quedan actualizados
    */ 
   void update_prioridad(const int accepted, const int rejected);

    
    // Lectura y Escriptura
   /** @brief Escriptura de la Prioridad
    * \pre <em>cierto</em>
    * \post Se imprime los proceso pendientes con sus informaciones detalladas por orden decreciente de antiguedad; Además debe imprimir los datos de procesos aceptados/rechazados de esta prioridad
    * \coste Linear que depende el tamaño de la lista de procesos del parametro implicito
   */
    void retrieve_jobs () const;

    /**
     * @brief Escriptura de la Prioridad que devuelve el proceso más antiguo de la lista
     * \pre <em>cierto</em>
     * \post Devuelve el proceso que cumple el criterio mencionado
     * \coste Logaritmico
    */
    Proceso retrieve_job ();


    /**
     * @brief Escriptura de la Prioridad que devuelve el tamaño de la lista de procesos
     * \pre <em>cierto</em>
     * \post Devuelve el tamaño de la lista de procesos 
     * \coste Constante
    */
    int retrieve_jobs_size () const;

    /**
     * @brief Escriptura de la Prioridad que devuelve el valor actual de los n_aceptados y n_rechazados
     * \pre <em>cierto</em>
     * \post Devuelve los valores mencionados en el biref
     * \coste Constante
    */
    pair<int, int> retrieve_info() const;
};

#endif