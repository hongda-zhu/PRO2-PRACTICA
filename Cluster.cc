#include "Cluster.hh"

Cluster::Cluster() {}

void Cluster::set_cluster(BinTree<string>& prc) {
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
        prc = BinTree<string>(prc_id, left, right);
    }
}

void Cluster::configurar_cluster() {
    prc_data = map<string, Procesador> ();
    set_cluster(prc);
}


void Cluster::get_cluster_structure(BinTree<string>& prc) const {
    if (not prc.empty()) {
        cout << '(' << prc.value();
        BinTree<string> left = prc.left();
        BinTree<string> right = prc.right();
        get_cluster_structure(left);
        get_cluster_structure(right);
        cout << ')';
    } else {
        cout << ' ';
    }
}

void Cluster::imprimir_estructura_cluster(){
    get_cluster_structure(prc);
} ;