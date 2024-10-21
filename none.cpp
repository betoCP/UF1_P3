#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sys/wait.h>  // Para la función wait()

using namespace std;

vector<string> nombres;

void agregarNombre(const string& nombre) {
    nombres.push_back(nombre);
}

void mostrarNombreAleatorio() {
    if (!nombres.empty()) {
        srand(time(0));
        int index = rand() % nombres.size();
        cout << "Nombre elegido: " << nombres[index] << endl;
    } else {
        cout << "No hay nombres en la lista." << endl;
    }
}

int main() {
    int numProcesos;
    cout << "Introduce el número de procesos a crear: ";
    cin >> numProcesos;

    for (int i = 0; i < numProcesos; ++i) {
        pid_t pid = fork();  // Crea un proceso hijo
        if (pid == 0) {  // Proceso hijo
            string nombre;
            cout << "Proceso hijo " << getpid() << ": Introduce un nombre: ";
            cin >> nombre;
            agregarNombre(nombre);
            mostrarNombreAleatorio();
            exit(0);  // Termina el proceso hijo
        } else if (pid > 0) {  // Proceso padre
            wait(NULL);  // Espera a que el proceso hijo termine
        } else {
            cout << "Error al crear el proceso." << endl;
        }
    }

    return 0;
}
