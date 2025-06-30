#ifndef GENERADORARREGLOS_HPP
#define GENERADORARREGLOS_HPP

#include <iostream>
#include <cstdlib>


using namespace std;

template<typename T>
struct GeneradorArreglos {
private:
    T* arreglo;
    int tam;

    void insertionSort(T arr[], int n, bool esAscendente = true) {
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;

            while (j >= 0 && (esAscendente ? arr[j] > key : arr[j] < key)) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    void cambiarUltimosTres(T arr[], int n) {
        if (n < 3) return;
        // Cambiar últimos 3 elementos para desordenarlos un poco
        T temp = arr[n - 1];
        arr[n - 1] = arr[n - 2];
        arr[n - 2] = arr[n - 3];
        arr[n - 3] = temp;
    }

    void generarAleatorio(T arr[], int n) {
        int left = 1;
        int right = n * 10;
        for (int i = 0; i < n; i++) {
            arr[i] = left + rand() % (right - left + 1);
        }
    }

public:
    GeneradorArreglos(int n, int tipoArreglo, bool esAscendente = true) : tam(n) {
        arreglo = new T[tam];

        switch (tipoArreglo) {
            case 0: // Aleatorio
                generarAleatorio(arreglo, tam);
                break;
            case 1: // Casi ordenado
                generarAleatorio(arreglo, tam);
                insertionSort(arreglo, tam, esAscendente);
                cambiarUltimosTres(arreglo, tam);
                break;
            case 2: // Reverso
                generarAleatorio(arreglo, tam);
                insertionSort(arreglo, tam, !esAscendente);
                break;
            default:
                generarAleatorio(arreglo, tam);
                break;
        }
    }

    ~GeneradorArreglos() {
        delete[] arreglo;
    }

    T* obtenerArreglo() {
        return arreglo;
    }

    int obtenerTam() const {
        return tam;
    }

    void imprimirArreglo() const {
        for (int i = 0; i < tam; i++) {
            cout << arreglo[i] << " ";
        }
        cout << endl;
    }
};

#endif // GENERADORARREGLOS_HPP
