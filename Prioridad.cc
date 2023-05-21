#include "Prioridad.hh"

Prioridad:: Prioridad() {
    n_accepted = 0;
    n_rejected = 0;
}

void Prioridad:: retrieve_procesos () const {
    for (list<Proceso>:: const_iterator it = jobs.begin(); it != jobs.end(); ++it) it -> print();
    cout << n_accepted << ' ' << n_rejected << endl;
}

void Prioridad:: alta_proceso_espera (Proceso &Job) {
    int id_job = Job.retrieve_id();
    set <int> ::const_iterator it = id_jobs.lower_bound(id_job);
    if (it != id_jobs.end() and *it == id_job) cout << "error: ya existe proceso" << endl; 
    else {
        id_jobs.insert(it, id_job);
        jobs.insert(jobs.end(), Job);
    }
}


int Prioridad:: retrieve_jobs_size () const {
    return id_jobs.size();
}

int Prioridad:: retrieve_accepted () const {
    return n_accepted;
}

int Prioridad:: retrieve_rejected () const {
    return n_rejected;
}

Proceso Prioridad:: retrieve_job () {
    list<Proceso>:: iterator it = jobs.begin();
    Proceso res = *it;
    int id_process = it -> retrieve_id();
    jobs.erase(it);
    id_jobs.erase(id_process);
    return res;
};

void Prioridad:: update_prioridad(const int rejected, const int accepted) {
    n_rejected = rejected;
    n_accepted = accepted;
}