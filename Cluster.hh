/** @file Cluster.hh
    @brief Especificación de la clase Cluster.
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"
#include "Proceso.hh"
#include "BinTree.hh"

#ifndef NO_DIAGRAM
#include <map>
#endif 

/** @class Cluster
 *  @brief Esta clase hace referencia a un Cluster, se consiste en un arb de procesadores (minimo 1) que
 *  realizan procesos y tareas. Permite anadir procesadores al Cluster, compactar la memoria de
 *  un procesador o todos los procesadores del Cluster, dar de alta a procesos (directamente a
 *  un procesador determinado o al procesador más optimo. También permite hacer consultas sobre
 *  l'estado de un procesador, si existe, tiene tareas en ejecución, si tiene procesadores auxiliares y
 *  la memoria disponible. No obstante, dispone de un contador de tiempo, se puede avanzar el tiempo para
 *  terminar los procesos en ejecución. Por último, dispone de operaciones de lectura y escriptura a nivell
 *  de cluster y a nivell de procesador. 
*/
class Cluster {

    private:
    BinTree<string>prcd;
    map<string, Procesador>prcd_data; 
    void set_cluster (BinTree<string>& prcd);
    /**
     * @brief: Setter de configurar_cluster
     * \pre Recibe la referencia del árbol cluster construido por procesadores, el árbol tiene que ser vacío<
     * \post El resultado sería el cluster configurado, en otras palabras, el árbol de cluster con los nodos correspondientes seteados de orden correcto
    */

    void get_cluster_structure (BinTree<string>& prcd) const;
    /**
    * @brief: Getter recursiva de imprimir_estructura_cluster
    * \pre Recibe la referencia de arbol
    * \post Imprime el resultado de forma ordenado creciente del árbol binario
   */

    public:

    //Constructoras

    /** @brief Creadora de Cluster
    * \pre <em>cierto</em>
    * \post Devuelve un Cluster vacio.
    */
    Cluster();

    //Modificadoras

    void alta_proceso_procesador (string id_prcd, Proceso Job);
    /** @brief Modificadora del Cluster.
     * \pre <em>cierto</em>
     * \post Se añade un proceso en el procesado del id indicado o imprime un error porque no existe el procesador con el id indicado
    */
   
    void baja_proceso_procesador (string id_prcd, int id_job);
    /** @brief Modificadora del Cluster.
     * \pre <em>cierto</em>
     * \post Se elimina un proceso en el procesado del id indicado o imprime un error porque ya existe un proceso con el mismo id en el procesador.
    */  

    void configurar_cluster (); 
    /** @brief Modificadora del Cluster.
     * \pre <em>cierto</em>
     * \post Devuleve el arbol de procesadores del cluster por el orden creciente de los identificadores correspondientes
    */

   // Consultora

    void imprimir_procesadores_cluster();
    /** @brief Consultora del Cluster.
     * \pre <em>Cierto></em>
     * \post Se imprime el listado de procesadores del cluster por el orden creciente de identificador
    */    

    void imprimir_estructura_cluster();
    /** @brief Consultora del Cluster.
     * \pre <em>cierto</em>
     * \post se imprime la estructura de procesadores en forma creciente de primera posición de prcd_data
    */

   void imprimir_procesador(string id_procesador);
    /** @brief Consultora del Cluster.
     * \pre Requiere el id valido de un procesador
     * \post se imprime los procesos de dicho profcesador por orden creciente de primera posición de memoria, incluyendo dicha posición y sus datos detallados 
    */
   
   // Lectura y escriptura

   


    
};
#endif