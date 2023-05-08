#include "Prioridad.hh"

Prioridad:: Prioridad() {
    n_procesos = 0;
    n_accepted = 0;
    n_rejected = 0;
}

void Prioridad:: retrieve_procesos () const {
    for (list<Proceso>::const_iterator it = jobs.begin();it != jobs.end();++it) it->print();
    cout << n_accepted << ' ' << n_rejected << endl;
}

void Prioridad:: alta_proceso_espera (Proceso &Job) {
    int id_job = Job.retrieve_id();
    if (id_jobs.find(id_job) != id_jobs.end()) cout << "error: ya existe proceso"  << endl;
    else {
        ++n_procesos;
        id_jobs.insert(id_job);
        jobs.insert(jobs.end(), Job);
    }
}


int Prioridad:: retrieve_jobs_size () const {
    return id_jobs.size();
}