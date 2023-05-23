/** @file Procesador.hh
    @brief  Especificación de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#endif

/** @class Procesador
    @brief Representa la información y las operaciones asociadas a un procesador en concreto. 
    
    Sus operaciones son una creadora del instante de procesador que require el id y la memoria,  unas operaciones modifcadoras como insertar un nuevo proceso al procesador o eliminar un proceso existente del procesador, avanzar tiempo de todos los procesos del procesador, compactar la memoria del parametro implicito. Además también tiene operaciones consultoras que mira el estado de los parametros implicios. Por el último, dispone operaciones de lectura y escriptura para leer los datos de un procesador y escribir los procesos de estos.
    
*/
class Procesador {

    // Descripción: contiene un cojunto de procesos y dispone las operaciones correspondiente.

    private:
    
    /*
    Un Procesador se representa mediante una lista de huecos de memoria libres, una lista de identificadores de procesos y la posición que ocupa y una lista de la posición inicial de la memoria y su conjunto correspondiente de Proceso que ocupa esa posición.
    */

    /** @brief id de procesador*/
    string id_prcd;

    /** @brief la memoria total del procesador*/
    int memory;
    /** @brief el tamaño del hueco más grande del procesador*/
    int total_memory;
    /** @brief la memoria libre de procesadorr*/
    int free_memory; 

    /** @brief Esta lista nos guarda los bloques de la memoria libre, el primer int indica el tamano del hueco y el segundo set nos indica por donde guarda la posicion de memoria por donde se empieza el hueco, el ordenamiento de esta lista es creciente respecto el tamaño del hueco*/
    map <int, set<int>> gap_data;

    /** @brief Esta lista nos guarda el id de proceso en el primer int y la posición de memoria por donde empieza en el segundo int, el ordenamiento de esta lista es creciente respecto el id de los procesos */
    map<int, int> prcd_job_memory;

    /** @brief Esta lista nos guarda la posición de memoria en el primer int y el proceso correspondiente en el segundo parametro, el ordenamiento de esta lista es creciente respecto la posición inicial en la memoria de cada proceso */
    map<int,Proceso> prcd_memory_job;


    /**
     * @brief Operacion modificadora de huecos libres
     * \pre Existe un hueco en el procesador con el tamaño <em>size</em> y empieza en la posición <em>start</em>
     * \post Se ha insertado correctamente este hueco
     * \coste Logaritmico
    */
    void insert_gap (int size, int start);

    /**
     * @brief Operacion modificadora de huecos libres
     * \pre Existe un hueco en el procesador con el tamaño <em>size</em> y empieza en la posición <em>start</em>
     * \post Se ha elimminado correctamente este hueco
     * \coste Logaritmico
    */
    void erase_gap (int size, int start);
    
    public:

    //Constructoras

    /** @brief Creadora de Procesador
     * \pre Requiere el id de procesador <em>id_prcd</em> y su tamano de la memoria <em>memory</em>
     * \post Devuelve un instante de procesador con su id y su tamano de memoria
     * \coste Constante
    */
    Procesador(const string &id_prcd, int memory);

    //Modificadoras
    /** @brief Escriptura del Procesador que añade un proceso al procesador tratado.
     * \pre Haya suficiente espacio
     * \post Se añade un proceso en el procesado del id indicado o imprime un error porque ya existe un proceso con el mismo id en el procesador.
     * \coste Logaritmico
    */ 
    void alta_proceso_procesador (const Proceso& Job);

    /** @brief Escriptura del Procesador.
     * \pre <em>cierto</em>
     * \post Se elimina un proceso en el procesado del id indicado o imprime un error porque ya existe un proceso con el mismo id en el procesador.
     * \coste Logaritmico
    */ 
    void baja_proceso_procesador (const int id_job);

    /** @brief Modificadora del Procesador.
     * \pre t >= 0
     * \post Se accelera todos el tiempo de todo los procesos del procesador, si el tiempo restante 't' es mayor que el tiempo que queda un procesador, este procesador se queda eliminado y liberamos su espacio
     * \coste Lineal que depende el tamaño de las listas relacionados
    */
    void avanzar_tiempo(int t);

    /** @brief Modificadora del Procesador que compacta la memoria del procesador tratado
    * \pre <em>cierto</em>
    * \post En el caso cuando el procesador del id existe en el cluster, se devuelve la memoria de este procesador de forma compactado, es decir sin dejar huecos, sin solaparse y respetando el orden inicial.
    * \coste Lineal 
    */
    void compactar_memoria_procesador();

    //Consultora

    /**
     * @brief Consultora del Procesador que verifica el estado de ocupación procesos del procesador
     * \pre <em>cierto</em>
     * \post devuelve true cuando el procesador si que contiene procesos y viceversa
     * \coste Constante;
    */ 
    bool not_empty() const;

    /**
     * @brief Consultora del Procesador que verifica la existencia del proceso en el procesador tratado
     * \pre <em>cierto</em>
     * \post devuelve true cuando el procesador si que contiene procesos y viceversa
     * \coste Logaritmico;
    */ 
    bool exist_job (const int id_job);

    /**
     * @brief Consultora del Procesador que verifica si existe el hueco optimo para el proceso que queremos insertar en el procesador tratado
     * \pre <em>cierto</em>
     * \post devuelve la posición inicial de la memoria cuando si que hay hueco optimo, sino existe el hueco devuleve el resultado -1.
     * \coste Logaritmico;
    */ 
    int best_fit (const int size_job); 

    /**
     * @brief Consultora del Procesador que verifica si existe el hueco para el proceso
     * \pre <em>cierto</em>
     * \post devuelve true cuando hay hueco para el proceso.
     * \coste Constante;
    */ 
    bool fit_job(const int size_job);


    //Lectura y escriptura
    /** @brief Escriptura del Procesador.
     * \pre <em>cierto</em>
     * \post devuleve la memoria libre
     * \coste Constante
    */ 
    int retrieve_free_memory () const;

    /** @brief Escriptura del Procesador.
     * \pre <em>cierto</em>
     * \post imprime el id, tamano y el tiempo restante de los procesos del procesador indicado
     * \coste Constante
    */ 
    void imprimir_procesos() const;
};
#endif