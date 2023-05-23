/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador(const string &id_prcd, int memory) {
    /* Inicializa el procesador vacio, iniciando la memoria total y la memoria libre como la memoria, solo habrá un hueco en la memoria que será la memoria total*/
    this->memory = memory;
    this->id_prcd = id_prcd;
    total_memory = memory;
    free_memory = memory;
    gap_data[memory] = {0};
}

void Procesador::insert_gap(int size, int start) {
    // Buscamos el hueco de la memoria libre respecto el tamaño(size) que estamos introduciendo, si tal hueco de dicho tamaño ya existe, creamos en el set una nueva posición inicial en ese hueco, sino creamos un nuevo hueco iniciando la posición de la memoria.
    map<int, set<int>>::iterator it = gap_data.lower_bound(size);
    if (it != gap_data.end() and it->first == size) {
        it->second.insert(start);
    } else gap_data.insert(it, make_pair(size, set<int>{start}));
    free_memory += size;
}

void Procesador::erase_gap(int size, int start_pos) {
    // Buscamos el hueco de la memoria libre respecto el tamaño(size) que estamos introduciendo. Si el hueco que queremos eliminar es el único hueco existente, eliminamos el hueco. Sino, eliminamos el set de la posición de memoria por donde empieza el hueco.
    map<int, set<int>>::iterator it = gap_data.find(size);
    it -> second.erase(start_pos);
    if (it-> second.empty()) gap_data.erase(it);
    free_memory -= size;
}

void Procesador::alta_proceso_procesador(const Proceso &Job) {
    int size_job = Job.retrieve_size();
    int id_job = Job.retrieve_id();
    // Comprovaciones de los errores, vemos si hay proceso relevante en la memoria del procesador
    map <int,int>::const_iterator it_job_memory = prcd_job_memory.lower_bound(id_job);
    if (it_job_memory != prcd_job_memory.end() and it_job_memory -> first == id_job) {
        // Error 1: ya existe el proceso con el mismo identificador
        cout << "error: ya existe proceso" << endl;
    } 
    else if (total_memory < size_job) {
        // Error 2: No hay suficiente memoria para insertar este proceso
        cout << "error: no cabe proceso" << endl;
    }
    else {
        // buscamos el hueco de la memoria para este proceso que queremos insertar
        map <int, set<int>>::iterator it = gap_data.lower_bound(size_job);
        int remain_space = it -> first;
        int start = *it -> second.begin();
        // actualizamos las dos listas añadiendo el nuevo proceso
        prcd_job_memory.insert(it_job_memory, make_pair(id_job, start));
        prcd_memory_job.insert(make_pair(start, Job)); 

        // reajustamos el hueco
        erase_gap(remain_space, start);
        if (remain_space > size_job) insert_gap (remain_space - size_job, start + size_job);

        // Actualizamos el espacio total
        if (gap_data.empty()) total_memory = 0;
        else if (remain_space == total_memory) total_memory = gap_data.rbegin() -> first;
    }
}

void Procesador::baja_proceso_procesador(const int id_job) {
    /* Verificamos la existencia del proceso que queremos eliminar, en el caso afirmativo, eliminamos este proceso y reajustamos los huecos de la memoria del procesador*/

    map<int,int>::iterator it_job_memory = prcd_job_memory.find(id_job);
    // Error 1: no existe el proceso que queremos eliminar
    if (it_job_memory == prcd_job_memory.end()) cout << "error: no existe proceso" << endl;
    else {
        int start_pos = it_job_memory -> second;
        map<int,Proceso>::iterator it_memory_job = prcd_memory_job.find(start_pos);
        int size_job = it_memory_job -> second.retrieve_size();

        // eliminamos el proceso en las dos listas
        prcd_job_memory.erase(it_job_memory);
        it_memory_job = prcd_memory_job.erase(it_memory_job);

        // comprovamos si la eliminación influye el hueco por la parte derecha de la posición del proceso eliminado
        int r_gap = 0;
        // Si no hay proceso por la parte derecha, la posición del único hueco ajustado de la parte derecha empieza contar desde la posición del proceso eliminado hasta la última posición de la lista. En caso contrario, el hueco que tendremos será desde la posición inicial del proceso eliminado hasta la posición inicial del siguiente proceso.
        if (it_memory_job == prcd_memory_job.end()) {
            r_gap = memory - start_pos - size_job;
        } else r_gap = it_memory_job -> first - start_pos - size_job;

        if (r_gap != 0) {
            // si los dos procesos no son consecutivos, existe espacio libre entre ellos.
            erase_gap(r_gap, start_pos + size_job);
            size_job += r_gap;
        }

        // comprovamos si la eliminación influye el hueco por la parte izquierda de la posición del proceso eliminado
        // si no hay más procesos en la parte izquieda, el nuevo hueco empezará contar desde la posición 0 hasta la última posición del proceso, sino la posición inicial del hueco creada se empezará contar desde la última posición del último proceso que se encuentra en la parte izquierda hasta última posición del proceso eliminado.
        int l_gap = 0;
        if (it_memory_job == prcd_memory_job.begin()) {
            l_gap = start_pos;
            start_pos = 0;
        } else {
            --it_memory_job;
            int pos_job = it_memory_job ->first;
            int size_job = it_memory_job -> second.retrieve_size();
            l_gap = start_pos - pos_job - size_job;
            if (l_gap != 0) {
                start_pos = pos_job + size_job;
            }
        }
        // si los dos procesos no son consecutivos, existe espacio libre entre ellos.
        if (l_gap != 0) {
            erase_gap(l_gap,start_pos);
            size_job += l_gap;
        }
        // ajustamos las posiciones de los huecos si existen, y los insertamos en la lista de huecos.
        if (size_job > total_memory) total_memory = size_job;
        insert_gap(size_job,start_pos);
    }
}

void Procesador::avanzar_tiempo(int t) {
    /**
     * Aplicamos un bucle para actualizar el estado de tiempo restante de cada proceso del procesador, esta implementación se destaca en la posibilidad que acumular los huecos que hay que liberar cuando los procesos tratados son posiblemente eliminados en caso cuando su tiempo restante después de la operación sean 0 o menor que 0.
    */
    map<int,Proceso>::iterator it = prcd_memory_job.begin();
    // size == tamaño del hueco creado por la eliminación del proceso
    int size = 0;
    int start_pos = 0;
    int last_pos = 0;
    bool consecutive = false;
    while (it != prcd_memory_job.end()) {
        it -> second.actualizar_proceso(t);

        int pos_job = it ->first;
        int time_job = it -> second.retrieve_time();
        int size_job = it -> second.retrieve_size();

        // existen 4 casos una vez cuando hemos actualizado el tiempo del proceso
        if (time_job <= 0){
            // caso 1: si el proceso ya ha acabado, lo eliminamos y actualizamos los datos. Si el proceso anterior también ha sido eliminado, se acumula el tamaño del hueco libre
            if (not consecutive) start_pos = last_pos;

            size += pos_job + size_job - last_pos;
            int gap = pos_job - last_pos;
            if (gap != 0) erase_gap(gap,last_pos);
            prcd_job_memory.erase(it -> second.retrieve_id());
            last_pos = pos_job + size_job;
            it = prcd_memory_job.erase(it);
            consecutive = true;
        } else if (size != 0){
            // caso 2: si nos encontramos un proceso que no has sido eliminado, en esta situación tendremos que registrar el hueco con toda la acumulación de espacio que hemos tenido previamente.
            int gap = pos_job - last_pos;
            if (gap != 0) {
                erase_gap(gap,last_pos);
                size += gap;
            }
            if (size > total_memory) total_memory = size;
            insert_gap(size, start_pos);
            size = 0;
            last_pos = pos_job + size_job;
            ++it;
            consecutive = false;
        } else {
            // caso 3: si el proceso no ha terminado, y no hay huecos libres, no hacemos nada en la memoria
            last_pos = pos_job + size_job;
            ++it;
        }

        // caso 4: si hemos llegado al final de la lista y tenemos un hueco, insertamos el hueco.
        if (it == prcd_memory_job.end() and size != 0) {
            int gap = memory - last_pos;
            if (gap != 0) {
                size += gap;
                erase_gap(gap,last_pos);
            }
            insert_gap(size, start_pos);
            if (size > total_memory) total_memory = size;
        }
    }
    // Post: (it == prcd_memory_job.end()) se ha actualizado correctamente todos los procesos del procesador tratado.
}

void Procesador::compactar_memoria_procesador() {
    /*
        Usaremos en esta caso dos bucles. El primer bucle se destaca a los procesos que ya estan compactados.
        El segundo bucle se enfoca a relocalizar aquellos procesos que no estan colocado correctamente.
    */
    
    // Cuando el procesador no contiene el proceso, no hacemos nada
    if (not prcd_memory_job.empty()) {
        gap_data.clear();
        map<int,Proceso> :: iterator it = prcd_memory_job.begin();
        int consecutive_pos = 0;
        int real_pos = it -> first;
        /*
            Inv: it apunta un elemento entre la posición del la lista procesador_memory_job.begin() y .end()
        */
        while (consecutive_pos == real_pos and it != prcd_memory_job.end()) {
            int size = it -> second.retrieve_size();
            consecutive_pos += size;
            real_pos = it -> first;
            ++it;
        }
        /*
        Post: 
            1. (consecutive_pos != real_pos): it ha apuntado a una procesos que no esta compactado
            2. (it == prcd_memory_job.end()): todos los procesos del procesador tratado estan compactados
        */

       /*
            Inv: it apunta un elemento entre la posición del la lista procesador_memory_job.begin() y .end()
            todos los procesos anteriores estan compactados
       */
        while (it != prcd_memory_job.end()) {
            Proceso job = it -> second;
            it = prcd_memory_job.erase(it);
            prcd_memory_job.insert(it, make_pair(consecutive_pos, job));
            prcd_job_memory[job.retrieve_id()] = consecutive_pos;
            consecutive_pos += job.retrieve_size();
        }
       /*
        Post: (it == prcd_memory_job.end()) todos los procesos del procesador tratado estan compactados
        */

        // Actualizamos la lista del hueco que tendrá un único hueco que cuenta desde memoria - posiciones acumulados hasta el final,  si la lista no está lleno previamente.
        if (consecutive_pos != memory) gap_data.insert(make_pair(memory - consecutive_pos, set<int>{consecutive_pos}));
        total_memory = memory - consecutive_pos;
    }
}

int Procesador:: retrieve_free_memory () const {
    // Devuelve la memoria libre 
    return free_memory;
}

bool Procesador::exist_job(const int id_job) {
    // Devuelve el bool que refleja la existencia del proceso insertado en el procesador tratado
    return prcd_job_memory.find(id_job) != prcd_job_memory.end();
}

bool Procesador::fit_job(const int size_job) {
    // Devuelve el bool que refleja si existe suficiente hueco en el procesador para el proceso que queremos insertar
    if(gap_data.empty()) return false;
    return size_job <= gap_data.rbegin() -> first;
}

int Procesador:: best_fit (const int size_job) {
    // res == result, que será -1 cuando no hay el hueco optimo para el proceso  
    int res;
    map <int, set<int>>:: const_iterator it = gap_data.lower_bound(size_job);
    if(it != gap_data.end()) res = it -> first;
    else res = -1;
    return res;
};
bool Procesador::not_empty() const {
    // Devuelve el bool para saber si el procesador está ocupado o no
    return prcd_job_memory.size() != 0;
}

void Procesador::imprimir_procesos() const {
    /**
     * Imprime todos los proceso del procesador tratado por el orden creciente de la posición de memoria 
    */

    // Inv: it apunta un proceso entre prcd_memory_job.begin() y end() - 1;

    for (map<int,Proceso>::const_iterator it = prcd_memory_job.begin(); it != prcd_memory_job.end(); ++it) {
        cout << it -> first << " " << it -> second.retrieve_id() << " " <<
        it -> second.retrieve_size() << " " << it -> second.retrieve_time() << endl;
    }

    // Post: (it == prcd_memory_job()) todos los procesos han sido tratados
}