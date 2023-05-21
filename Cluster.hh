/** @file Cluster.hh
    @brief Especificación de la clase Cluster.
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <queue>
#include <map>
#endif

/** @class Cluster
 *  @brief Representa a un cluster.
 * 
 *  Hace referencia a un conjunto de prcd (minimo 1) que
 *  realizan procesos y tareas. Permite anadir prcd al Cluster, compactar la memory de
 *  un procesador o todos los prcd del Cluster, dar de alta a procesos (directamente a
 *  un procesador determinado o al procesador más optimo. También permite hacer consultas sobre
 *  l'estado de un procesador, si existe, tiene tareas en ejecución, si tiene prcd auxiliares y
 *  la memory disponible. No obstante, dispone de un contador de tiempo, se puede avanzar el tiempo para
 *  terminar los procesos en ejecución. Por último, dispone de operaciones de lectura y escriptura a nivell
 *  de cluster y a nivell de procesador. 
*/
class Cluster {
    private:

    BinTree<string> prcd;
    map<string, Procesador> prcd_data;

    void i_configurar_cluster (BinTree<string> &procesadores, map<string,Procesador> &prcd_data);

    static bool i_modificar_cluster(BinTree<string> &prcd, map<string, Procesador>&prcd_data, const string &id_prcd, const Cluster &c2);

    void i_enviar_procesos_cluster(const Proceso &Job, const BinTree<string>& prcd, string& id_prcd, int &free_memory, int &gap, int &depth, int counter); // FALTA

    static void i_imprimir_estructura_cluster (BinTree<string>& prcd);


    public:
    //Constructoras

    /** @brief Creadora de Cluster
    * \pre <em>cierto</em>
    * \post El resultado es un Cluster vacío sin procesadores pendientes.
    * \coste Constante
    */
    Cluster();

    //Modificadoras
    void alta_proceso_procesador (const string &id_prcd, Proceso Job);
    /** @brief Modificadora del Cluster.
     * \pre id_prcd es el id de un procesadro en concreto y Job es un instante del módulo Proceso
     * \post Se añade un proceso en el procesado del id indicado en el caso que no se ha producido ningun tipo de errores. En caso contrario,  se imprime un error que puede ser por la inexistencia del procesador que queremos dar la alta o porque tal procesador ya contiene un instante de Proceso con el mismo id que queremos dar la alta 
     * \coste 
    */
   
    void baja_proceso_procesador (const string &id_prcd, int id_job);
    /** @brief Modificadora del Cluster.
     * \pre id_prcd es el id de un procesadro en concreto y id_job corresponde al id del proceso que queremos eliminar
     * \post Se añade un proceso en el procesado del id indicado en el caso que no se ha producido ningun tipo de errores. En caso contrario,  se imprime un error que puede ser por la inexistencia del procesador que queremos dar la alta o porque tal procesador ya contiene un instante de Proceso con el mismo id que queremos dar la alta 
     * \coste
    */

    void configurar_cluster (); 
    /** @brief Modificadora del Cluster.
     * \pre <em>cierto</em>
     * \post Devuelve el arbol de procesadores del cluster por el orden creciente de los identificadores correspondientes
    */

   void modificar_cluster (const string& id_prcd, const Cluster& c2);
    /** @brief Modificadora del Cluster.
     * \pre <em>cierto<em>
     * \post Devuelve el cluster modificado si el procesador que hemos introducido es una hoja, es decir que es un vertice sin vertices auxiliares.
    */

    void avanzar_tiempo (int t);
    /** @brief Modificadora del Cluster.
     * \pre FALTA
     * \post Accelera todos el tiempo de todo los procesadores pendientes, si el tiempo restante 't' es mayor que el tiempo que queda un procesador, este procesador se queda eliminado y liberamos su espacio
    */

    void compactar_memoria_procesador (const string &id_prcd);
    /** @brief Modificadora del Cluster que compacta la memoria de un procesador determinado
    * \pre <em>cierto<em>
    * \post En el caso cuando el procesador del id mencionado existe en el cluster, se devuelve la memoria de este procesador de forma compactado, es decir sin dejar huecos, sin solaparse y respetando el orden inicial.
    */

    void compactar_memoria_cluster ();
    /** @brief Modificadora del Cluster que compacta las memorias de todos los procesadores existente del cluster
    * \pre <em>cierto<em>
    * \post En este caso, compactan todos la memoria de todos los procesadores.
    */

   bool enviar_procesos_cluster(const Proceso& proceso); // FALTA

   // Consultora

   static bool has_auxiliary(const string id_prcd);
   /** @brief Consultora del Cluster que chequea si el procesador tiene procesadores auxiliares o no, es una 
    * \pre requiere un id de un procesador existente del Cluster
    * \post devuleve true cuando tal procesador si que contiene procesadores auxiliares.
   */


   // Lectura y escriptura

    void imprimir_procesadores_cluster ();
    /** @brief Escriptura del Cluster.
     * \pre <em>Cierto></em>
     * \post Se imprime el listado de procesadores del cluster por el orden creciente de identificador
    */    

    void imprimir_estructura_cluster ();
    /** @brief Escriptura del Cluster.
     * \pre <em>cierto</em>
     * \post se imprime la estructura de procesadores en forma creciente de primera posición de prcd_data
    */

   void imprimir_procesador (const string &id_prcd);
    /** @brief Escriptura del Cluster.
     * \pre Requiere el id valido de un procesador
     * \post se imprime los procesos de dicho profcesador por orden creciente de primera posición de memoria, incluyendo dicha posición y sus datos detallados 
    */
    
};
#endif