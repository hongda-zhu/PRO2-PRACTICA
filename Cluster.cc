  
/** @file Cluster.cc
    @brief Codigo de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster() {
}

void Cluster::i_configurar_cluster(BinTree<string> &prcd, map<string,Procesador> &prcd_data) {
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
    prcd_data.clear();
    i_configurar_cluster(prcd, prcd_data);
}

void Cluster::i_imprimir_estructura_cluster(BinTree<string>& prcd) {
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
    i_imprimir_estructura_cluster(prcd);
    cout << endl;
};

void Cluster::modificar_cluster(const string& id_prcd, const Cluster& c2) {
    map<string, Procesador>:: iterator it = prcd_data.find(id_prcd);
    if (it == prcd_data.end())  cout << "error: no existe procesador" << endl;
    else if (it -> second.not_empty()) cout << "error: procesador con procesos" << endl;
    else {
        bool is_modified = i_modificar_cluster(prcd, prcd_data, id_prcd, c2);
        if (not is_modified) cout << "error: procesador con auxiliares" << endl;
    };
}

bool Cluster::i_modificar_cluster(BinTree<string> &prcd, map<string, Procesador>&prcd_data, const string &id_prcd, const Cluster &c2) {
    bool res = false;
    if (prcd.empty()) res = false;
    // caso base 1 : si encontramos el procesador y tal procesador contiene un procesador auxiliar, entonces devolvemos false 
    else if (prcd.value() == id_prcd and (not (prcd.left().empty() and prcd.right().empty()))) res = false;
    // caso base 2: si hemos pasado al caso uno, esto quiere decir el id que hemos encontrado es una hoja, entonces eliminamos el procesador que queremos consultar y añadimos el nuevo procesador;
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
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it != prcd_data.end()) {
        it->second.alta_proceso_procesador(Job);
    } else cout << "error: no existe procesador" << endl;
}

void Cluster::baja_proceso_procesador(const string &id_prcd, int id_job) {
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it != prcd_data.end()) {
        it->second.baja_proceso_procesador(id_job);
    } else cout << "error: no existe procesador" << endl;
}


void Cluster::avanzar_tiempo (int t) {
    map<string, Procesador>:: iterator it = prcd_data.begin();
    while(it != prcd_data.end()) {
        it->second.avanzar_tiempo(t);
        ++it;
    }
}

void Cluster::compactar_memoria_procesador (const string &id_prcd) {
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it == prcd_data.end()) cout << "error: no existe procesador" << endl;
    else it -> second.compactar_memoria_procesador();
}
void Cluster::compactar_memoria_cluster() {
    for (map<string,Procesador>::iterator it = prcd_data.begin(); it != prcd_data.end(); ++it)
        it -> second.compactar_memoria_procesador();
}

bool Cluster:: enviar_procesos_cluster(const Proceso &Job) {
    bool res;
    string id_prcd = " ";
    int free_memory = 0;
    int depth = 0;
    int gap = 0;
    i_enviar_procesos_cluster(Job, prcd, id_prcd, free_memory, depth, gap, 0);
    if (id_prcd != " ") {
        prcd_data.find(id_prcd) -> second.alta_proceso_procesador(Job);
        res = true;
    }
    else res = false;
    return res;
}

void Cluster:: i_enviar_procesos_cluster(const Proceso &Job, const BinTree<string>& prcd, string& id_prcd, int &free_memory, int &gap, int &depth, int counter) {
    if (not prcd.empty()) {
        string temp_id_prcd = prcd.value();
        map<string, Procesador>:: iterator it = prcd_data.find(temp_id_prcd);
        // chequeamos que no existe el mismo proceso en la memoria del procesador
        bool exist_job = it -> second.exist_job(Job.retrieve_id());
        if (not exist_job) {
            // chequeamos si existe el hueco más ajustado, y existe nos devuelve el hueco, si no existe,  saltamos este nodo
            int temp_gap = it -> second.exist_fit(Job.retrieve_size());
            if (temp_gap != -1) {
                // 1. comparamos el hueco del procesador que estamos tratando es más ajustado respecto con el procesador que hemos registrado
                int temp_free_memory = it -> second.retrieve_free_memory();
                if (gap == 0 or temp_gap > gap) {
                    // 1.1 si cumple la condición, sustituimos el procesador registrado respecto al procesador que estamos tratando
                    gap = temp_gap;
                    free_memory = temp_free_memory;
                    id_prcd = temp_id_prcd;
                    depth = counter;
                } 
                else if (gap == temp_gap) {
                    // 2. chequeamos quien tiene mayor memoria libre
                    if (temp_free_memory > free_memory) {
                        free_memory = temp_free_memory;
                        id_prcd = temp_id_prcd;
                        depth = counter;
                    }
                    else if (temp_free_memory == free_memory) {
                    // 3. si tiene la misma memoria libre, chequeamos quien tiene está más cercano al nodo principal
                        if (depth > counter) {
                            id_prcd = temp_id_prcd;
                            depth = counter;
                        }
                    }
                }
            }
        }
        i_enviar_procesos_cluster(Job, prcd.left(), id_prcd, free_memory, gap, depth, ++counter);
        i_enviar_procesos_cluster(Job, prcd.right(), id_prcd, free_memory, gap, depth, ++counter);
    }
}


void Cluster::imprimir_procesadores_cluster() {
    for(map<string, Procesador>:: iterator it = prcd_data.begin(); it != prcd_data.end(); ++it) {
        cout << it->first << endl;
        it->second.imprimir_procesos();
    }
}

void Cluster::imprimir_procesador(const string& id_prcd) {
    map<string, Procesador>:: iterator it = prcd_data.find(id_prcd);
    if(it != prcd_data.end()) {    
        it->second.imprimir_procesos();
    } else cout << "error: no existe procesador" << endl;
}