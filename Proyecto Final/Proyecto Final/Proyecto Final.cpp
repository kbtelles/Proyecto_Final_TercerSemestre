#include <mysql.h>
#include <iostream>
#include "Empleados.h"

using namespace std;

void menuEmpleados() {
    Empleados e;
    int opcion = 0;
    do {
        cout << "\n--- Menu Empleados ---\n";
        cout << "1. Crear\n2. Leer\n3. Actualizar\n4. Borrar\n5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            string nombres, apellidos, direccion, telefono, DPI, FechaNacimiento, FechaInicioLabores, FechaIngreso;
            bool genero;
            short idPuestos;

            cout << "Ingrese Nombres: "; getline(cin, nombres);
            cout << "Ingrese Apellidos: "; getline(cin, apellidos);
            cout << "Ingrese Direccion: "; getline(cin, direccion);
            cout << "Ingrese Telefono: "; getline(cin, telefono);
            cout << "Ingrese DPI: "; getline(cin, DPI);
            cout << "Ingrese Genero (1 para masculino, 0 para femenino): "; cin >> genero; cin.ignore();
            cout << "Ingrese Fecha de Nacimiento (YYYY-MM-DD): "; getline(cin, FechaNacimiento);
            cout << "Ingrese Id de Puesto: "; cin >> idPuestos; cin.ignore();
            cout << "Ingrese Fecha de Inicio de Labores (YYYY-MM-DD): "; getline(cin, FechaInicioLabores);
            cout << "Ingrese Fecha de Ingreso (YYYY-MM-DD HH:MM:SS): "; getline(cin, FechaIngreso);

            e = Empleados(idPuestos, "", 0, nombres, apellidos, direccion, telefono, DPI, genero, FechaNacimiento, FechaInicioLabores, FechaIngreso);
            e.crear();
            break;
        }
        case 2:
            e.leer();
            break;
        case 3: {
            int IdEmpleado;
            string nombres, apellidos, direccion, telefono, DPI, FechaNacimiento, FechaInicioLabores, FechaIngreso;
            bool genero;
            short idPuestos;

            cout << "Ingrese el ID a modificar: "; cin >> IdEmpleado; cin.ignore();
            cout << "Ingrese Nombres: "; getline(cin, nombres);
            cout << "Ingrese Apellidos: "; getline(cin, apellidos);
            cout << "Ingrese Direccion: "; getline(cin, direccion);
            cout << "Ingrese Telefono: "; getline(cin, telefono);
            cout << "Ingrese DPI: "; getline(cin, DPI);
            cout << "Ingrese Genero (1 para masculino, 0 para femenino): "; cin >> genero; cin.ignore();
            cout << "Ingrese Fecha de Nacimiento (YYYY-MM-DD): "; getline(cin, FechaNacimiento);
            cout << "Ingrese Id de Puesto: "; cin >> idPuestos; cin.ignore();
            cout << "Ingrese Fecha de Inicio de Labores (YYYY-MM-DD): "; getline(cin, FechaInicioLabores);
            cout << "Ingrese Fecha de Ingreso (YYYY-MM-DD HH:MM:SS): "; getline(cin, FechaIngreso);

            e.setId_empleado(IdEmpleado);
            e.setNombres(nombres);
            e.setApellidos(apellidos);
            e.setDireccion(direccion);
            e.setTelefono(telefono);
            e.setDPi(DPI);
            e.setGenero(genero);
            e.setFecha_Nacimiento(FechaNacimiento);
            e.setFechaInicioLabores(FechaInicioLabores);
            e.setFecha_Ingreso(FechaIngreso);
            e.setidPuestos(idPuestos);

            e.actualizar();
            break;
        }
        case 4: {
            int IdEmpleado;
            cout << "Ingrese el ID a eliminar: "; cin >> IdEmpleado; cin.ignore();
            e.setId_empleado(IdEmpleado);
            e.borrar();
            break;
        }
        case 5:
            cout << "Saliendo del menu de empleados...\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 5);
}

int main() {
    int opcionPrincipal = 0;
    do {
        cout << "\n--- Menu Principal ---\n";
        cout << "1. Empleados\n2. Clientes (pendiente)\n3. Productos (pendiente)\n4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;
        cin.ignore();

        switch (opcionPrincipal) {
        case 1:
            menuEmpleados();
            break;
        case 2:
            cout << "Modulo Clientes en desarrollo\n";
            break;
        case 3:
            cout << "Modulo Productos en desarrollo\n";
            break;
        case 4:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcionPrincipal != 4);

    return 0;
}
