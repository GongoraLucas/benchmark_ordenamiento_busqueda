#ifndef MEZCLADIRECTA_HPP
#define MEZCLADIRECTA_HPP

#include <iostream>
#include <chrono>
using namespace std;

template<typename T>
struct MezclaDirecta {
private:
    T* arreglo;
    int tam;
    int comparaciones;
    int asignaciones;
    std::chrono::milliseconds tiempoEjecucion;

    void fusionar(T* arr, int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        T* izquierda = new T[n1];
        T* derecha = new T[n2];

        for (int i = 0; i < n1; i++) {
            izquierda[i] = arr[inicio + i];
            asignaciones++;
        }
        for (int j = 0; j < n2; j++) {
            derecha[j] = arr[medio + 1 + j];
            asignaciones++;
        }

        int i = 0, j = 0, k = inicio;

        while (i < n1 && j < n2) {
            comparaciones++;
            if (izquierda[i] <= derecha[j]) {
                arr[k++] = izquierda[i++];
            } else {
                arr[k++] = derecha[j++];
            }
            asignaciones++;
        }

        while (i < n1) {
            arr[k++] = izquierda[i++];
            asignaciones++;
        }
        while (j < n2) {
            arr[k++] = derecha[j++];
            asignaciones++;
        }

        delete[] izquierda;
        delete[] derecha;
    }

    void sort() {
        for (int longitud = 1; longitud < tam; longitud *= 2) {
            for (int inicio = 0; inicio < tam - longitud; inicio += 2 * longitud) {
                int medio = inicio + longitud - 1;
                int fin = (inicio + 2 * longitud - 1 < tam - 1) ? inicio + 2 * longitud - 1 : tam - 1;
                fusionar(arreglo, inicio, medio, fin);
            }
        }
    }

public:
    MezclaDirecta(T* arrOriginal, int t) : tam(t), comparaciones(0), asignaciones(0) {
        arreglo = new T[tam];
        for (int i = 0; i < tam; i++) {
            arreglo[i] = arrOriginal[i];
        }
    }

    ~MezclaDirecta() {
        delete[] arreglo;
    }

    void ejecutar(int repeticiones = 1000) {
        comparaciones = 0;
        asignaciones = 0;

        int comparacionesReal = 0;
        int asignacionesReal = 0;

        auto inicio = chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            sort();
            if (r == 0){
                comparacionesReal = comparaciones;
                asignacionesReal = asignaciones;
            }
        }

        auto fin = chrono::high_resolution_clock::now();
        tiempoEjecucion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

        comparaciones = comparacionesReal;
        asignaciones = asignacionesReal;
    }

    void mostrarResultados() const {
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Asignaciones: " << asignaciones << endl;
        cout << "Tiempo de ejecución: " << tiempoEjecucion.count() << " milisegundos" << endl;
    }
};

#endif // MEZCLADIRECTA_HPP
