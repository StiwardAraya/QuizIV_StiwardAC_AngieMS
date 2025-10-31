#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Arista {
    char origen;
    char destino;
    int peso;

    Arista(char o, char d, int p) : origen(o), destino(d), peso(p) {}

    bool operator<(const Arista& otra) const {
        return peso < otra.peso;
    }
};

class Grafo {
private:
    map<char, vector<pair<char, int>>> listaAdyacencia; 
    vector<Arista> aristas;
    vector<char> nodos;

public:
    Grafo() {}

    void agregarNodo(char nodo) {
        if (listaAdyacencia.find(nodo) == listaAdyacencia.end()) {
            listaAdyacencia[nodo] = vector<pair<char, int>>();
            nodos.push_back(nodo);
        }
    }

    void agregarArista(char origen, char destino, int peso) {
        agregarNodo(origen);
        agregarNodo(destino);

        listaAdyacencia[origen].push_back(make_pair(destino, peso));
        listaAdyacencia[destino].push_back(make_pair(origen, peso));

        aristas.push_back(Arista(origen, destino, peso));
    }

    vector<char> getNodos() const {
        return nodos;
    }

    vector<Arista> getAristas() const {
        return aristas;
    }

    void mostrarTablaAdyacencia() const {
        cout << "\n========================================" << endl;
        cout << "   TABLA DE ADYACENCIA DEL GRAFO" << endl;
        cout << "========================================\n" << endl;

        cout << "Nodo | Adyacentes (Nodo:Peso)" << endl;
        cout << "-----+---------------------------" << endl;

        for (const auto& par : listaAdyacencia) {
            cout << "  " << par.first << "  | ";
            for (size_t i = 0; i < par.second.size(); i++) {
                cout << par.second[i].first << ":" << par.second[i].second;
                if (i < par.second.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void dfsRecursivo(char nodo, map<char, bool>& visitado) const {
        visitado[nodo] = true;
        cout << nodo << " ";

        for (const auto& vecino : listaAdyacencia.at(nodo)) {
            if (!visitado[vecino.first]) {
                dfsRecursivo(vecino.first, visitado);
            }
        }
    }

    bool verificarConectividad() const {
        if (nodos.empty()) return false;

        map<char, bool> visitado;
        for (char nodo : nodos) {
            visitado[nodo] = false;
        }

        cout << "\n========================================" << endl;
        cout << "   VERIFICACIÓN DE CONECTIVIDAD (DFS)" << endl;
        cout << "========================================" << endl;
        cout << "Recorrido desde el nodo " << nodos[0] << ": ";

        dfsRecursivo(nodos[0], visitado);
        cout << "\n" << endl;

        for (const auto& par : visitado) {
            if (!par.second) {
                cout << "El grafo NO está conectado." << endl;
                return false;
            }
        }

        cout << "✓ El grafo está COMPLETAMENTE conectado." << endl;
        cout << "  (Todos los nodos son alcanzables)\n" << endl;
        return true;
    }

    void mostrarAristas() const {
        cout << "\n========================================" << endl;
        cout << "   TODAS LAS CONEXIONES DISPONIBLES" << endl;
        cout << "========================================" << endl;
        cout << "Conexión  |  Costo (miles $)" << endl;
        cout << "----------+-----------------" << endl;

        vector<string> mostradas;
        for (const auto& arista : aristas) {
            string clave1 = string(1, arista.origen) + "-" + string(1, arista.destino);
            string clave2 = string(1, arista.destino) + "-" + string(1, arista.origen);

            if (find(mostradas.begin(), mostradas.end(), clave1) == mostradas.end() &&
                find(mostradas.begin(), mostradas.end(), clave2) == mostradas.end()) {
                cout << "   " << arista.origen << "-" << arista.destino
                    << "     |       " << arista.peso << endl;
                mostradas.push_back(clave1);
            }
        }
        cout << endl;
    }
};

#endif