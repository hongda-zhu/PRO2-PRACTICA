/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

    /*El métode que he empleat pricipalment per simular la memoria es utilitzar procesos amb id -1, que simbolitzen els blocs ocupats. 
    Per tant, en el segon map de direcció-proces hi haura procesos amb identificador -1.
    */

Procesador::Procesador(const string &id_prcd, int memory) {
    this->id_prcd = id_prcd;
    this->memory = memory;
    max_space = memory;
    free_space = memory;
    memory_data.insert(make_pair(memory, set<int>{0}));
}

void Procesador::alta_proceso_procesador(Proceso& Job) {
    int id_job = Job.retrieve_id();
    int size_job = Job.retrieve_size();
    map<int, set<int>>:: iterator it = memory_data.lower_bound(size_job);
    if (prcd_job_data.find(id_job) != prcd_job_data.end()) {
        // Encuentra que ya existe un proceso con el mismo id en el procesador
        cout << "error: ya existe proceso" << endl;
        return;
    }
    else if (memory_data.empty() or size_job > max_space or it == memory_data.end()) {
        // Encuentra que ya no hay suficiente espacio para el proceso
        cout << "error: no cabe proceso" << endl;
        return;
    } else {
        int remain_memory_space = it -> first;
        int initial_memory_position = *it -> second.begin();
        prcd_job_data.insert(make_pair(id_job, initial_memory_position));
        prcd_memory_data.insert(make_pair(initial_memory_position, Job));
        if(remain_memory_space*2 > free_space) memory_data.erase(it);
        if (remain_memory_space > size_job) {
            memory_data.insert(make_pair(remain_memory_space - size_job, set<int>{initial_memory_position + size_job}));
        }
        if(memory_data.empty()) max_space = 0;
        else if (remain_memory_space == max_space) max_space = memory_data.rbegin() -> first;
    }
}