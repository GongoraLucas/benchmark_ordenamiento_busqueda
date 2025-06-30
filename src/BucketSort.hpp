#ifndef BUCKETSORT_HPP
#define BUCKETSORT_HPP

#include <iostream>
#include <chrono>
using namespace std;

template<typename T>
class BucketSort {
private:
    T* arreglo;
    int tam;
    int asignaciones;
    int intercambios;
    int buckets;
    int bucketsUsados;
    int metodoOrdenamiento; // 0:InsertionSort, 1:BubbleSort
    std::chrono::milliseconds tiempoEjecucion;

    T** bucketsArr;
    int* counts;

    void insertionSort(T arr[], int n) {
        for (int i = 1; i < n; i++) {
            T temp = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > temp) {
                asignaciones++;
                arr[j + 1] = arr[j];
                j--;
            }
            asignaciones++;
            arr[j + 1] = temp;
        }
    }

    void bubbleSort(T arr[], int n) {
        bool ordenado;
        for (int i = 0; i < n; i++) {
            ordenado = true;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    intercambios++;
                    ordenado = false;
                }
            }
            if (ordenado) break;
        }
    }

    void sort(T arr[], int n, int numBuckets) {
        bucketsArr = new T*[numBuckets];
        counts = new int[numBuckets];

        for (int i = 0; i < numBuckets; i++) {
            bucketsArr[i] = new T[n];
            counts[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            int idx = static_cast<int>(arr[i] * numBuckets);
            if (idx >= numBuckets) idx = numBuckets - 1;

            bucketsArr[idx][counts[idx]] = arr[i];
            counts[idx]++;
            asignaciones++;
        }

        bucketsUsados = 0;
        for (int i = 0; i < numBuckets; i++) {
            if (counts[i] > 0) bucketsUsados++;
        }

        for (int i = 0; i < numBuckets; i++) {
            if (counts[i] > 1) {
                if (metodoOrdenamiento == 0) {
                    insertionSort(bucketsArr[i], counts[i]);
                } else if (metodoOrdenamiento == 1) {
                    bubbleSort(bucketsArr[i], counts[i]);
                } else {
                    insertionSort(bucketsArr[i], counts[i]);
                }
            }
        }

        int pos = 0;
        for (int i = 0; i < numBuckets; i++) {
            for (int j = 0; j < counts[i]; j++) {
                arr[pos++] = bucketsArr[i][j];
                asignaciones++;
            }
        }

        for (int i = 0; i < numBuckets; i++) {
            delete[] bucketsArr[i];
        }
        delete[] bucketsArr;
        delete[] counts;
    }

public:
    BucketSort(T* arrOriginal, int t, int b, int metodo) {
        tam = t;
        buckets = b;
        metodoOrdenamiento = metodo;
        asignaciones = 0;
        intercambios = 0;
        bucketsUsados = 0;

        arreglo = new T[tam];
        for (int i = 0; i < tam; i++) {
            arreglo[i] = arrOriginal[i];
        }
    }

    ~BucketSort() {
        delete[] arreglo;
    }

    void ejecutar(int repeticiones = 1000) {
        asignaciones = 0;
        intercambios = 0;
        bucketsUsados = 0;

        int asignacionesReal = 0;
        int intercambiosReal = 0;
        int bucketsUsadosReal = 0;

        auto inicio = std::chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            sort(arreglo, tam, buckets);
            if (r == 0){
                asignacionesReal = asignaciones;
                intercambiosReal = intercambios;
                bucketsUsadosReal = bucketsUsados;
            }
        }

        auto fin = std::chrono::high_resolution_clock::now();
        tiempoEjecucion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

        asignaciones = asignacionesReal;
        intercambios = intercambiosReal;
        bucketsUsados = bucketsUsadosReal;

    }

    void mostrarResultados() const {
        cout << "Método de ordenamiento interno: ";
        if (metodoOrdenamiento == 0) cout << "Insertion Sort\n";
        else if (metodoOrdenamiento == 1) cout << "Bubble Sort\n";
        else cout << "No se ingresó uno correcto, se usó Insertion Sort\n";

        cout << "Asignaciones (BucketSort): " << asignaciones << endl;
        cout << "Intercambios (BucketSort): " << intercambios << endl;
        cout << "Buckets usados: " << bucketsUsados << " de " << buckets << endl;
        cout << "Tiempo de ejecución: " << tiempoEjecucion.count() << " milisegundos\n";
    }
};

#endif // BUCKETSORT_HPP
