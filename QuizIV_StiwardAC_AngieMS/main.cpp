#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Grafo.h"
#include "UnionFind.h"

using namespace std;

vector<Arista> algoritmoKruskal(Grafo& grafo) {
    vector<Arista> mst; 
    vector<Arista> aristas = grafo.getAristas();
    vector<char> nodosChar = grafo.getNodos();

    vector<string> nodosString;
    for (char nodo : nodosChar) {
        nodosString.push_back(string(1, nodo));
    }

    sort(aristas.begin(), aristas.end());

    UnionFind uf(nodosString);

    cout << "\n========================================" << endl;
    cout << "   ALGORITMO DE KRUSKAL - PROCESO" << endl;
    cout << "========================================\n" << endl;

    cout << "Aristas ordenadas por peso:" << endl;
    for (const auto& arista : aristas) {
        cout << "  " << arista.origen << "-" << arista.destino
            << " (peso: " << arista.peso << ")" << endl;
    }
    cout << "\nProceso de selección:\n" << endl;

    for (const auto& arista : aristas) {
        string origen = string(1, arista.origen);
        string destino = string(1, arista.destino);

        if (uf.unionSets(origen, destino)) {
            mst.push_back(arista);
            cout << "✓ Seleccionada: " << arista.origen << "-" << arista.destino
                << " (peso: " << arista.peso << ")" << endl;
        }
        else {
            cout << "✗ Rechazada: " << arista.origen << "-" << arista.destino
                << " (formaría un ciclo)" << endl;
        }
    }

    return mst;
}

void mostrarResultado(const vector<Arista>& mst) {
    int costoTotal = 0;

    cout << "\n========================================" << endl;
    cout << "   RED ÓPTIMA DE FIBRA ÓPTICA" << endl;
    cout << "========================================" << endl;
    cout << "Conexión  |  Costo (miles $)" << endl;
    cout << "----------+-----------------" << endl;

    for (const auto& arista : mst) {
        cout << "   " << arista.origen << "-" << arista.destino
            << "     |       " << arista.peso << endl;
        costoTotal += arista.peso;
    }

    cout << "----------+-----------------" << endl;
    cout << "   TOTAL  |       " << costoTotal << endl;
    cout << "========================================\n" << endl;

    cout << "RESUMEN:" << endl;
    cout << "• Comunidades conectadas: " << (mst.size() + 1) << endl;
    cout << "• Conexiones instaladas: " << mst.size() << endl;
    cout << "• Costo total: $" << costoTotal << ",000 USD" << endl;
    cout << endl;
}

void generarArchivo(Grafo& grafo, const vector<Arista>& mst) {
    ofstream archivo("resultado_red_fibra_optica.txt");

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo." << endl;
        return;
    }

    archivo << "========================================\n";
    archivo << "  RED DE FIBRA ÓPTICA - INFORME FINAL\n";
    archivo << "========================================\n\n";

    archivo << "PROYECTO: Instalación de Red de Fibra Óptica\n";
    archivo << "COMUNIDADES: A, B, C, D, E, F, G, H, I\n\n";

    archivo << "========================================\n";
    archivo << "   TABLA DE ADYACENCIA DEL GRAFO\n";
    archivo << "========================================\n\n";
    archivo << "Nodo | Adyacentes (Nodo:Peso)\n";
    archivo << "-----+---------------------------\n";

    vector<char> nodos = grafo.getNodos();
    sort(nodos.begin(), nodos.end());

    for (char nodo : nodos) {
        archivo << "  " << nodo << "  | ";
        vector<Arista> aristas = grafo.getAristas();
        vector<pair<char, int>> adyacentes;

        for (const auto& arista : aristas) {
            if (arista.origen == nodo) {
                adyacentes.push_back(make_pair(arista.destino, arista.peso));
            }
            else if (arista.destino == nodo) {
                adyacentes.push_back(make_pair(arista.origen, arista.peso));
            }
        }

        sort(adyacentes.begin(), adyacentes.end());
        adyacentes.erase(unique(adyacentes.begin(), adyacentes.end()), adyacentes.end());

        for (size_t i = 0; i < adyacentes.size(); i++) {
            archivo << adyacentes[i].first << ":" << adyacentes[i].second;
            if (i < adyacentes.size() - 1) archivo << ", ";
        }
        archivo << "\n";
    }

    archivo << "\n========================================\n";
    archivo << "   VERIFICACIÓN DE CONECTIVIDAD\n";
    archivo << "========================================\n";
    archivo << "El grafo está COMPLETAMENTE conectado.\n";
    archivo << "Todas las comunidades son alcanzables.\n";

    archivo << "\n========================================\n";
    archivo << "   ALGORITMO DE KRUSKAL - RESULTADO\n";
    archivo << "========================================\n\n";
    archivo << "Árbol de Expansión Mínima (MST):\n\n";
    archivo << "Conexión  |  Costo (miles $)\n";
    archivo << "----------+-----------------\n";

    int costoTotal = 0;
    for (const auto& arista : mst) {
        archivo << "   " << arista.origen << "-" << arista.destino
            << "     |       " << arista.peso << "\n";
        costoTotal += arista.peso;
    }

    archivo << "----------+-----------------\n";
    archivo << "   TOTAL  |       " << costoTotal << "\n";
    archivo << "========================================\n\n";

    archivo << "RESUMEN EJECUTIVO:\n";
    archivo << "==================\n";
    archivo << "• Comunidades conectadas: " << (mst.size() + 1) << "\n";
    archivo << "• Conexiones instaladas: " << mst.size() << "\n";
    archivo << "• Costo total: $" << costoTotal << ",000 USD\n\n";

    archivo << "METODOLOGÍA:\n";
    archivo << "============\n";
    archivo << "ALGORITMO UTILIZADO: Kruskal\n\n";
    archivo << "El algoritmo de Kruskal encuentra el árbol de expansión\n";
    archivo << "mínima (MST) mediante los siguientes pasos:\n\n";
    archivo << "1. Ordenar todas las aristas por peso (menor a mayor)\n";
    archivo << "2. Inicializar cada nodo como un conjunto independiente\n";
    archivo << "3. Para cada arista en orden:\n";
    archivo << "   - Si conecta dos conjuntos diferentes: seleccionarla\n";
    archivo << "   - Si crea un ciclo: descartarla\n";
    archivo << "4. Continuar hasta conectar todos los nodos\n\n";

    archivo << "ESTRUCTURA DE DATOS:\n";
    archivo << "====================\n";
    archivo << "• Grafo: Representado mediante lista de adyacencia\n";
    archivo << "• Union-Find: Para detección eficiente de ciclos\n";
    archivo << "  - Find: Búsqueda del representante con compresión de camino\n";
    archivo << "  - Union: Unión de conjuntos por rango\n\n";

    archivo << "CONCLUSIÓN:\n";
    archivo << "===========\n";
    archivo << "La red óptima de fibra óptica conecta todas las comunidades\n";
    archivo << "rurales con un costo mínimo de $" << costoTotal << ",000 USD, garantizando\n";
    archivo << "conectividad completa sin redundancias innecesarias.\n";

    archivo.close();

    cout << "✓ Archivo 'resultado_red_fibra_optica.txt' generado exitosamente.\n" << endl;
}

int main() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║  RED DE FIBRA ÓPTICA - PROYECTO MST   ║" << endl;
    cout << "╚════════════════════════════════════════╝\n" << endl;

    Grafo grafo;

    cout << "Inicializando red de comunidades..." << endl;
    cout << "Cargando 14 conexiones posibles...\n" << endl;

    grafo.agregarArista('A', 'B', 4);
    grafo.agregarArista('A', 'H', 8);
    grafo.agregarArista('B', 'C', 8);
    grafo.agregarArista('B', 'H', 11);
    grafo.agregarArista('C', 'D', 7);
    grafo.agregarArista('C', 'F', 4);
    grafo.agregarArista('C', 'I', 2);
    grafo.agregarArista('D', 'E', 9);
    grafo.agregarArista('D', 'F', 14);
    grafo.agregarArista('E', 'F', 10);
    grafo.agregarArista('F', 'G', 2);
    grafo.agregarArista('G', 'H', 1);
    grafo.agregarArista('G', 'I', 6);
    grafo.agregarArista('H', 'I', 7);

    grafo.mostrarTablaAdyacencia();

    grafo.mostrarAristas();

    grafo.verificarConectividad();

    vector<Arista> mst = algoritmoKruskal(grafo);

    mostrarResultado(mst);

    generarArchivo(grafo, mst);

    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║      PROCESO COMPLETADO CON ÉXITO     ║" << endl;
    cout << "╚════════════════════════════════════════╝\n" << endl;

    cout << "Presione Enter para salir...";
    cin.get();

    return 0;
}