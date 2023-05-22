/** @file Area_Espera.cc
    @brief Codigo de la clase Area_Espera
*/

#include "Area_Espera.hh"

Area_Espera::Area_Espera() {
}

void Area_Espera:: alta_prioridad(const string &id_prioridad) {
    /* Verifica la existencia de la prioridad que quiere agregar en el parametro implicito
    */
    map<string, Prioridad>:: const_iterator it = prioridades_data.find(id_prioridad);
    if(it != prioridades_data.end()) {
        /* Error 1: La prioridad indicada ya existe en el parametro implicito
        */
        cout << "error: ya existe prioridad" << endl;
    } else prioridades_data.insert(make_pair(id_prioridad, Prioridad()));
}

void Area_Espera:: baja_prioridad(const string &id_prioridad) {
    /* Verifica la existencia de la prioridad que quiere suprimir en el parametro implicito
    */
    map<string, Prioridad>:: iterator it = prioridades_data.find(id_prioridad);
    if(it == prioridades_data.end()) {
        /* Error 1: La prioridad indicada no existe en el parametro implicito
        */
        cout << "error: no existe prioridad" << endl;
    } else if (it->second.retrieve_jobs_size() != 0)  {
        /* Error 2: La prioridad indicada contiene procesos pendientes
        */
        cout << "error: prioridad con procesos" << endl;
    } else {
        prioridades_data.erase(it);
    };
}

void Area_Espera:: alta_proceso_espera (const string &id_prioridad, Proceso &Job) {
    /* Verifica la existencia de la prioridad que quiere agregar el nuevo proceso en el parametro implicito
    */
    map<string, Prioridad>:: iterator it = prioridades_data.find(id_prioridad);
    if(it == prioridades_data.end()) {;
        /* Error 1: La prioridad indicada no existe en el parametro implicito
        */
        cout << "error: no existe prioridad" << endl;   
    } else it->second.alta_proceso_espera(Job);
}

void Area_Espera:: imprimir_prioridad(const string id_prioridad) const {
    /* Verifica la existencia de la prioridad que quiere imprimir las informaciones en el parametro implicito
    */
    map<string, Prioridad>:: const_iterator it = prioridades_data.find(id_prioridad);
    if(it == prioridades_data.end()) {
        /* Error 1: La prioridad indicada no existe en el parametro implicito
        */
        cout << "error: no existe prioridad" << endl;
    } else it->second.retrieve_procesos();
}

void Area_Espera:: imprimir_area_espera () const {
    /* Se imprime las informaciones de todas las prioridades existentes del parametro implicito
    */
   /* Inv: it apunta desde la posición begin() hasta la posición end().
   */
    map<string, Prioridad>::const_iterator it = prioridades_data.begin();
    // Cota: it = la posición end()
    while(it != prioridades_data.end()) {
        cout << it->first << endl;
        it->second.retrieve_procesos();
        ++it;
    }
}

void Area_Espera::enviar_procesos_cluster(const int& n, Cluster &c) {
    /* 
    Aplicamos dos bucles while para hacer la iteración: 
    La primera iteración nos sirve para actualizar los numeros de envios aceptados y de envios rechazados.
    La segunda iteración nos sirve para comprobar el estado del envío tal que cuando el estado del envío es true, quiere decir que hemos dado de alta correctamente el proceso que ha enviado, sino volvemos a insertar el proceso como si fuese nuevo a la misma prioridad;
    */

    /*
    Inv: 
    i = el contador de los procesos aceptados respect el n 
    j = el contador de los procesos existentes de la prioridad que se está tratando
    it = la posición de las prioridades que está situado en el parametro implicito, que comienza desde el begin() hasta el end() en el caso extremo
    size = la cantidad del procesos que tiene en una prioridad;
    info_prioridad = Pair<int n_aceptados, int n_rechazados> 
        info_prioridad.first = los numeros totales de procesos aceptados de la prioridad tratada
        info_prioridad.second = los numeros totales de procesos rechazados de la prioridad tratada
    0 <= i <= n
    0 <= j <= size
    */
    int i = 0;
    map<string,Prioridad>::iterator it = prioridades_data.begin();
    // Cota : n - i e it = prioridades_data.end()
    while (i < n and it != prioridades_data.end()) {
        int j = 0;
        int size = it -> second.retrieve_jobs_size();
        pair<int, int> info_prioridad = it -> second.retrieve_info();
        while (i < n and j < size) {
            // Devolvemos el proceso más antiguo de la prioridad
            Proceso temp = it -> second.retrieve_job();
            bool is_sent = c.enviar_procesos_cluster(temp);
            // is_sent == true cuando el proceso se ha enviado correctamente
            if (is_sent) {
                ++i;
                ++info_prioridad.first;
            }
            else {
                // si is_sent == false, entonces el proceso no se ha enviado correctamente, volvemos a agregar el proceso a la area de espera
                it -> second.alta_proceso_espera(temp);
                ++info_prioridad.second;
            }
            ++j;
        }
        /*
        Post :
        1. (i == n): se ha enviado correctamente n procesos 
        2. (j == size): todos los procesos de esta prioridad ha sido enviado una vez
        */
        it -> second.update_prioridad(info_prioridad.first,info_prioridad.second);
        ++it;
    }
    /*
    Post: 
    1. (i == n): se ha enviado correctamente n procesos
    2. (it == prioridades.end()): los procesos de todas las prioridades del parametro implicito han sido tratados 
    */
}