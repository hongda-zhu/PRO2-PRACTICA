#include "Area_Espera.hh"

Area_Espera:: Area_Espera() {}

void Area_Espera:: alta_prioridad(string id_prioridad) {
    map<string, Prioridad>:: iterator it = prioridades_data.find(id_prioridad);
    if(it != prioridades_data.end()) {
        cout << "error: ya existe prioridad" << endl;
    } else prioridades_data.insert(make_pair(id_prioridad, Prioridad()));
}

void Area_Espera:: baja_prioridad(string id_prioridad) {
    map<string, Prioridad>:: iterator it = prioridades_data.find(id_prioridad);
    if(it == prioridades_data.end()) {
        cout << "error: no existe prioridad" << endl;
    } else if (it->second.retrieve_jobs_size() != 0)  {
        cout << "error: prioridad con procesos" << endl;
    } else {
        prioridades_data.erase(it);
    };
}

void Area_Espera:: imprimir_area_espera () const {
    map<string, Prioridad>::const_iterator it = prioridades_data.begin();
    while(it != prioridades_data.end()) {
        cout << it->first << endl;
        it->second.retrieve_procesos();
        ++it;
    }
}

void Area_Espera:: alta_proceso_espera (const string &id_prioridad, Proceso &Job) {
    map<string, Prioridad>:: iterator it = prioridades_data.find(id_prioridad);
    if(it != prioridades_data.end()) {;
        it->second.alta_proceso_espera(Job);
    } else cout << "error: no existe prioridad" << endl;
}

void Area_Espera:: imprimir_prioridad(string id_prioridad) const {
    map<string, Prioridad>:: const_iterator it = prioridades_data.find(id_prioridad);
    if(it != prioridades_data.end()) {
        it->second.retrieve_procesos();
    } else cout << "error: no existe prioridad" << endl;
}