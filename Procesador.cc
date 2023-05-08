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
    seg_data.insert(make_pair(memory, set<int>{0}));
}

void Procesador::alta_proceso_procesador(Proceso& Job) {
    int id_job = Job.retrieve_id();
    int size_job = Job.retrieve_size();
    map<int, set<int>>:: iterator it = seg_data.lower_bound(size_job);
    if (prcd_job_memory.find(id_job) != prcd_job_memory.end()) {
        // Encuentra que ya existe un proceso con el mismo id en el procesador
        cout << "error: ya existe proceso" << endl;
        return;
    }
    else if (seg_data.empty() or size_job > max_space or it == seg_data.end()) {
        // Encuentra que ya no hay suficiente espacio para el proceso
        cout << "error: no cabe proceso" << endl;
        return;
    } else {
        int remain_memory_space = it -> first;
        // start_pos = position where the next elem will start
        int start_pos = *it -> second.begin();
        prcd_job_memory.insert(make_pair(id_job, start_pos));
        prcd_memory_job.insert(make_pair(start_pos, Job));

        // case 1: erase the entire remain_memory_space
        int it_size = it->second.size();
        if(remain_memory_space*2 > free_space or it_size == 1) seg_data.erase(it);
        else it -> second.erase(it -> second.begin());
        free_space -= remain_memory_space;

        // when the remain_memory_space is not equal or smaller than job's size, we refresh the memory structure
        if (remain_memory_space > size_job) {
            // second parameter of verify_seg will be true when there's not same key in seg_data, viceversa;
            pair <map<int, set<int>>::iterator, bool> verify_seg;
            verify_seg = seg_data.insert(make_pair(remain_memory_space - size_job, set<int>{start_pos + size_job}));
            if (not verify_seg.second) verify_seg.first -> second.insert(start_pos + size_job);
            free_space += remain_memory_space - size_job;
        }

        // update max_space
        // case 1: when seg_data has no instance, then there is no space in seg_data
        if(seg_data.empty()) max_space = 0;
        // case 2: when old rms = ms, means the max shall be equal to the new rms
        else if (remain_memory_space == max_space) max_space = seg_data.rbegin() -> first;
    }
}

void Procesador:: baja_proceso_procesador(int id_job) {
    // iterator from the <id_job, memory_position>
    map<int, int>:: iterator it_job_memory = prcd_job_memory.find(id_job);
    if (it_job_memory == prcd_job_memory.end()) {
        cout << "error: no existe proceso" << endl;
    } else {
        // grab the data of job that we want to eliminate
        int job_seg_pos = it_job_memory -> second; // memory_position where this job start in the memory of procesador;

        map<int, Proceso> ::iterator it_memory_job = prcd_memory_job.find(job_seg_pos); // grab the iterator by using .find() method using the memory_position of this job, map<memory_position, Job>

        int size_job = it_memory_job -> second.retrieve_size(); // grab size of reletate job that we want to eliminate

        // delete the job 
        prcd_job_memory.erase(it_job_memory); // eliminate job in the <id_job, memory_position>;
        it_memory_job = prcd_memory_job.erase(it_memory_job);
        free_space += size_job;
        
        // iterator for spaces map
        map<int, set<int>> :: iterator it_seg;
        
        // checking if the right size has segmentation or not 
        int r_seg = 0;
        if (it_memory_job == prcd_memory_job.end()) {
            // case 1: while deleted job is situate in the last pos of memory, then we have all the rest of space of the right size as our new segmentation
            r_seg = memory - job_seg_pos - size_job;
        } else if (it_memory_job -> first != job_seg_pos + size_job) {
            // case 2: while deleted job is no situate in the last pos and it creates blocks
            r_seg = it_memory_job -> first - job_seg_pos - size_job;
        }

        // while segmentation exist, we recalculate the pos in memory data; 
        if (r_seg != 0) {
            it_seg = seg_data.find(r_seg);
            if(r_seg*2 > free_space or it_seg -> second.size() == 1) seg_data.erase(it_seg);
            else it_seg -> second.erase(job_seg_pos + size_job);
            // add the release space into the right size block 
            size_job += r_seg;
        }

        int l_seg = 0;
        if (job_seg_pos == 0){
            // case 1: while delete job is situate in the first pos of memory
            // then no segmentation is in the left side
            l_seg = job_seg_pos;
            job_seg_pos = 0;
        } else {
            // case 2: if deletejob is no in the first pos;
            // then we have a new segmentation which is starts from the end of the nerby left side job 
            --it_memory_job;
            int aux_pos = it_memory_job -> first;
            int aux_size = it_memory_job -> second.retrieve_size();
            l_seg = job_seg_pos - aux_pos - aux_size;
            if (l_seg != 0) {
                // case 3: while --it is not the first item, then we have to calculate the seg
                job_seg_pos = aux_pos + aux_size;
            }
        }

        // while segmentation exist, we recalculate the pos in memory data;
        if (l_seg != 0) {
            it_seg = seg_data.find(l_seg);
            if(r_seg*2 > free_space or it_seg -> second.size() == 1) seg_data.erase(it_seg);
            else it_seg -> second.erase(job_seg_pos + size_job);
            // add the release space into the right size block
            size_job += l_seg;
        }

        if (size_job > max_space) max_space = size_job;
        // second parameter of verify_seg will be true when there's not same key in seg_data, viceversa;
        pair<map<int, set<int>>::iterator, bool> verify_seg;
        verify_seg = seg_data.insert(make_pair(size_job, set<int>{job_seg_pos}));
        // add new segmentation position of the same amount of size
        if (not verify_seg.second) verify_seg.first -> second.insert(job_seg_pos);
    }
}

void Procesador:: avanzar_tiempo (int t) {

}

void Procesador:: imprimir_procesos() {
    map<int, Proceso>:: iterator it = prcd_memory_job.begin();
    while (it != prcd_memory_job.end()) {
        int id_job = it -> second.retrieve_id();
        int size_job = it -> second.retrieve_size();
        int time_job = it -> second.retrieve_time();
        if (time_job != -1) cout << it -> first << ' ' << id_job << ' ' <<
         size_job << ' ' << time_job << endl;
        ++it;
    }
}