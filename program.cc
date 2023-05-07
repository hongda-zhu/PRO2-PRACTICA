/** @mainpage
 * 
 *  El programa principal se encuentra en el program.cc.
 * 
    Atendiendo a los tipos de datos sugeridos en el enunciado, necesitaremos un
    módulo para representar Procesador, donde el conjunto de ellos da lugar
    a otro modulo llamado Cluster. Por otro lado tenemos una Area_Espera, donde
    habrá Proceso, un nuevo modulo que se define como la tarea que realiza los Clusters,
    cada procesos estará contenido en una Prioridad, el conjunto de procesos. El conjunto de
    Prioridades forma la Area_Espera.
 */

/** @file program.cc
    @brief Programa princial.

    Suponemos que los datos leídos son siempre correctos, ya que no
    incluimos combrobaciones al respecto.  Para acceder a las opciones
    disponibles usaremos comandos.
*/

#include "Cluster.hh" // redundante, pero necesario
#include "Proceso.hh" // redundante, pero necesario
#include "Procesador.hh" // redundante, pero necesario
#include "Area_Espera.hh"

int main () {

    Cluster c;
    c.configurar_cluster();

    Area_Espera a;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string id_prioridad;
        cin >> id_prioridad;
        a.alta_prioridad(id_prioridad);
    }

    string command;
    cin >> command;
    while (command != "fin") {
        cout << '#' << command;
        if (command == "cc" or command == "configurar_cluster") {
            cout << endl;
            c.configurar_cluster();
            cout << endl;
        }
        else if (command == "ap" or command == "alta_prioridad"){
            string id_prioridad;
            cin >> id_prioridad;

            cout << " " << id_prioridad << endl;
            if (not a.exist_prioridad(id_prioridad)) cout << "error: ya existe prioridad";
            else a.alta_prioridad(id_prioridad);
        }
    //     else if (command == "bp" or command == "baja_prioridad"){
    //         string id_prioridad;
    //         cin >> id_prioridad;

    //         cout << " " << id_prioridad << endl;
    //         a.baja_prioridad(id_prioridad);
    //     }
        else if (command == "ape" or command == "alta_proceso_espera"){
            string id_prioridad;
            cin >> id_prioridad;

            Proceso job;
            // job.leer();

            cout << " " << id_prioridad << " " << job.id << endl;

            // a.alta_proceso_espera(id_prioridad, job);
        }
    //     else if (command == "app" or command == "alta_proceso_procesador"){
    //         string id_procesador;
    //         cin >> id_procesador;

    //         Proceso job;
    //         job.leer();

    //         cout << " " << id_procesador << " " << job.id << endl;

    //         c.alta_proceso_procesador(id_procesador, job);
    //     }
    //     else if (command == "bpp" or command == "baja_proceso_procesador"){

    //         string id_procesador;
    //         cin >> id_procesador;

    //         int id_job;
    //         cin >> id_job;

    //         cout << " " << id_procesador << " " << id_job << endl;
    //         c.baja_proceso_procesador(id_procesador, id_job);
    //     }
    //     else if (command == "at" or command == "avanzar_tiempo"){
    //         int t;
    //         cin >> t;

    //         cout << " " << t << endl;
    //         c.avanzar_tiempo(t);
    //     }
    //     else if (command == "ipri" or command == "imprimir_prioridad"){
    //         string id_prioridad;
    //         cin >> id_prioridad;

    //         cout << " " << id_prioridad << endl;

    //         a.imprimir_prioridad(id_prioridad);
    //     }
        else if (command == "ia" or command == "imprimir_area_espera"){
            cout << endl;
            a.imprimir_area_espera();
        }
    //     else if (command == "ipro" or command == "imprimir_procesador"){
    //         string id_procesador;
    //         cin >> id_procesador;
    //         cout << " " << id_procesador << endl;
    //         c.imprimir_procesador(id_procesador);
    //     }
        else if (command == "ipc" or command == "imprimir_procesadores_cluster"){
            cout << endl;
            c.imprimir_procesadores_cluster();
        }
        else if (command == "iec" or command == "imprimir_estructura_cluster"){
            cout << endl;
            c.imprimir_estructura_cluster();
        }
        cin >> command;
    }
}