  
/** @file Cluster.cc
    @brief Codigo de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster() {
}

void Cluster::i_configurar_cluster(BinTree<string> &prcd, map<string,Procesador> &prcd_data) {
    // Inicializa el cluster por preorden
    // El único caso base es que nos encuentra en el id_prcd un '*' tal que indica que es un nodo vacío para la estructura de los procesadores que estamos contruyendo
    string id_prcd;
    cin >> id_prcd;
    if (id_prcd != "*") {
        int memory;
        cin >> memory;
        prcd_data.insert(make_pair(id_prcd,Procesador(id_prcd, memory)));
        BinTree <string> left, right;
        i_configurar_cluster(left, prcd_data);
        i_configurar_cluster(right, prcd_data);
        prcd = BinTree <string> (id_prcd,left,right);
    }
}

void Cluster::configurar_cluster() {
    // resetea la estructura de procesadores 
    prcd_data.clear();
    i_configurar_cluster(prcd, prcd_data);
}

void Cluster::i_imprimir_estructura_cluster(BinTree<string>& prcd) {
    // Se imprime el cluster por preorden
    // El caso base es que no se encuentre un nodo vacío, es decir que el hueco que estamos revisando tenga un valor que representa el id del procesador.
    if (not prcd.empty()) {
        cout << '(' << prcd.value();
        BinTree<string> left = prcd.left();
        BinTree<string> right = prcd.right();
        i_imprimir_estructura_cluster(left);
        i_imprimir_estructura_cluster(right);
        cout << ')';
    } else {
        cout << ' ';
    }
}

void Cluster::imprimir_estructura_cluster() {
    // invoca a la funcion recursiva imersiva
    i_imprimir_estructura_cluster(prcd);
    cout << endl;
};

void Cluster::modificar_cluster(const string& id_prcd, const Cluster& c2) {
    // Invocamos a la funcion recurvsiva immersiva después de chequear posibles errores.
    map<string, Procesador>:: iterator it = prcd_data.find(id_prcd);
    // error 1: el procesador que queremos modificafr no existe
    if (it == prcd_data.end())  cout << "error: no existe procesador" << endl;
    // error 2: el procesador que queremos modificafr tiene procesos pendientes
    else if (it -> second.not_empty()) cout << "error: procesador con procesos" << endl;
    else {
        bool is_modified = i_modificar_cluster(prcd, prcd_data, id_prcd, c2);
        // error 3: el procesador que queremos modificafr tiene procesadores auxiliares
        if (not is_modified) cout << "error: procesador con auxiliares" << endl;
    };
}

bool Cluster::i_modificar_cluster(BinTree<string> &prcd, map<string, Procesador>&prcd_data, const string &id_prcd, const Cluster &c2) {
    // Busca la posición de procesador que queremos modificar en la estructura de procesadores
    // res = result, result es falso cuando el procesador que queremos modificar tiene procesadores auxiliares y es true cuando hemos cambiado su valor correctamente
    bool res = false;
    // caso base 1: si estamos apuntando un nodo vacio sin procesador
    if (prcd.empty()) res = false;
    // caso base 2 : si encontramos el procesador y tal procesador contiene un procesador auxiliar, entonces devolvemos false 
    else if (prcd.value() == id_prcd and (not (prcd.left().empty() and prcd.right().empty()))) res = false;
    // caso base 3: si hemos pasado al caso uno, esto quiere decir el id que hemos encontrado es una hoja, entonces eliminamos el procesador que queremos consultar y añadimos el nuevo procesador;
    else if (prcd.value() == id_prcd) {
        // modificamos el nodo en el árbol original
        prcd = c2.prcd;
        // insertamos los elementos nuevo del nodo que queremos modificar al prcd_data
        prcd_data.erase(id_prcd);
        prcd_data.insert(c2.prcd_data.begin(), c2.prcd_data.end());
        res = true;
    } else {
        // left
        BinTree<string>left = prcd.left();
        bool is_left = i_modificar_cluster(left, prcd_data, id_prcd, c2);
        // si hemos encontrado el nodo por la parte izquierda
        if (is_left) {
            // modificamos el árbol 
            prcd = BinTree<string>(prcd.value(), left, prcd.right());
            res = true;
        } else {
            // right
            BinTree<string>right = prcd.right();
            bool is_right = i_modificar_cluster(right, prcd_data, id_prcd, c2);
            // si hemos encontrado el nodo por por la parte derecha
            if (is_right) {
                prcd = BinTree<string>(prcd.value(), prcd.left(), right);
                res = true;
            } 
        }
    }
    return res;
}

void Cluster::alta_proceso_procesador(const string &id_prcd, Proceso Job) {
    // Verificamos la existencia del procesador que queremos agregar el proceso
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it == prcd_data.end()) {
        // Error 1: no existe procesador
        cout << "error: no existe procesador" << endl;
    } else it->second.alta_proceso_procesador(Job);
}

void Cluster::baja_proceso_procesador(const string &id_prcd, int id_job) {
    // Verificamos la existencia del procesador que queremos eliminar el proceso
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it == prcd_data.end()) {
        // Error 1: no existe procesador
        cout << "error: no existe procesador" << endl;
    } else it->second.baja_proceso_procesador(id_job);
}


void Cluster::avanzar_tiempo (int t) {
    // it = la posición de los procesadores que está situado en el conjunto de procesadores en el parametro implicito, que comienza desde el begin() hasta el end(). 
    // Cota: dist(it, prcd_data.end())
    map<string, Procesador>:: iterator it = prcd_data.begin();
    while(it != prcd_data.end()) {
        it->second.avanzar_tiempo(t);
        ++it;
    }
    // Post: 
    // (it == prcd_data.end()): se ha avanzado el tiempo de los procesos de todos procesadores existentes de la estructura de procesadores
}

void Cluster::compactar_memoria_procesador (const string &id_prcd) {
    // Verificamos la existencia del procesador que queremos compactar la memoria
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it == prcd_data.end()) {
        // Error 1: no existe procesador
        cout << "error: no existe procesador" << endl;
    }
    else it -> second.compactar_memoria_procesador();
}

void Cluster::compactar_memoria_cluster() {
    // Compactamos todos los procesadores existentes de la estructura del procesador
    for (map<string,Procesador>::iterator it = prcd_data.begin(); it != prcd_data.end(); ++it)
        it -> second.compactar_memoria_procesador();
    //Post: 
    // (it == prcd_data.end()): la memoria todos los procesadores de la estructura de procesadores han sido compactados
}

bool Cluster::enviar_procesos_cluster (const Proceso &job) {
    // Invocamos a la funcion recurvsiva immersiva antes de chequear los posibles errores.
    /*
    Inv:
    cuando el proceso ha sido enviado correctamente
    id_prcd representa el id de procesador donde se ha enviado el proce
    depth representa la profundidad del procesador respect la estructura de procesadores
    gap representa el hueco que se situará el procesador respecto la raíz de la estructura de procesadores
    free_memory representa la memoria libre del procesador selecionado
    u el 0 del parametro refiere al contador de la profundidad del procesador que se trata en cada llamada imersiva 
    */

    string id_prcd = "null"; 
    int depth = 0;
    int gap = 0; 
    int free_memory = 0;
    i_enviar_procesos_cluster(job, prcd, id_prcd, free_memory,gap,depth, 0);
    // si el id_prcd ha sido cambiado, quiere decir que hemos encontrado el procesador que cumple los criterios mencionado
    if (id_prcd != "null") {
        prcd_data.find(id_prcd) -> second.alta_proceso_procesador(job);
        return true;
    }
    return false;
}

void Cluster::i_enviar_procesos_cluster (const Proceso &job, const BinTree<string> &prcd, string &id_prcd, int &free_memory, int &gap, int &depth, int counter) {
    // llamada recursiva en forma preorden cumpliendo los criterios mencionados
    // El caso base sería cuando el nodo estamos tratando no es un nodo vacío
    if (not prcd.empty()) {
        string temp_id_prcd = prcd.value();
        map<string,Procesador>::iterator it = prcd_data.find(temp_id_prcd);
        bool exist_job = it -> second.exist_job(job.retrieve_id());
        if (not exist_job){
            // 1. comparamos el hueco del procesador que estamos tratando es más ajustado respecto con el procesador que hemos registrado
            if (it -> second.fit_job(job.retrieve_size())) {
                int temp_free_memory = it -> second.retrieve_free_memory();
                int temp_gap = it -> second.best_fit(job.retrieve_size());
                if (gap == 0 or gap > temp_gap) {
                // 1.1 si cumple la condición, sustituimos el procesador registrado respecto al procesador que estamos tratando
                    gap = temp_gap;
                    free_memory = temp_free_memory;
                    id_prcd = temp_id_prcd;
                    depth = counter;
                } else if (temp_gap == gap) {
                    // 2. chequeamos quien tiene mayor memoria libre
                    if (temp_free_memory > free_memory) {
                        free_memory = temp_free_memory;
                        id_prcd = temp_id_prcd;
                        depth = counter;
                    } else if (temp_free_memory == free_memory) {
                        // 3. si tiene la misma memoria libre, chequeamos quien tiene está más cercano al nodo principal
                        if (depth > counter) {
                            id_prcd = temp_id_prcd;
                            depth = counter;
                        }
                    }
                }
            }
            // al recorrer la estructura en preorden y tener los criterios anteriores cubiertos, el criterio de "procesador de más izquierda" se cumple automaticamente
        }

        // llamada recursiva en preorden, incrementando el contador cada vez +1
        i_enviar_procesos_cluster(job, prcd.left(), id_prcd, free_memory, gap, depth, ++counter);
        i_enviar_procesos_cluster(job, prcd.right(), id_prcd, free_memory, gap, depth, ++counter);
    }
}


void Cluster::imprimir_procesadores_cluster() {
    // it = la posición de los procesadores que está situado en el conjunto de procesadores en el parametro implicito, que comienza desde el begin() hasta el end(). 
    for(map<string, Procesador>:: iterator it = prcd_data.begin(); it != prcd_data.end(); ++it) {
        cout << it->first << endl;
        it->second.imprimir_procesos();
    }
    // Post: (it == prcd_data.end()) se ha imprimido todos los procesadores del conjunto de procesadores
}

void Cluster::imprimir_procesador(const string& id_prcd) {
    // Verificamos la existencia del procesador que queremos imprimir
    map<string, Procesador>:: iterator it = prcd_data.find(id_prcd);
    if(it == prcd_data.end()) {
        // Error 1: no existe procesador
        cout << "error: no existe procesador" << endl;
    } else it->second.imprimir_procesos();
}