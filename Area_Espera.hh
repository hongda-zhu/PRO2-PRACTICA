/** @file Area_Espera.hh
    @brief Espesificación de la clase de Area de espera
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
 *  @brief Representa el cojunto de características y operaciones de la Area de espera y de clases de prioridades.
 *  Ofrece las operaciones que permiten a chequear los estados de las prioridades, agregar nuevas prioridades y suprimir prioridades existente, enviar procesos que está agregado en la area de espera al cluster y dar la alta de proceso de espera. Finalmente también tenemos dos operaciones de escriptura, una se destina a la prioridad especifica y otra para todas las prioridades de una area de espera
*/
class Area_Espera {
    // Descripción: contiene la estructura de la area de espera y las operaciones sobre las prioridades.

    private:
    /*
        Una area de espera está formado por un cojunto de prioridades que está formado por un map ordenado crecientemente por el id de cada prioridad;
    */
   /** @brief El map de prioridades existentes en la area de espera, Ordenada crecientemente por el id de sus componentes */
    map <string, Prioridad> prioridades_data;

    public:

    // Constructoras
    /** @brief Creadora por defecto
     * \pre <em>cierto</em>
     * \post El resultado es una area de espera sin prioridades.
     * @coste Constante
    */
    Area_Espera();

    // Modificadoras
    /** @brief Modificadora de Area de Espera que gestiona el intento de entrada de un proceso en la area de espera
     * \pre job en este caso se refiere a un proceso libre que no está colocado en ningún lado
     * \post Se agrega el proceso a la prioridad indicada por el id de prioridad del parametro implicito de la area de espera.
     * \coste Logaritmico
    */
    void alta_proceso_espera(const string &id_prioridad, Proceso &job);

    /** @brief Modificadora de Area de Espera para agrega una nueva prioridad en el parametro implicito de la area de espera
     * \pre  <em>id_prioridad</em> es el identificador de la nueva prioridad 
     * \post El parametro impliclito pasa a tener una prioridad nueva con  <em>id_prioridad<em> como su identificador
     * \coste Logaritmico
    */
    void alta_prioridad(const string &id_prioridad);

    /** @brief Modificadora de Area de Espera para suprimir una prioridad existente del parametro implicito
     * \pre <em>id_prioridad</em> es el identificador de una prioridad existente en el parametro implicito
     * \post La prioridad indicado por el <em>id_prioridad</em> pasa a ser eliminado en el parametro implicito
     * \coste Logaritmico
    */
   void baja_prioridad(const string &id_prioridad);

    /** @brief Modificadora de Area de Espera que envia n procesos por el orden de prioridad al cluster.
    * \pre <em>n</em> representa el número de los procesos de envíos aceptados así n>=0
    * \post El resultado indica que se tiene queu enviar los n procesos más prioritarios (hasta que no queden procesos pendientes o hasta que todos los que queden pendiente hayan intentado colocar sin éxito) al procesador de <em>c</em> Cluster que cumple más condiciones en el caso cuando haya empates. 
    * El proceso que no ha sido colocado volverá el parametro implicito como si fuese el nuevo a la mismo prioridad, además por cada envío realizados, se tiene que actualizar los datos como los números de los procesos aceptados y rechazados de cada prioridad. 
    * \coste Constante
    */
   void enviar_procesos_cluster(const int &n, Cluster &c);

   // Lectura y escriptura
    /** @brief Escriptura de la area de espera que imprime todas las informaciones del parametro implicito
     * \pre <em>cierto</em>
     * \post Se imprime todos los procesos pendientes de las todas las prioridades existentes del parametro implicito por el orden creciente de la prioridad.
    */
   void imprimir_area_espera() const;

   /** @brief Escriptura de la area de espera
    * \pre <em>cierto</em>
    * \post Se devuelve un error en el caso cuando no existe el <em>id_prioridad<em>. Pero si existe esta prioridad, se imprime los proceso pendientes con sus informaciones detalladas por orden decreciente de antiguedad; Además debe imprimir los datos de procesos aceptados/rechazados de esta prioridad
   */
   void imprimir_prioridad(const string id_prioridad) const; 

};


#endif