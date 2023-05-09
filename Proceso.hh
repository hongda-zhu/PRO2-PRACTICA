/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Proceso
    @brief FALTA EXPLICACION
*/
class Proceso {


    private:
    int left_time;
    int id;
    /** @brief Tamano que ocupa el proceso*/
    int size;

    public:

    //Constructoras



    Proceso();
    /** @brief Creadora de Proceso.
    * \pre <em>cierto</em>
    * \post Devuelve un instante de proceso vacio.
    */

    //Modificadora

    void actualizar_proceso (int t);
    /** @brief Modificadora de Proceso.
        * \pre <em>cierto</em>
        * \post reduce el tiempo de proceso respecto el valor t.
    */

    // Consultora
    int retrieve_id();
    /** @brief Consultora de Proceso.
    * \pre <em>cierto</em>
    * \post devuleve el id de proceso.
    */

    int retrieve_size();
    /** @brief Consultora de Proceso.
    * \pre <em>cierto</em>
    * \post devuleve el tamano que ocupa la memoria de proceso.
    */

    int retrieve_time();
    /** @brief Consultora de Proceso.
    * \pre <em>cierto</em>
    * \post devuleve el tamano que ocupa el tiempo restante de proceso.
    */

    //Lectura y escriptura´
    void read ();
    /** @brief Lectura de Proceso.
    * \pre <em>cierto</em>
    * \post lee el id, tiempo y tamano para formular el proceso.
    */

       //Lectura y escriptura
    void print() const;
    /** @brief Escriptura del Procesador.
     * \pre <em>cierto<em>
     * \post imprime el id, tamano y el tiempo restante del proceso indicado
    */ 



};

#endif