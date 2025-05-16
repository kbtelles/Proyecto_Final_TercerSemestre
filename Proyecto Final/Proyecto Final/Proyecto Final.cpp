#include <mysql.h>
#include <iostream>
#include "Empleados.h"
#include "Clientes.h"

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

void menuClientes() {
    Clientes c;
    int opcion = 0;

    do {
        cout << "\n--- Menu Clientes ---\n";
        cout << "1. Crear\n2. Leer\n3. Actualizar\n4. Borrar\n5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            string nombres, apellidos, NIT, telefono, correo, fecha;
            bool genero;
            cout << "Nombres: "; getline(cin, nombres);
            cout << "Apellidos: "; getline(cin, apellidos);
            cout << "NIT: "; getline(cin, NIT);
            cout << "Genero (1 = M, 0 = F): "; cin >> genero; cin.ignore();
            cout << "Telefono: "; getline(cin, telefono);
            cout << "Correo: "; getline(cin, correo);
            cout << "Fecha_Ingreso: "; getline(cin, fecha);

            c = Clientes(0, nombres, apellidos, NIT, genero, telefono, correo, fecha);
            c.crear();
            break;
        }
        case 2:
            c.leer();
            break;
        case 3: {
            int id;
            string nombres, apellidos, NIT, telefono, correo, fecha;
            bool genero;
            cout << "ID del cliente a actualizar: "; cin >> id; cin.ignore();
            cout << "Nombres: "; getline(cin, nombres);
            cout << "Apellidos: "; getline(cin, apellidos);
            cout << "NIT: "; getline(cin, NIT);
            cout << "Genero (1 = M, 0 = F): "; cin >> genero; cin.ignore();
            cout << "Telefono: "; getline(cin, telefono);
            cout << "Correo: "; getline(cin, correo);
            cout << "Fecha_Ingreso:"; getline(cin, fecha);

            c.setIdCliente(id);
            c.setNombres(nombres);
            c.setApellidos(apellidos);
            c.setNIT(NIT);
            c.setGenero(genero);
            c.setTelefono(telefono);
            c.setCorreo(correo);
            c.setFechaIngreso(fecha);
            c.actualizar();
            break;
        }
        case 4: {
            int id;
            cout << "ID del cliente a eliminar: "; cin >> id; cin.ignore();
            c.setIdCliente(id);
            c.borrar();
            break;
        }
        case 5:
            cout << "Saliendo del menu de clientes...\n";
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
        cout << "1. Empleados\n2. Clientes\n3. Productos (pendiente)\n4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;
        cin.ignore();

        switch (opcionPrincipal) {
        case 1:
            menuEmpleados();
            break;
        case 2:
            menuClientes();
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
