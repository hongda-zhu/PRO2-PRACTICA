/** @mainpage
 * Fichero principal
 * 
 * El program se ejeucuta a partir de program.cc.
 *  Con lo que hemos visto en el enunciado, necesitaremos crear un módulo que se llama Cluster que será el conjunto de otro módulo que se llama Procesador. Por otro lado, tenemos un módulo que se llama el Area_Espera donde está formado por el conjunto de módulo de Prioridad.
 Tanto el módulo de los procesadores como el módulo de prioridades trabajan con los conjuntos de procesos que pertenece al módulo Proceso, que será el elemento principal que trataremos en esta practica.
*/

/** @file program.cc
    @brief Programa princial.
    Estamos suponiendo que los datos leídos serán siempre correctos, donde el id del módulo Prioridad y el id del módulo Procesador serán en formato string, el variable para avanzar el tiempo y los atributos del proceso serán todos en formato de integer.
*/
 
#include "Cluster.hh" // redundante, pero necesario para el diagrama
#include "Proceso.hh"  // redundante, pero necesario para el diagrama
#include "Procesador.hh" // redundante, pero necesario para el diagrama
#include "Area_Espera.hh"

int main () {

    Cluster c; // instante de Cluster
    c.configurar_cluster();

    Area_Espera ae; // instante de Cluster
    int n; // num de prioridad 
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string id_prioridad;
        cin >> id_prioridad;
        ae.alta_prioridad(id_prioridad);
    }

    string command; // comando de operación
    cin >> command;
    while (command != "fin") {
        if (command == "cc" or command == "configurar_cluster") {
            cout << '#' << command << endl;
            c.configurar_cluster();
        }
        else if (command == "mc" or command == "modificar_cluster") {
            string id_prcd;
            cin >> id_prcd;
            Cluster c2;
            c2.configurar_cluster();
            cout << '#' << command << ' ' << id_prcd <<  endl;
            c.modificar_cluster(id_prcd, c2);
        }
        else if (command == "ap" or command == "alta_prioridad"){
            string id_prioridad;
            cin >> id_prioridad;
            cout << '#' << command << ' ' << id_prioridad << endl;

            ae.alta_prioridad(id_prioridad);
        }
        else if (command == "bp" or command == "baja_prioridad"){
            string id_prioridad;
            cin >> id_prioridad;
            cout << '#' << command << ' ' << id_prioridad << endl;
            ae.baja_prioridad(id_prioridad);
        }
        else if (command == "ape" or command == "alta_proceso_espera"){
            string id_prioridad;
            cin >> id_prioridad;
            Proceso Job;
            Job.read();
            cout << '#' << command << ' ' << id_prioridad << ' ' << Job.retrieve_id() << endl;

            ae.alta_proceso_espera(id_prioridad, Job);
        }
        else if (command == "app" or command == "alta_proceso_procesador"){
            string id_prcd;
            cin >> id_prcd;
            Proceso Job;
            Job.read();
            cout << '#' << command << ' ' << id_prcd << ' ' << Job.retrieve_id() << endl;

            c.alta_proceso_procesador(id_prcd, Job);
        }
        else if (command == "bpp" or command == "baja_proceso_procesador"){
            string id_prcd;
            cin >> id_prcd;
            int id_job;
            cin >> id_job;
            cout << '#' << command << ' ' << id_prcd << ' ' << id_job << endl;
            
            c.baja_proceso_procesador(id_prcd, id_job);
        }
        else if (command == "epc" or command == "enviar_procesos_cluster") {
            int n;
            cin >> n;
            cout << '#' << command << ' ' << n << endl;
            ae.enviar_procesos_cluster(n, c);
        }
        else if (command == "at" or command == "avanzar_tiempo"){
            int t;
            cin >> t;
            cout << '#' << command << ' ' << t << endl;

            c.avanzar_tiempo(t);
        }
        else if (command == "ipri" or command == "imprimir_prioridad"){
            string id_prioridad;
            cin >> id_prioridad;
            cout << '#' << command << ' ' << id_prioridad << endl;

            ae.imprimir_prioridad(id_prioridad);
        }
        else if (command == "iae" or command == "imprimir_area_espera"){
            cout << '#' << command << endl;  
            ae.imprimir_area_espera();
        }
        else if (command == "ipro" or command == "imprimir_procesador"){
            string id_prcd;
            cin >> id_prcd;
            cout << '#' << command << ' ' << id_prcd << endl;
            c.imprimir_procesador(id_prcd);
        }
        else if (command == "ipc" or command == "imprimir_procesadores_cluster"){
            cout << '#' << command << endl;
            c.imprimir_procesadores_cluster();
        }
        else if (command == "iec" or command == "imprimir_estructura_cluster"){
            cout << '#' << command << endl;
            c.imprimir_estructura_cluster();
        }
        else if (command == "cmp" or command == "compactar_memoria_procesador"){
            string id_prcd;
            cin >> id_prcd;
            cout << '#' << command << ' ' << id_prcd <<  endl;
            c.compactar_memoria_procesador(id_prcd);
        }
        else if (command == "cmc" or command == "compactar_memoria_cluster"){
            cout << '#' << command  <<  endl;
            c.compactar_memoria_cluster();
        }
        cin >> command;
    }
}