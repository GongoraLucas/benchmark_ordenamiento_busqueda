#ifndef BUSQUEDABINARIA_HPP
#define BUSQUEDABINARIA_HPP

#include <iostream>
#include <chrono>
using namespace std;

template<typename T>
struct BusquedaBinaria {
private:
    T* arreglo;
    int tam;
    int comparaciones;
    int indiceResultado;
    std::chrono::milliseconds tiempoEjecucion;

    void quickSort(T arr[], int left, int right) {
        if (left >= right) return;

        T pivot = arr[(left + right) / 2];
        int i = left, j = right;

        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;

            if (i <= j) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        if (left < j) quickSort(arr, left, j);
        if (i < right) quickSort(arr, i, right);
    }

    int buscar(T clave) {
        int izq = 0, der = tam - 1;
        // No reset comparaciones aquí porque se acumulará externamente
        while (izq <= der) {
            int medio = (izq + der) / 2;
            comparaciones++;
            if (arreglo[medio] == clave) return medio;
            else if (arreglo[medio] < clave) izq = medio + 1;
            else der = medio - 1;
        }
        return -1;
    }

public:
    BusquedaBinaria(T* datos, int t) {
        tam = t;
        arreglo = new T[tam];
        for (int i = 0; i < tam; i++) arreglo[i] = datos[i];

        quickSort(arreglo, 0, tam - 1);
        comparaciones = 0;
        indiceResultado = -1;
    }

    ~BusquedaBinaria() {
        delete[] arreglo;
    }

    void ejecutar(T clave, int repeticiones=100000) {
        comparaciones = 0;
        indiceResultado = -1;

        int comparacionesReal = 0;
        int indiceResultadoReal = -1;

        auto inicio = chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            indiceResultado = buscar(clave);
            if (r == 0){
                comparacionesReal = comparaciones;
                indiceResultadoReal = indiceResultado;
            }
        }

        auto fin = chrono::high_resolution_clock::now();
        tiempoEjecucion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

        comparaciones =comparacionesReal;
        indiceResultado = indiceResultadoReal;
    }

    void mostrarResultados() const {
        cout << "Comparaciones totales: " << comparaciones << endl;
        if (indiceResultado != -1)
            cout << "Última búsqueda: Valor encontrado en el índice: " << indiceResultado << endl;
        else
            cout << "Última búsqueda: Valor no encontrado." << endl;

        cout << "Tiempo total de búsqueda para las repeticiones: " << tiempoEjecucion.count() << " milisegundos" << endl;
    }

    int obtenerIndice() const {
        return indiceResultado;
    }
};

#endif // BUSQUEDABINARIA_HPP
