#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <iostream>
#include <chrono>
#include <cstdlib>  // rand()

using namespace std;

template<typename T>
struct QuickSort {
private:
    T* arreglo;
    int tam;
    int comparaciones;
    int asignaciones;
    int tipoPivot; // -1: inicial, 0: central, 1: final, 2: aleatorio
    std::chrono::milliseconds tiempoEjecucion;

    T obtenerPivot(T arr[], int left, int right) {
        if (tipoPivot == -1) {
            return arr[left];
        } else if (tipoPivot == 0) {
            return arr[(left + right) / 2];
        } else if (tipoPivot == 1) {
            return arr[right];
        } else if (tipoPivot == 2) {
            int randomIndex = left + rand() % (right - left + 1);
            return arr[randomIndex];
        } else {
            return arr[(left + right) / 2]; // por defecto: central
        }
    }

    void sort(T arr[], int left, int right) {
        int i = left;
        int j = right;
        T pivot = obtenerPivot(arr, left, right);

        while (i <= j) {
            while (arr[i] < pivot) {
                comparaciones++;
                i++;
            }
            while (arr[j] > pivot) {
                comparaciones++;
                j--;
            }

            if (i <= j) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                asignaciones++;
                i++;
                j--;
            }
        }

        if (left < j) sort(arr, left, j);
        if (i < right) sort(arr, i, right);
    }

public:
    QuickSort(T* arrOriginal, int t, int tipoPiv) {
        tam = t;
        comparaciones = 0;
        asignaciones = 0;
        tipoPivot = tipoPiv;

        arreglo = new T[tam];
        for (int i = 0; i < tam; i++) {
            arreglo[i] = arrOriginal[i];
        }
    }

    ~QuickSort() {
        delete[] arreglo;
    }

    void ejecutar(int repeticiones=1000) {
        comparaciones = 0;
        asignaciones = 0;
        int comparacionesReal = 0;
        int asignacionesReal = 0;
        auto inicio = std::chrono::high_resolution_clock::now();

        for (int i=0;i<=repeticiones;i++){
            sort(arreglo, 0, tam - 1);
            if (i == 0){
                comparacionesReal = comparaciones;
                asignacionesReal = asignaciones;
            }
        }
        auto fin = std::chrono::high_resolution_clock::now();
        tiempoEjecucion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

        comparaciones = comparacionesReal;
        asignaciones = asignacionesReal;
    }

    void mostrarResultados() const {
        cout << "Tipo de pivote: ";
        if (tipoPivot == -1) cout << "Inicial\n";
        else if (tipoPivot == 0) cout << "Central\n";
        else if (tipoPivot == 1) cout << "Final\n";
        else if (tipoPivot == 2) cout << "Aleatorio\n";
        else cout << "Desconocido (se usó central por defecto)\n";

        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Asignaciones (intercambios lógicos): " << asignaciones << endl;
        cout << "Tiempo de ejecución: " << tiempoEjecucion.count() << " milisegundos" << endl;
    }
};

#endif // QUICKSORT_HPP
