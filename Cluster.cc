#include "Cluster.hh"

Cluster::Cluster() {}

void Cluster::set_cluster(BinTree<string>& prcd) {
    string prc_id;
    cin >> prc_id;
    if (prc_id != "*") {
        int prc_memory;
        cin >> prc_memory;
        Procesador elem(prc_id, prc_memory);
        prc_data.insert(make_pair(prc_id, elem));
        BinTree<string>left, right;
        set_cluster(left);
        set_cluster(right);
        prcd = BinTree<string>(prc_id, left, right);
    }
}

void Cluster::configurar_cluster() {
    prc_data = map<string, Procesador> ();
    set_cluster(prcd);
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

void Cluster::imprimir_procesadores_cluster()const{
    map<string, Procesador>:: const_iterator it = prc_data.begin();
    while(it != prc_data.end()) {
        cout << it->first << endl;
        ++it;
    }
}