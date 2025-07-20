#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>
using namespace std;

#define NUM_VEHICULOS 6
#define META 70
#define ALTURA_CARRO 4
#define ANCHO_CARRO 15

struct Vehiculo {
    string nombre;
    int color;
    int velocidad;
    int posicion;
    string dibujo[ALTURA_CARRO];
};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ocultarCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void pantallaBienvenida() {
    system("cls");
    cout << "\n\n\n\t\tBienvenido al Simulador de Carreras estilo ASCII art, Haga sus apuestas!\n";
    cout << "\t\tPresentamos a Rayo, Trueno, Furia, Tornado, Nitro y Relampago \n";
    cout << "\t\tPresiona cualquier tecla para comenzar...\n";
    char temp = _getch();
}

void mostrarVehiculos(Vehiculo vehiculos[]) {
    for (int i = 0; i < NUM_VEHICULOS; i++) {
        for (int j = 0; j < ALTURA_CARRO; j++) {
            cursor(vehiculos[i].posicion, 3 + i * (ALTURA_CARRO + 1) + j);
            setColor(vehiculos[i].color);
            cout << vehiculos[i].dibujo[j];
        }
    }
    setColor(7);
}

void limpiarVehiculos(Vehiculo vehiculos[]) {
    for (int i = 0; i < NUM_VEHICULOS; i++) {
        for (int j = 0; j < ALTURA_CARRO; j++) {
            cursor(vehiculos[i].posicion, 3 + i * (ALTURA_CARRO + 1) + j);
            cout << string(ANCHO_CARRO, ' ');
        }
    }
}

void inicializarVehiculos(Vehiculo vehiculos[]) {
    string nombres[NUM_VEHICULOS] = { "Rayo", "Trueno", "Furia", "Tornado", "Nitro", "Relampago" };
    int colores[NUM_VEHICULOS] = { 4, 2, 3, 6, 5, 1 };
    string dibujos[ALTURA_CARRO] = {
        "    ________ ",
        " __/[] [] []\\__",
        "",
        "|_0_______0____|"
    };

    for (int i = 0; i < NUM_VEHICULOS; i++) {
        vehiculos[i].nombre = nombres[i];
        vehiculos[i].color = colores[i];
        vehiculos[i].velocidad = rand() % 3 + 1;
        vehiculos[i].posicion = 0;
        for (int j = 0; j < ALTURA_CARRO; j++) {
            if (j == 2) {
                string nombreCarro = "| " + vehiculos[i].nombre;
                nombreCarro.resize(ANCHO_CARRO - 1, ' ');
                nombreCarro += "|";
                vehiculos[i].dibujo[j] = nombreCarro;
            }
            else {
                vehiculos[i].dibujo[j] = dibujos[j];
            }
        }
    }
}

int correrCarrera(Vehiculo vehiculos[], Vehiculo& ganador) {
    bool hayGanador = false;
    int idGanador = -1;
    inicializarVehiculos(vehiculos);

    while (!hayGanador) {
        limpiarVehiculos(vehiculos);

        for (int i = 0; i < NUM_VEHICULOS; i++) {
            vehiculos[i].posicion += vehiculos[i].velocidad;
            if (vehiculos[i].posicion >= META && !hayGanador) {
                hayGanador = true;
                idGanador = i;
            }
        }

        mostrarVehiculos(vehiculos);
        Sleep(100);
    }

    ganador = vehiculos[idGanador];
    return idGanador;
}

void mostrarGanador(const Vehiculo& ganador) {
    setColor(14);
    cursor(0, 20 + NUM_VEHICULOS * 3);
    cout << "\n\t\t\tGanador: " << ganador.nombre << "!\n";
    setColor(7);
    Sleep(2000);
}
void creditos() {
    system("cls");
    cout << "\t\tMatt Silva\n\n";
    cout << "\t\tGracias por jugar!\n";
	system("pause");
}

int main() {
    srand((unsigned int)time(NULL));
    ocultarCursor();

    pantallaBienvenida();

    int totalCarreras = rand() % 5 + 4;
    int ganadoresIndex[8];
    Vehiculo ganadores[8];
    Vehiculo vehiculos[NUM_VEHICULOS];

    for (int i = 0; i < totalCarreras; i++) {
        system("cls");
        cout << "\tCARRERA " << (i + 1) << " / " << totalCarreras << endl;
        ganadoresIndex[i] = correrCarrera(vehiculos, ganadores[i]);
        mostrarGanador(ganadores[i]);
    }
    creditos();
    return 0;
}
