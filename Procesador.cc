/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador(const string &id_prcd, int memory) {
    /*Inicialització de un procesador buit. Inicialment la memory disponible, maxima es la total
    */
    this->memory = memory;
    this->id_prcd = id_prcd;
    max_memory = memory;
    seg_data[memory] = {0};
    free_memory = memory;
}

void Procesador::insert_seg(int size, int start) {
    map<int, set<int>>::iterator it = seg_data.lower_bound(size);
    if (it != seg_data.end() and it->first == size) {
        it->second.insert(start);
    } else seg_data.insert(it, make_pair(size, set<int>{start}));
}

void Procesador::erase_seg(int size, int start_pos) {
    map<int, set<int>>::iterator it = seg_data.find(size);
    it -> second.erase(start_pos);
    if (it-> second.empty()) seg_data.erase(it);
}

void Procesador::alta_proceso_procesador(const Proceso &Job) {
    int size_job = Job.retrieve_size();
    int id_job = Job.retrieve_id();
    map <int,int>::const_iterator it_job_memory = prcd_job_memory.lower_bound(id_job);
    map <int, set<int>>::iterator it = seg_data.lower_bound(size_job);
    if (it_job_memory != prcd_job_memory.end() and it_job_memory -> first == id_job) {
        cout << "error: ya existe proceso" << endl;
    } 
    else if (max_memory < size_job) {
        cout << "error: no cabe proceso" << endl;
    }
    else {
        int remain_space = it -> first;
        int start = *it -> second.begin();
        prcd_job_memory.insert(it_job_memory, make_pair(id_job, start));
        prcd_memory_job.insert(make_pair(start, Job)); 
        erase_seg(remain_space, start);
        if (remain_space > size_job) insert_seg (remain_space - size_job, start + size_job);
        if (seg_data.empty()) max_memory = 0;
        else if (remain_space == max_memory) max_memory = seg_data.rbegin() -> first;
    }
}

void Procesador::baja_proceso_procesador(int id_job) {
    map<int,int>::iterator it_job_memory = prcd_job_memory.find(id_job);
    if (it_job_memory == prcd_job_memory.end()) cout << "error: no existe proceso" << endl;
    else {
        int start_pos = it_job_memory -> second;
        map<int,Proceso>::iterator it_memory_job = prcd_memory_job.find(start_pos);
        int size_job = it_memory_job -> second.retrieve_size();

        prcd_job_memory.erase(it_job_memory);
        it_memory_job = prcd_memory_job.erase(it_memory_job);

        // right
        int r_seg = 0;
        if (it_memory_job == prcd_memory_job.end()) {
            r_seg = memory - start_pos - size_job;
        } else r_seg = it_memory_job -> first - start_pos - size_job;
        if (r_seg != 0) {
            erase_seg(r_seg, start_pos + size_job);
            size_job += r_seg;
        }

        // left
        int l_seg = 0;
        if (it_memory_job == prcd_memory_job.begin()) {
            l_seg = start_pos;
            start_pos = 0;
        } else {
            --it_memory_job;
            int pos_job = it_memory_job ->first;
            int size_job = it_memory_job -> second.retrieve_size();
            l_seg = start_pos - pos_job - size_job;
            if (l_seg != 0) {
                start_pos = pos_job + size_job;
            }
        }
        if (l_seg != 0) {
            erase_seg(l_seg,start_pos);
            size_job += l_seg;
        }
        if (size_job > max_memory) max_memory = size_job;
        insert_seg(size_job,start_pos);
    }
}

void Procesador::avanzar_tiempo(int t) {
    map<int,Proceso>::iterator it = prcd_memory_job.begin();
    // size == seg's space
    int size = 0;
    int start_pos = 0;
    int last_pos = 0;
    bool consecutive = false;
    while (it != prcd_memory_job.end()) {
        it -> second.actualizar_proceso(t);

        int pos_job = it ->first;
        int time_job = it -> second.retrieve_time();
        int size_job = it -> second.retrieve_size();

        // 4 cases
        if (time_job <= 0){
            // if there's process that exceed time, then we have new seg's space here
            if (not consecutive) start_pos = last_pos;
            // we add space here
            size += pos_job + size_job - last_pos;
            int seg = pos_job - last_pos;
            if (seg != 0) erase_seg(seg,last_pos);
            prcd_job_memory.erase(it -> second.retrieve_id());
            last_pos = pos_job + size_job;
            it = prcd_memory_job.erase(it);
            consecutive = true;
        } else if (size != 0){
            // while the process that we are encounter now, has not exceed the time, then we have to group all the seg'space that we have been grouping from now
            int seg = pos_job - last_pos;
            if (seg != 0) {
                erase_seg(seg,last_pos);
                size += seg;
            }
            if (size > max_memory) max_memory = size;
            insert_seg(size, start_pos);
            size = 0;
            last_pos = pos_job + size_job;
            ++it;
            consecutive = false;
        } else {
            // process[it] has no exceed its time
            last_pos = pos_job + size_job;
            ++it;
        }

        // if we reach to the last process, we have to see recalculate the right size of seg if needed
        if (it == prcd_memory_job.end() and size != 0) {
            int seg = memory - last_pos;
            if (seg != 0) {
                size += seg;
                erase_seg(seg,last_pos);
            }
            insert_seg(size, start_pos);
            if (size > max_memory) max_memory = size;
        }
    }
}

void Procesador::compactar_memoria_procesador() {
    
    map <int,Proceso> new_memory_job;
    map <int,int> new_job_memory;
    map<int,Proceso> :: iterator it = prcd_memory_job.begin();
    int last_pos = 0;
    for (map<int, Proceso>:: const_iterator it = prcd_memory_job.begin(); it != prcd_memory_job.end(); ++it) {
        new_memory_job.insert(new_memory_job.end(), make_pair(last_pos, it -> second));
        new_job_memory.insert(new_job_memory.end(), make_pair(it -> second.retrieve_id(), last_pos));
        last_pos += it -> second.retrieve_size();
    }
    seg_data.clear();
    if (last_pos != memory) seg_data.insert(make_pair(memory - last_pos, set<int>{last_pos}));
    max_memory = free_memory = memory - last_pos;
    prcd_memory_job.swap(new_memory_job);
    prcd_job_memory.swap(new_job_memory);
}

int Procesador:: retrieve_free_memory () const {
    return free_memory;
}

bool Procesador::exist_job(const int id_job) {
    return prcd_job_memory.find(id_job) != prcd_job_memory.end();
}

bool Procesador::fit_job(const int size_job) {
    if(seg_data.empty()) return false;
    return size_job <= seg_data.rbegin() -> first;
}

int Procesador:: exist_fit (const int size_job) {
    // result = -1 means that tehre is no best fix
    int res;
    map <int, set<int>>:: const_iterator it = seg_data.lower_bound(size_job);
    if(it != seg_data.end()) res = it -> first;
    else res = -1;
    return res;
};
bool Procesador::not_empty() const {
    return prcd_job_memory.size() != 0;
}

void Procesador::imprimir_procesos() const {
    for (map<int,Proceso>::const_iterator it = prcd_memory_job.begin(); it != prcd_memory_job.end(); ++it) {
        cout << it -> first << " " << it -> second.retrieve_id() << " " <<
        it -> second.retrieve_size() << " " << it -> second.retrieve_time() << endl;
    }
}
