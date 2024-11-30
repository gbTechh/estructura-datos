/*
THREADS SUMA 20 - ARRAY 1
Considere el siguiente programa (preg_threads.cpp). En la función main, se tiene un
arreglo "v" de 1000 elementos enteros y se tiene un arreglo "sums" de 5 elementos.
Se pide sumar todos los elementos de "v" de la siguiente manera, los elementos que terminan en:
0 o 9 se sumen en sums[0]
1 o 8 se sumen en sums[1]
2 o 7 se sumen en sums[2]
3 o 6 se sumen en sums[3]
4 o 5 se sumen en sums[4]
- El proceso debe ser realizado con 20 threads.
- Todas las sumas deben ser hechas directamente en el array sums.
- No se debe utilizar la idea de que cada thread tenga su propia suma.
- Sólo se debe modificar la función ThreadingSum
- Se puede agregar otras funciones y variables
- La función main no debe ser modificada
*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


// Necesitamos mutexes para proteger las sumas concurrentes
std::mutex sumMutexes[5];

// Función que ejecutará cada thread
void sumDigits(int* arr, int start, int count, unsigned long* sums) {
    // Cada thread procesará una porción del arreglo
    for (int i = start; i < start + count; i++) {
        // Obtenemos el último dígito del número
        int lastDigit = arr[i] % 10;

        // Determinamos en qué posición de sums debemos sumar
        int sumIndex;
        if (lastDigit == 0 || lastDigit == 9) sumIndex = 0;
        else if (lastDigit == 1 || lastDigit == 8) sumIndex = 1;
        else if (lastDigit == 2 || lastDigit == 7) sumIndex = 2;
        else if (lastDigit == 3 || lastDigit == 6) sumIndex = 3;
        else sumIndex = 4; // Para 4 y 5

        // Protegemos la suma con un mutex para evitar condiciones de carrera
        {
            std::lock_guard<std::mutex> lock(sumMutexes[sumIndex]);
            sums[sumIndex] += arr[i];
        }
    }
}

void ThreadingSum(int* pv, int sizev, unsigned long* sums, int sizes) {
    const int NUM_THREADS = 20;
    std::vector<std::thread> threads;

    // Calculamos cuántos elementos procesará cada thread
    int elementsPerThread = sizev / NUM_THREADS;
    int remainingElements = sizev % NUM_THREADS;

    // Creamos los threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Calculamos el punto de inicio para este thread
        int start = i * elementsPerThread;

        // Calculamos cuántos elementos procesará este thread
        int count = elementsPerThread;
        if (i == NUM_THREADS - 1) {
            // El último thread se encarga de los elementos restantes
            count += remainingElements;
        }

        // Creamos el thread y lo añadimos al vector
        threads.push_back(std::thread(sumDigits, pv, start, count, sums));
    }

    // Esperamos a que todos los threads terminen
    for (auto& thread : threads) {
        thread.join();
    }
}


int main()
{
    unsigned long sums[5] = {0,0,0,0,0};
    int v[1000] = {11,58,12,98,68,55,98,65,16,44,14,22,31,9,66,25,7,69,66,45,88,14,99,94,2,91,2,10,64,17,80,22,22,97,92,49,4,39,41,16,98,67,72,94,49,93,56,78,54,57,22,34,25,18,17,9,89,78,75,42,64,0,46,86,30,37,22,63,58,91,77,49,32,94,68,41,10,56,21,56,44,25,44,16,50,79,65,82,79,3,73,35,15,28,3,79,34,44,58,44,23,76,91,32,73,78,36,62,76,91,51,53,55,29,7,52,80,63,2,15,65,31,46,44,77,39,67,28,0,5,44,64,7,66,86,81,99,79,50,88,54,73,59,24,20,17,92,18,47,41,62,59,21,96,20,41,25,33,33,58,79,52,81,39,67,8,19,38,57,74,25,43,67,7,31,45,16,17,13,47,96,8,38,44,12,72,53,46,74,86,1,11,45,10,6,39,64,12,51,62,38,81,32,29,40,96,17,83,59,46,61,4,1,43,99,42,28,64,13,74,35,78,23,85,67,73,10,18,46,66,21,57,73,21,42,43,10,39,37,8,40,49,86,73,13,80,34,50,48,27,91,14,86,55,71,0,96,2,74,74,59,78,56,19,59,94,93,16,72,50,14,17,78,57,90,82,27,14,13,3,22,6,24,26,76,12,34,94,86,47,31,25,75,35,92,4,3,83,87,69,37,4,36,88,96,80,57,46,81,24,79,5,85,8,54,69,51,99,44,31,33,1,50,23,50,99,33,29,1,89,4,10,23,11,39,59,30,9,99,32,74,30,63,92,90,89,13,49,5,57,18,49,44,66,56,78,10,15,24,94,29,82,49,39,68,7,14,33,56,60,32,61,9,66,24,13,71,78,21,97,55,73,31,22,28,62,58,21,55,56,54,28,73,82,21,92,69,78,44,4,44,34,78,19,66,83,17,45,26,15,25,69,45,68,13,54,11,41,19,84,95,86,89,62,72,67,0,0,48,5,62,14,39,1,86,7,97,80,78,24,29,20,50,70,69,1,70,92,82,43,37,3,1,47,17,27,95,99,75,80,37,35,34,28,64,11,82,8,42,48,46,7,67,87,79,4,27,5,33,71,56,66,61,55,97,78,35,77,36,81,79,46,94,74,70,38,49,35,47,82,62,97,97,95,2,14,27,93,14,97,11,4,27,15,75,54,85,12,45,45,72,6,93,59,18,57,29,71,45,88,94,8,30,99,83,51,7,81,41,15,70,81,17,14,9,15,85,98,64,36,38,66,29,27,88,46,74,17,59,93,72,48,97,77,32,51,38,19,68,47,75,90,99,83,20,97,85,63,82,75,78,82,35,49,33,57,76,38,82,3,80,76,36,47,83,38,7,43,5,9,83,24,34,71,3,43,55,74,6,53,88,19,18,5,58,86,34,7,80,71,56,24,56,1,5,90,69,74,86,83,11,89,73,47,69,66,87,29,41,0,15,72,85,18,17,44,72,52,14,52,2,56,35,82,1,51,16,8,82,79,33,15,1,12,42,36,73,62,32,38,42,75,26,47,44,16,56,11,71,95,14,54,86,64,13,29,2,76,18,65,50,29,6,66,2,75,48,83,11,62,83,26,60,77,44,10,80,40,94,91,6,50,66,10,5,25,94,61,81,98,49,84,23,64,46,18,0,89,17,60,67,59,76,59,53,26,91,90,36,47,10,84,28,85,67,27,71,67,81,32,64,29,35,7,11,3,93,0,54,90,64,57,18,30,81,87,68,63,73,34,85,4,87,55,62,59,67,22,76,71,77,92,88,19,9,69,59,84,24,12,28,65,54,48,36,54,67,52,13,65,65,47,66,85,13,26,1,25,88,43,52,51,21,52,29,29,62,11,38,23,16,70,52,5,76,69,9,56,7,9,45,76,17,59,34,96,2,76,32,33,65,19,60,61,44,77,54,28,15,4,60,5,35,78,3,84,51,36,97,78,89,82,85,71,96,20,46,29,48,81,77,81,13,37,98,28,54,95,98,16,20,5,26,98,48,21,19,64,60,80,99,72,64,39,60,37,43,17,65,34,5,65,69,77,17,35,44,9,39,40,69,69,77,40,94,86,68,88,26,22,1,4,59,18,19,97,65,84,58,16,91,23,81,93,45,30,53,33,12,70,6,16,74,17,90,8,70,37,10,17,3,3,61,79,87,72,66,45,55,82,12,31,16,92,72,71,72,67,27,75,46,96,31,85,72,34,33,10,28,88,84,67,65,0,31,44,11,31,68,98,64,17,86,13,7,73,6,82,89,74};
    ThreadingSum(v, 1000, sums, 5);
    int s = 0;
    for(int i = 0; i < 1000; i++){
        s += v[i];
    }
    std::cout<<"\nsuma:"<<s<<"\n";
    for (auto i : sums)
        std::cout<<i<<"\n";
}
//FIN THREADS SUMA 20 - ARRAY
