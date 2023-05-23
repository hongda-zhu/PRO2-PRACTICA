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
 *  @brief Representa a un conjunto de procesadores. 
 
 Hace referencia a un conjunto de procesador o prcd (minimo 1) que realizan procesos y tareas. Permite agregar nuevos procesadores y suprimir un procesador en concreto en el parametro implicito, también permite compactar la memory de un procesador en concreto o todos los procesadores que tiene el parametro implicito, dar de alta a procesos al procesador correspondinete. Tiene operaciones para hacer consultas o modificar sobre los estados de un procesador. Por el último,  dispone operaciones de lectura y escriptura para un procesador o un conjunto de procesadores del parametro implicito.
*/
class Cluster {
    // Descripción: contiene la estructura de procesadores y las operaciones de un cluster.
    private:

    /** @brief Estructura de procesadores(prcd)*/
    BinTree<string> prcd;

    /** @brief Conjunto de procesadores ordenado por el orden creciente de id */
    map<string, Procesador> prcd_data;

    /**
     * @brief Creadora que inicializa el cluster
     * \pre <em>cierto</em>
     * \post El resultado es un conjunto de procesadores ordenado crecientemente por el id de cada procesador. Este nuevo instante pasará a sustituir el viejo cluster, si previamente ya existía un instante de Cluster.
     * \coste Linear que depende del volumen de procesadores leídos.
    */
    void i_configurar_cluster (BinTree<string> &prcd, map<string,Procesador> &prcd_data);

    /**
     * @brief Modificadora que actualiza la estructura de procesadores.
     * \pre <em>cierto</em>
     * \post Siento el procesador <em>id_prcd</em> que quiere modificar es un procesador sin auxiliares, el resultado es que la estructura nueva que quiere insertar que anexa a la estructura de procesadores <em>prcd</em> en la posicición del procesador <em>id_prcd</em>
     * \coste Linear en el peor caso
    */
    static bool i_modificar_cluster(BinTree<string> &prcd, map<string, Procesador>&prcd_data, const string &id_prcd, const Cluster &c2);

    /**
     * @brief Modificadora que actualiza el estado de un procesador en concreto
     * \pre <em>cierto</em>
     * \post Intenta colocar el proceso <em>Job</em> a un procesesador más apropiado dentro del conjunto de procesadores existente del <em>prcd</em>. Habrá el resultado cuando <em>id_prcd</em> ha sido modificado respecto su valor inicial, y se selecionará el procesador más optimo cuando existe empates entre procesadores mirando sus capacidad de la memoria libre <em>free_memory</em>, el hueco más ajustado <em>gap</em>, la profundidad que este situado más cerca de la raíz estructura entera y izqueirda <em>depth</em>.
     * \coste Linear 
    */
    void i_enviar_procesos_cluster(const Proceso &Job, const BinTree<string>& prcd, string& id_prcd, int &free_memory, int &gap, int &depth, int counter);

    /**
     * @brief Escriptura de Cluster que imprime la estructura de procesadores por preorden
     * \pre <em>cierto</em>
     * \post Imprime la estructura de procesadores por preorden
     * \coste Linear respecto el tamaño de la estructura de procesadores
    */
    static void i_imprimir_estructura_cluster (BinTree<string>& prcd);



    public:
    //Constructoras

    /** @brief Creadora de Cluster
    * \pre <em>cierto</em>
    * \post El resultado es un Cluster vacío sin procesadores.
    * \coste Constante
    */
    Cluster();

    //Modificadoras

    /** @brief Modificadora del Cluster que configura un nuevo cluster.
     * \pre <em>cierto</em>
     * \post Devuleve la estructura de procesadores del cluster por el orden creciente del id de procesadores
    */
    void configurar_cluster (); 

    /** @brief Modificadora del Cluster que agrega un proceso al procesador indicado.
     * \pre id_prcd es el id de un procesadro en concreto y Job es un instante del módulo Proceso
     * \post Se añade un proceso al procesado con el id <em>id_prcd</em> cuando no se ha producido ningun tipo de errores. En caso contrario, se imprime un error que puede ser por la inexistencia del procesador que queremos dar la alta o porque tal procesador ya contiene un instante de Proceso con el mismo id que queremos dar la alta 
     * \coste Logaritmico
    */
    void alta_proceso_procesador (const string &id_prcd, Proceso Job);
   
    /** @brief Modificadora del Cluster que elimina un proceso del procesador indicado.
     * \pre id_prcd es el id de un procesadro en concreto y id_job corresponde al id del proceso que queremos eliminar
     * \post Se añade un proceso en el procesado del id indicado en el caso que no se ha producido ningun tipo de errores. En caso contrario,  se imprime un error que puede ser por la inexistencia del procesador que queremos dar la alta o porque tal procesador ya contiene un instante de Proceso con el mismo id que queremos dar la alta 
     * \coste Logaritmico
    */
    void baja_proceso_procesador (const string &id_prcd, int id_job);

    /** @brief Modificadora del Cluster que actualiza la estructura de procesadores en la posición de procesador indicada.
     * \pre Siento <em>id_prcd</em> es el id de procesador que quiere modificar, <em>c2</em> representa la estructura nueva que quiere insertar en la modificación
     * \post Devuelve la estructura de procesadores modificada si el procesador introducido es una hoja, es decir que es un vertice sin vertices auxiliares.
     * \coste Lineal
    */
   void modificar_cluster (const string& id_prcd, const Cluster& c2);

    /** @brief Modificadora del Cluster.
     * \pre Siento <em>t</em> el valor de tiempo que queremos actualizar a todos los procesos existentes en la estructura de procesadores
     * \post Accelera el tiempo restante de todo los procesos existentes de la estructura de procesadores, si el tiempo restante 't' es mayor que el tiempo que queda un procesador, este procesador se queda eliminado y liberamos su espacio
     * \coste Linear que depende el tamaño de todos los procesos existentes
    */
    void avanzar_tiempo (int t);

    /** @brief Modificadora del Cluster que compacta la memoria de un procesador indicado
    * \pre <em>cierto</em>
    * \post En el caso cuando el procesador del id mencionado existe en la estructura de los procesadores, compacta la memoria de este procesador tratado. Es decir sin dejar huecos, sin solaparse y respetando el orden inicial.
    * \coste Lineal que depende el tamaño de todos los procesos existentes de la estructura de procesadores.
    */
    void compactar_memoria_procesador (const string &id_prcd);

    /** @brief Modificadora del Cluster que compacta las memorias de todos los procesadores existente del cluster
    * \pre <em>cierto</em>
    * \post En este caso, compactan la memoria de todos los procesadores existentes en la estructura de procesadores.
    * \coste lineal que dependerá el tamaño de la estructura de procesadores.
    */
    void compactar_memoria_cluster ();

    /** @brief Modificadora del Cluster que envia un proceso a un procesador del Cluster, se escoge el procesador que cumple la mayor criterios posibles por el orden. Se fija primero los procesadores con el hueco más ajustado, si existe empates, el que tenga mayor memoria libre. Si el empate persiste, el que se encuentra más cercano a la raíz de la estructura de procesadores y si todavía persiste el empate, el procesador que está más a la izquierda.
    * \pre <em>cierto</em>
    * \post El resultado es true cuando ha podido colocar el proceso a un procesador que cumple todos los criterios anteriores.
    * \coste Lineal que depende el tamaño de la estructura de los procesadores
    */
   bool enviar_procesos_cluster(const Proceso& proceso); 

   // Lectura y escriptura

    /** @brief Escriptura del Cluster que imprime todos los procesadores del clúster por orden creciente de identificador.
     * \pre <em>cierto></em>
     * \post Se imprime el listado de procesadores del cluster por el orden creciente de identificador
     * \coste Lineal que depende el tamaño del conjunto de procesadores y los procesos correspondientes.
    */    
    void imprimir_procesadores_cluster ();

    /** @brief Escriptura del Cluster que imprime la estructura de procesadores de Cluster.
     * \pre <em>cierto</em>
     * \post se imprime la estructura de procesadores en forma creciente
     * \coste Lineal que depende el tamaño de la estructura de procesadores
    */
    void imprimir_estructura_cluster ();

    /** @brief Escriptura del Cluster que imprime el estado de un procesador particular.
     * \pre <em>cierto</em>
     * \post se imprime los procesos de dicho profcesador por orden creciente de primera posición de memoria, incluyendo dicha posición y sus datos detallados 
     * \coste Logaritmico 
    */
   void imprimir_procesador (const string &id_prcd);
};
#endif