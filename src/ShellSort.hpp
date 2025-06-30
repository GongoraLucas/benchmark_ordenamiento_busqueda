#ifndef SHELLSORT_HPP
#define SHELLSORT_HPP

#include <iostream>
#include <chrono>

using namespace std;

template<typename T>
struct ShellSort {
private:
    T* arreglo;
    int tam;
    int comparaciones;
    int asignaciones;
    std::chrono::milliseconds tiempoEjecucion;

    void sort(T arr[], int n) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                T temp = arr[i];
                int j = i;

                while (j >= gap) {
                    comparaciones++;
                    if (arr[j - gap] > temp) {
                        arr[j] = arr[j - gap];
                        asignaciones++;
                        j -= gap;
                    } else {
                        break;
                    }
                }

                if (j != i) {
                    arr[j] = temp;
                    asignaciones++;
                }
            }
        }
    }

public:
    ShellSort(T* arrOriginal, int t) {
        tam = t;
        comparaciones = 0;
        asignaciones = 0;

        arreglo = new T[tam];
        for (int i = 0; i < tam; i++) {
            arreglo[i] = arrOriginal[i];
        }
    }

    ~ShellSort() {
        delete[] arreglo;
    }

    void ejecutar(int repeticiones = 1000) {
        comparaciones = 0;
        asignaciones = 0;
        int comparacionesReal = 0;
        int asignacionesReal = 0;
        auto inicio = std::chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            sort(arreglo, tam);
            if (r == 0){
                comparacionesReal=comparaciones;
                asignacionesReal=asignaciones;
            }
        }

        auto fin = std::chrono::high_resolution_clock::now();
        tiempoEjecucion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

        comparaciones = comparacionesReal;
        asignaciones = asignacionesReal;

    }

    void mostrarResultados() const {
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Asignaciones: " << asignaciones << endl;
        cout << "Tiempo de ejecución: " << tiempoEjecucion.count() << " milisegundos" << endl;
    }
};

#endif // SHELLSORT_HPP
