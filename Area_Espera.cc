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

void Area_Espera::enviar_procesos_cluster(int n, Cluster &c) {
    int i = 0;
    map<string,Prioridad>::iterator it = prioridades_data.begin();
    while (i < n and it != prioridades_data.end()) {
        int j = 0;
        int size = it -> second.retrieve_jobs_size();
        pair<int, int> info_prioridad = it -> second.retrieve_info();
        while (i < n and j < size) {
            Proceso temp = it -> second.retrieve_job();
            bool is_sent = c.enviar_procesos_cluster(temp);
            if (is_sent) {
                ++i;
                ++info_prioridad.first;
            }
            else {
                it -> second.alta_proceso_espera(temp);
                ++info_prioridad.second;
            }
            ++j;
        }
        it -> second.update_prioridad(info_prioridad.first,info_prioridad.second);
        ++it;
    }
}