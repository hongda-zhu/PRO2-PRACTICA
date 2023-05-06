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
    BinTree<string>prc;
    map<string, Procesador>prc_data; 
    void set_cluster (BinTree<string>& prc);
    /**
     * @brief: Setter de configurar_cluster
     * \pre Recibe la referencia del árbol cluster construido por procesadores, el árbol tiene que ser vacío<
     * \post El resultado sería el cluster configurado, en otras palabras, el árbol de cluster con los nodos correspondientes seteados de orden correcto
    */

    void get_cluster_structure (BinTree<string>& prc) const;
    /**
    * @brief: Getter de imprimir_estructura_cluster
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

    void configurar_cluster (); 

    /** @brief Operacion de escriptura del Cluster.
     * \pre <em>cierto</em>
     * \post Devuleve el arbol de procesadores del cluster por el orden creciente de los identificadores correspondientes
    */  

   // Lectura y escriptura

    void imprimir_procesador_cluster() const;

    /** @brief Operacion de escriptura del Cluster.
     * \pre <em>Cierto></em>
     * \post Se ha escrito la estructura los procesadores del Cluster del parametro implicito
     *  por el canal de salida.
    */    

    void imprimir_estructura_cluster();
    /** @brief Operacion de escriptura del procesador.
     * \pre <em>cierto</em>
     * \post escribe la estructura de procesadores en forma creciente de primera posición de prc_data
    */
    

};
#endif