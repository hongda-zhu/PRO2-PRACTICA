/** @mainpage
 * Fichero principal
 */

/** @file program.cc
    @brief Programa princial.
*/

#include "Cluster.hh"
#include "Proceso.hh"
#include "Procesador.hh"
#include "Area_Espera.hh"

int main () {

    Cluster c1;
    c1.configurar_cluster();

    Area_Espera ae;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string id_prioridad;
        cin >> id_prioridad;
        ae.alta_prioridad(id_prioridad);
    }

    string command;
    cin >> command;
    while (command != "fin") {
        if (command == "cc" or command == "configurar_cluster") {
            cout << "#" << command << endl;
            c1.configurar_cluster();
        }
        else if (command == "ap" or command == "alta_prioridad"){
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << command << " " << id_prioridad << endl;

            ae.alta_prioridad(id_prioridad);
        }
        else if (command == "bp" or command == "baja_prioridad"){
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << command << " " << id_prioridad << endl;

            ae.baja_prioridad(id_prioridad);
        }
        else if (command == "ape" or command == "alta_proceso_espera"){
            string id_prioridad;
            cin >> id_prioridad;
            Proceso job;
            job.read();
            cout << "#" << command << " " << id_prioridad << " " << job.retrieve_id() << endl;

            ae.alta_proceso_espera(id_prioridad, job);
        }
        else if (command == "app" or command == "alta_proceso_procesador"){
            string id_procesador;
            cin >> id_procesador;
            Proceso job;
            job.read();
            cout << "#" << command << " " << id_procesador << " " << job.retrieve_id() << endl;

            c1.alta_proceso_procesador(id_procesador, job);
        }
        else if (command == "bpp" or command == "baja_proceso_procesador"){
            string id_procesador;
            cin >> id_procesador;
            int id_job;
            cin >> id_job;
            cout << "#" << command << " " << id_procesador << " " << id_job << endl;
            
            c1.baja_proceso_procesador(id_procesador, id_job);
        }
        else if (command == "at" or command == "avanzar_tiempo"){
            int t;
            cin >> t;
            cout << "#" << command << " " << t << endl;

            c1.avanzar_tiempo(t);
        }
        else if (command == "ipri" or command == "imprimir_prioridad"){
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << command << " " << id_prioridad << endl;

            ae.imprimir_prioridad(id_prioridad);
        }
        else if (command == "iae" or command == "imprimir_area_espera"){
            cout << "#" << command << endl;  
            ae.imprimir_area_espera();
        }
        else if (command == "ipro" or command == "imprimir_procesador"){
            string id_procesador;
            cin >> id_procesador;
            cout << "#" << command << " " << id_procesador << endl;
            c1.imprimir_procesador(id_procesador);
        }
        else if (command == "ipc" or command == "imprimir_procesadores_cluster"){
            cout << "#" << command << endl;
            c1.imprimir_procesadores_cluster();
        }
        else if (command == "iec" or command == "imprimir_estructura_cluster"){
            cout << "#" << command << endl;
            c1.imprimir_estructura_cluster();
        }
        cin >> command;
    }
}