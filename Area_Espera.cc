/** @file Area_Espera.cc
    @brief Codigo de la clase Area_Espera
*/

#include "Area_Espera.hh"

Area_Espera::Area_Espera() {
}

void Area_Espera:: alta_prioridad(const string &id_prioridad) {
    map<string, Prioridad>:: const_iterator it = prioridades_data.find(id_prioridad);
    if(it != prioridades_data.end()) {
        cout << "error: ya existe prioridad" << endl;
    } else prioridades_data.insert(make_pair(id_prioridad, Prioridad()));
}

void Area_Espera:: baja_prioridad(const string &id_prioridad) {
    map<string, Prioridad>:: iterator it = prioridades_data.find(id_prioridad);
    if(it == prioridades_data.end()) {
        cout << "error: no existe prioridad" << endl;
    } else if (it->second.retrieve_jobs_size() != 0)  {
        cout << "error: prioridad con procesos" << endl;
    } else {
        prioridades_data.erase(it);
    };
}

void Area_Espera:: alta_proceso_espera (const string &id_prioridad, Proceso &Job) {
    map<string, Prioridad>:: iterator it = prioridades_data.find(id_prioridad);
    if(it != prioridades_data.end()) {;
        it->second.alta_proceso_espera(Job);
    } else cout << "error: no existe prioridad" << endl;
}

void Area_Espera:: imprimir_prioridad(const string id_prioridad) const {
    map<string, Prioridad>:: const_iterator it = prioridades_data.find(id_prioridad);
    if(it != prioridades_data.end()) {
        it->second.retrieve_procesos();
    } else cout << "error: no existe prioridad" << endl;
}

void Area_Espera:: imprimir_area_espera () const {
    map<string, Prioridad>::const_iterator it = prioridades_data.begin();
    while(it != prioridades_data.end()) {
        cout << it->first << endl;
        it->second.retrieve_procesos();
        ++it;
    }
}

void Area_Espera:: enviar_procesos_cluster (int& n, Cluster&c) {
// enviar los procesos más antiguos por el orden de prioridad dos for
    // cota 1: se acaba el procedimiento cuando hemos colocado n procesos
    // for 1: for prioriodad por el orden
    for (map <string, Prioridad>:: iterator it = prioridades_data.begin(); it != prioridades_data.end() and (n > 0); ++it) {
        int n_accepted = it -> second.retrieve_accepted();
        int n_rejected = it -> second.retrieve_rejected();
        int size = it -> second.retrieve_jobs_size();
        // for 2: los procesos de tal prioridad, cuando termina se va al siguiente prioridad
        // cota 2: se acaba el procedimiento cuando ya no hay procesos pendientes
        // cota 3: se acaba el procedimiento cuando los que se queden pendientes se hayan colocado sin éxito == cuando i se alcanza el size
        for (int i = 0; i < size and (n > 0); ++i) {
            Proceso p = it -> second.retrieve_job();
            bool is_colocated = c.enviar_procesos_cluster(p);
            if (is_colocated) {  
            // si un proceso no se ha podido colocar, vuelve a su lista de la prioridad como si fuese un proceso nuevo.
                it -> second.alta_proceso_espera(p);
                ++n_rejected;
                --n;
            } else {
                ++n_accepted;
            }
        }
    } 
}