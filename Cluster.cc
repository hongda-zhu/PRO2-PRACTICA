#include "Cluster.hh"

Cluster::Cluster() {}

void Cluster::set_cluster(BinTree<string> &prcd, map<string,Procesador> &prcd_data) {
    string id_prc;
    cin >> id_prc;
    if (id_prc != "*") {
        int memory;
        cin >> memory;
        prcd_data.insert(make_pair(id_prc,Procesador(id_prc, memory)));
        BinTree <string> left, right;
        set_cluster(left, prcd_data);
        set_cluster(right, prcd_data);
        prcd = BinTree <string> (id_prc,left,right);
    }
}

void Cluster::configurar_cluster() {
    prcd_data.clear();
    set_cluster(prcd, prcd_data);
}


void Cluster::get_cluster_structure(BinTree<string>& prcd) const {
    if (not prcd.empty()) {
        cout << '(' << prcd.value();
        BinTree<string> left = prcd.left();
        BinTree<string> right = prcd.right();
        get_cluster_structure(left);
        get_cluster_structure(right);
        cout << ')';
    } else {
        cout << ' ';
    }
}

void Cluster::imprimir_estructura_cluster(){
    get_cluster_structure(prcd);
    cout << endl;
};

void Cluster::imprimir_procesadores_cluster() {
    for(map<string, Procesador>:: iterator it = prcd_data.begin(); it != prcd_data.end(); ++it) {
        cout << it->first << endl;
        it->second.imprimir_procesos();
    }
}

void Cluster::alta_proceso_procesador(const string id_prcd, Proceso Job) {
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it != prcd_data.end()) {
        it->second.alta_proceso_procesador(Job);
    } else cout <<  "error: no existe procesador" << endl;
}

void Cluster::baja_proceso_procesador(const string id_prcd, int id_job) {
    map<string, Procesador>::iterator it = prcd_data.find(id_prcd);
    if (it != prcd_data.end()) {
        it->second.baja_proceso_procesador(id_job);
    } else cout <<  "error: no existe procesador" << endl;
}

void Cluster:: avanzar_tiempo (int t) {
    map<string, Procesador>:: iterator it = prcd_data.begin();
    while(it != prcd_data.end()) {
        it->second.avanzar_tiempo(t);
        ++it;
    }
}

void Cluster::imprimir_procesador(string id_procesador) {
    map<string, Procesador>:: iterator it = prcd_data.find(id_procesador);
    if(it != prcd_data.end()) {    
        it->second.imprimir_procesos();
    } else cout << "error: no existe procesador" << endl;
}