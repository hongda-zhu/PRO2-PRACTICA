/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#include <vector>
#endif

/** @class Procesador
    @brief FALTA EXPLICACION
*/
class Procesador {

    private:
    
    int max_space;
    int memory;
    int free_space;
    /*Este map nos guarda los bloques de la memoria libre, el primer int indica el tamano del bloque y el segundo set nos indica por donde guarda la posicion de memoria por donde se empieza el bloque*/
    map <int, set<int>> seg_data;

    /* Este map nos guarda el id de proceso en el primer int y la posición de memoria por donde empieza en el segundo int */
    map<int, int> prcd_job_memory;

    /* Este map nos guarda la posición de memoria en el primer int y el proceso correspondiente en el segundo parametro.*/
    map<int,Proceso> prcd_memory_job;

    void erase_seg (int size, int start);
    void insert_seg (int size, int start);

    public:

    string id_prcd;

    //Constructoras

    /** @brief Creadora de Procesador
     * \pre Requiere el id de procesador y su tamano de la memoria
     * \post Devuelve un instante de procesador con su id y su tamano de memoria
    */
    Procesador(const string &id_prcd, int memory);

    /** @brief Creadora de Procesador
     * \pre <em>cierto<em>
     * \post Devuelve un instante de procesador vacio
    */
    Procesador();

    //Modificadoras
    void alta_proceso_procesador (const Proceso& Job);
    /** @brief Escriptura del Procesador.
     * \pre instante de proceso válido
     * \post Se añade un proceso en el procesado del id indicado o imprime un error porque ya existe un proceso con el mismo id en el procesador.
    */ 
    void baja_proceso_procesador (int id_job);
    /** @brief Escriptura del Procesador.
     * \pre <em>cierto<em>
     * \post Se elimina un proceso en el procesado del id indicado o imprime un error porque ya existe un proceso con el mismo id en el procesador.
    */ 

    void avanzar_tiempo(int t);
    /** @brief Modificadora del Procesador.
     * \pre <t >= 0
     * \post Se accelera todos el tiempo de todo los procesadores pendientes, si el tiempo restante 't' es mayor que el tiempo que queda un procesador, este procesador se queda eliminado y liberamos su espacio
    */ 

    //Consultora

    //Lectura y escriptura
    void imprimir_procesos() const;
    /** @brief Escriptura del Procesador.
     * \pre <em>cierto<em>
     * \post imprime el id, tamano y el tiempo restante de los procesos del procesador indicado
    */ 


};
#endif