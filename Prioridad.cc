/** @file Prioridad.cc
    @brief  Codigo de la clase Prioridad
*/

#include "Prioridad.hh"

Prioridad:: Prioridad() {
    /**
     * los valores inicial del n_aceptados y n_rejected son 0
    */
    n_accepted = 0;
    n_rejected = 0;
}

void Prioridad:: retrieve_jobs () const {
    /*
    Inv it apunta a un proceso entre la posición begin() y end() de la lista de procesos del parametro implicito
    */
    // Cota: dist(it, jobs.end())
    for (list<Proceso>:: const_iterator it = jobs.begin(); it != jobs.end(); ++it) it -> print();
    cout << n_accepted << ' ' << n_rejected << endl;
    // Post: (it == jobs.end()) todos los procesos han sido tratados
}

void Prioridad:: alta_proceso_espera (Proceso &Job) {   
    // Verificamos la existencia del proceso agregar en el listado de procesos del parametro implicito
    int id_job = Job.retrieve_id();
    set <int> ::const_iterator it = id_jobs.lower_bound(id_job);
    if (it != id_jobs.end() and *it == id_job) {
        // Error 1: el proceso que quiere insertar ya existe en el parametro implicito
        cout << "error: ya existe proceso" << endl;
    } 
    else {
        id_jobs.insert(it, id_job);
        jobs.insert(jobs.end(), Job);
    }
}


int Prioridad:: retrieve_jobs_size () const {
    // Devuleve el tamaño del listado de procesos del parametro implicito
    return id_jobs.size();
}

pair <int, int> Prioridad:: retrieve_info() const {
    // Devuleve el n_aceptados y n_rechazados en formato de pair
    pair <int, int> result; 
    result.first = n_accepted;
    result.second = n_rejected;
    return result;
}

Proceso Prioridad:: retrieve_job () {
    // Devolvemos el proceso más antiguo de la lista de procesos
    list<Proceso>:: iterator it = jobs.begin();
    Proceso res = *it;
    int id_process = it -> retrieve_id();
    jobs.erase(it);
    id_jobs.erase(id_process);;
    return res;
};

void Prioridad:: update_prioridad(const int accepted, const int rejected) {
    // Actualizamos el n_acptados y n_rechazados
    n_accepted = accepted;
    n_rejected = rejected;
}