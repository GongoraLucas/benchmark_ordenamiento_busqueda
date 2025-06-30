#ifndef TABLASHASH_HPP
#define TABLASHASH_HPP

#include <iostream>
#include <chrono>
using namespace std;

template<typename T>
struct TablaHash {
private:
    struct Nodo {
        T clave;
        Nodo* siguiente;
        Nodo(T c) : clave(c), siguiente(nullptr) {}
    };

    Nodo** tabla;
    int tam;
    int colisiones;
    int comparacionesBusqueda;

    std::chrono::milliseconds tiempoBusqueda;

    int funcionHash(T clave) {
        return clave % tam;
    }

public:
    float longitudPromedio;
    TablaHash(T* arr, int n, int tamanioTabla) {
        tam = tamanioTabla;
        tabla = new Nodo*[tam];
        for (int i = 0; i < tam; i++)
            tabla[i] = nullptr;

        colisiones = 0;

        for (int i = 0; i < n; i++) {
            int pos = funcionHash(arr[i]);
            if (tabla[pos] != nullptr)
                colisiones++;

            Nodo* nuevo = new Nodo(arr[i]);
            nuevo->siguiente = tabla[pos];
            tabla[pos] = nuevo;
        }

        int totalNodos = 0;
        for (int i = 0; i < tam; i++) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                totalNodos++;
                actual = actual->siguiente;
            }
        }
        longitudPromedio = static_cast<float>(totalNodos) / tam;

        comparacionesBusqueda = 0;
    }

    ~TablaHash() {
        for (int i = 0; i < tam; i++) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] tabla;
    }

    // Ejecutar búsqueda repetida para evitar tiempo 0
    bool ejecutar(T clave, int repeticiones = 100000) {
        comparacionesBusqueda = 0;
        bool encontrado = false;

        int comparacionesBusquedaReal = 0;
        bool encontradoReal = false;

        auto inicio = chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            int pos = funcionHash(clave);
            Nodo* actual = tabla[pos];
            while (actual != nullptr) {
                comparacionesBusqueda++;
                if (actual->clave == clave) {
                    encontrado = true;
                    break;
                }
                actual = actual->siguiente;
            }

            if (r == 0){
                comparacionesBusquedaReal = comparacionesBusqueda;
                encontradoReal = encontrado;
            }
        }

        auto fin = chrono::high_resolution_clock::now();
        tiempoBusqueda = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

        comparacionesBusqueda = comparacionesBusquedaReal;
        encontrado = encontradoReal;

        return encontrado;
    }

    void mostrarResultados() const {
        cout << "Colisiones: " << colisiones << endl;
        cout << "Comparaciones totales en búsqueda: " << comparacionesBusqueda << endl;
        cout << "Longitud promedio de listas: " << longitudPromedio << endl;
        cout << "Tiempo total de búsqueda para las repeticiones: " << tiempoBusqueda.count() << " milisegundos" << endl;
    }

    void mostrarTabla() {
        for (int i = 0; i < tam; i++) {
            cout << "Posición " << i << ": ";
            Nodo* actual = tabla[i];
            if (!actual) {
                cout << "[VACÍA]";
            } else {
                while (actual != nullptr) {
                    cout << actual->clave << " -> ";
                    actual = actual->siguiente;
                }
                cout << "NULL";
            }
            cout << endl;
        }
    }
};

#endif // TABLASHASH_HPP
