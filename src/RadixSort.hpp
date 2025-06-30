#ifndef RADIXSORT_HPP
#define RADIXSORT_HPP

#include <iostream>
#include <chrono>
using namespace std;

template<typename T>
struct RadixSort {
private:
    T* arreglo;
    int tam;
    int asignaciones;
    std::chrono::milliseconds tiempoEjecucion;

    void CountingSort(T arr[], int n, int exp) {
        T* output = new T[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            int digito = (arr[i] / exp) % 10;
            count[digito]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digito = (arr[i] / exp) % 10;
            output[count[digito] - 1] = arr[i];
            asignaciones++;
            count[digito]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
            asignaciones++;
        }

        delete[] output;
    }

    T getMax(T arr[], int n) {
        T maxVal = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }
        return maxVal;
    }

    void sort(T arr[], int n) {
        T maxVal = getMax(arr, n);

        for (T exp = 1; maxVal / exp > 0; exp *= 10) {
            CountingSort(arr, n, exp);
        }
    }

public:
    RadixSort(T* arr, int t) {
        tam = t;
        asignaciones = 0;
        arreglo = new T[tam];

        for (int i = 0; i < tam; i++) {
            arreglo[i] = arr[i];
        }
    }

    ~RadixSort() {
        delete[] arreglo;
    }

    void ejecutar(int repeticiones = 1000) {
        asignaciones = 0;
        int asignacionesReal = 0;

        auto inicio = chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            sort(arreglo, tam);

            if (r == 0){
                asignacionesReal = asignaciones;
            }
        }

        auto fin = chrono::high_resolution_clock::now();
        tiempoEjecucion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
        asignaciones = asignacionesReal;
    }

    void mostrarResultados() const {
        cout << "Asignaciones (RadixSort): " << asignaciones << endl;
        cout << "Tiempo de ejecución: " << tiempoEjecucion.count() << " milisegundos" << endl;
    }
};

#endif // RADIXSORT_HPP
