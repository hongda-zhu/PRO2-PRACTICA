/** @file Prioridad.hh
    @brief  Especificación de la clase Proceso
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Proceso
    @brief Representa la información y las operaciones relacionado del Proceso

    Sus operaciones mayoriariamente está enfocado en consultoras de las informaciones de los parametros implicitos, dispone dos operaciones de escriptura y lectura, una operación constructora y una única operación de modificadora que se actualiza el tiempo restante del proceso. 
*/
class Proceso {

    // Descripción: contiene el id, el tiempo restante y el tamaño de un proceso.

    private:
    /** @brief el tiempo restante del proceso */
    int left_time;
    /** @brief el id del proceso */
    int id;
    /** @brief el tamaño del proceso */
    int size;

    public:

    //Constructoras

    Proceso();
    /** @brief Creadora de Proceso.
    * \pre <em>cierto</em>
    * \post Devuelve un instante de proceso vacio.
    */

    //Modificadora

    /** @brief Modificadora de Proceso.
        * \pre <em>cierto</em>
        * \post reduce el tiempo de proceso respecto el valor t.
        * \coste Constante
    */
    void actualizar_proceso (int t);

    // Consultora
    /** @brief Consultora de Proceso.
        * \pre <em>cierto</em>
        * \post devuelve el id de proceso.
        * \coste Constante
    */
    int retrieve_id() const;

    /** @brief Consultora de Proceso.
        * \pre <em>cierto</em>
        * \post devuelve el tamano que ocupa la memory de proceso.
        * \coste Constante
    */
    int retrieve_size() const;

    /** @brief Consultora de Proceso.
        * \pre <em>cierto</em>
        * \post devuelve el tiempo restante de proceso.
        * \coste Constante
    */
    int retrieve_time() const;

    //Lectura y escriptura´
    /** @brief Lectura de Proceso.
        * \pre <em>cierto</em>
        * \post lee el id, tiempo y tamano para formular el proceso.
        * \coste Constante
    */
    void read ();

    /** @brief Escriptura del Procesador.
         * \pre <em>cierto</em>
         * \post imprime el id, tamano y el tiempo restante del proceso indicado
         * \coste Constante
    */ 
    void print() const;
};

#endif