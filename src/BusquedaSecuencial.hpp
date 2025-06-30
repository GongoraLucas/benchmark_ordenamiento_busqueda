#ifndef BUSQUEDASECUENCIAL_HPP
#define BUSQUEDASECUENCIAL_HPP

#include <iostream>
#include <chrono>
using namespace std;

template<typename T>
struct BusquedaSecuencial {
private:
    T* arreglo;
    int tam;
    int comparaciones;
    int indiceResultado;
    std::chrono::milliseconds tiempoEjecucion;

    void buscar(T valorBuscado){
        indiceResultado = -1; // reset resultado en cada búsqueda
        for (int i = 0; i < tam; i++) {
            comparaciones++;
            if (arreglo[i] == valorBuscado) {
                indiceResultado = i;
                break;
            }
        }
    }

public:
    BusquedaSecuencial(T* datos, int t) {
        tam = t;
        arreglo = new T[tam];
        for (int i = 0; i < tam; i++) {
            arreglo[i] = datos[i];
        }
        comparaciones = 0;
        indiceResultado = -1;
    }

    ~BusquedaSecuencial() {
        delete[] arreglo;
    }

    void ejecutar(T valorBuscado, int repeticiones=100000) {
        comparaciones = 0;
        indiceResultado = -1;

        int comparacionesReal = 0;
        int indiceResultadoReal = -1;

        auto inicio = chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            buscar(valorBuscado);
            if (r == 0){
                comparacionesReal = comparaciones;
                indiceResultadoReal = indiceResultado;
            }
        }

        auto fin = chrono::high_resolution_clock::now();
        tiempoEjecucion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

        comparaciones = comparacionesReal;
        indiceResultado = indiceResultadoReal;
    }

    void mostrarResultados() const {
        cout << "Comparaciones totales: " << comparaciones << endl;
        if (indiceResultado != -1)
            cout << "Última búsqueda: Valor encontrado en el índice: " << indiceResultado << endl;
        else
            cout << "Última búsqueda: Valor no encontrado." << endl;

        cout << "Tiempo total de ejecución para " << "repeticiones" << ": " << tiempoEjecucion.count() << " milisegundos" << endl;
    }

    int obtenerIndice() const {
        return indiceResultado;
    }
};

#endif // BUSQUEDASECUENCIAL_HPP
