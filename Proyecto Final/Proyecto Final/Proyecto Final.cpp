#include <mysql.h>
#include <iostream>
#include "Empleados.h"
#include "Clientes.h"
#include "Proveedor.h"
#include "Productos.h"
#include "marcas.h"
#include "ventas.h"
#include "Compras.h"

using namespace std;

void menuPuestos() {
    Puestos p;
    int opcion = 0;

    do {
        cout << "\n--- Menu de Puestos ---\n";
        cout << "1. Crear\n2. Leer\n3. Actualizar\n4. Borrar\n5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            int idPuestos;
            string Puesto;
            cout << "Puesto: "; getline(cin, Puesto);


            p = Puestos(0, Puesto);
            p.crear();
            break;
        }
        case 2:
            p.leer();
            break;
        case 3: {
            int idPuestos;
            string Puesto;
            cout << "ID del puesto a actualizar: "; cin >> idPuestos; cin.ignore();
            cout << "Puesto: "; getline(cin, Puesto);


            p.setIdPuesto(idPuestos);
            p.setPuesto(Puesto);
            break;
        }
        case 4: {
            int idPuestos;
            cout << "ID del puesto a eliminar: "; cin >> idPuestos; cin.ignore();
            p.setIdPuesto(idPuestos);
            p.borrar();
            break;
        }
        case 5:
            cout << "Saliendo del menu de proveedores...\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 5);
}


void mostrarPuestos() {
    ConexionBD cn;
    cn.abrir_conexion();

    if (cn.getConector()) {
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        string consulta = "SELECT idPuesto, puesto FROM puestos;";
        if (!mysql_query(cn.getConector(), consulta.c_str())) {
            resultado = mysql_store_result(cn.getConector());
            cout << "----- PUESTOS DISPONIBLES -----" << endl;
            while ((fila = mysql_fetch_row(resultado))) {
                cout << "ID: " << fila[0] << ", Puesto: " << fila[1] << endl;
            }
            mysql_free_result(resultado);
        }
        else {
            cout << "Error al consultar puestos: " << mysql_error(cn.getConector()) << endl;
        }
    }
    else {
        cout << "Fallo la conexión a la base de datos." << endl;
    }
    cn.cerrar_conexion();
}


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

            mostrarPuestos();  
            cout << "Ingrese Id de Puesto: "; cin >> idPuestos; cin.ignore();

            cout << "Ingrese Fecha de Inicio de Labores (YYYY-MM-DD): "; getline(cin, FechaInicioLabores);
          

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

            mostrarPuestos();  
            cout << "Ingrese Id de Puesto: "; cin >> idPuestos; cin.ignore();

            cout << "Ingrese Fecha de Inicio de Labores (YYYY-MM-DD): "; getline(cin, FechaInicioLabores);
            

            e.setId_empleado(IdEmpleado);
            e.setNombres(nombres);
            e.setApellidos(apellidos);
            e.setDireccion(direccion);
            e.setTelefono(telefono);
            e.setDPi(DPI);
            e.setGenero(genero);
            e.setFecha_Nacimiento(FechaNacimiento);
            e.setFechaInicioLabores(FechaInicioLabores);
            
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
        cout << "1. Crear\n2. Busqueda\n3. Actualizar\n4. Borrar\n5. Salir\n";
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

void menuProveedores() {
    Proveedores p;
    int opcion = 0;

    do {
        cout << "\n--- Menu Proveedores ---\n";
        cout << "1. Crear\n2. Leer\n3. Actualizar\n4. Borrar\n5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            string proveedor, nit, direccion, telefono;
            cout << "Proveedor: "; getline(cin, proveedor);
            cout << "NIT: "; getline(cin, nit);
            cout << "Direccion: "; getline(cin, direccion);
            cout << "Telefono: "; getline(cin, telefono);

            p = Proveedores(0, proveedor, nit, direccion, telefono);
            p.crear();
            break;
        }
        case 2:
            p.leer();
            break;
        case 3: {
            int id;
            string proveedor, nit, direccion, telefono;
            cout << "ID del proveedor a actualizar: "; cin >> id; cin.ignore();
            cout << "Proveedor: "; getline(cin, proveedor);
            cout << "NIT: "; getline(cin, nit);
            cout << "Direccion: "; getline(cin, direccion);
            cout << "Telefono: "; getline(cin, telefono);

            p.setIdProveedor(id);
            p.setProveedor(proveedor);
            p.setNIT(nit);
            p.setDireccion(direccion);
            p.setTelefono(telefono);
            p.actualizar();
            break;
        }
        case 4: {
            int id;
            cout << "ID del proveedor a eliminar: "; cin >> id; cin.ignore();
            p.setIdProveedor(id);
            p.borrar();
            break;
        }
        case 5:
            cout << "Saliendo del menu de proveedores...\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 5);
}

void menuMarcas() {
    Marcas marca;
    int opcion = 0;

    do {
        cout << "\n--- Menu Marcas ---\n";
        cout << "1. Crear\n2. Leer\n3. Actualizar\n4. Borrar\n5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            string nombreMarca;
            cout << "Nombre de la Marca: ";
            getline(cin, nombreMarca);
            marca = Marcas(0, nombreMarca);
            marca.crear();
            break;
        }
        case 2:
            marca.leer();
            break;
        case 3: {
            int id;
            string nombreMarca;
            cout << "ID de la Marca a actualizar: ";
            cin >> id;
            cin.ignore();
            cout << "Nuevo nombre de la Marca: ";
            getline(cin, nombreMarca);
            marca.setIdMarca(id);
            marca.setMarca(nombreMarca);
            marca.actualizar();
            break;
        }
        case 4: {
            int id;
            cout << "ID de la Marca a eliminar: ";
            cin >> id;
            cin.ignore();
            marca.setIdMarca(id);
            marca.borrar();
            break;
        }
        case 5:
            cout << "Saliendo del menu de marcas...\n";
            break;
        default:
            cout << "Opción inválida\n";
        }
    } while (opcion != 5);
}


void mostrarTablaMarcas() {
    ConexionBD cn;
    cn.abrir_conexion();
    MYSQL_ROW fila;
    MYSQL_RES* resultado;

    cout << "\n--- Lista de Marcas ---\n";
    if (cn.getConector()) {
        string consulta = "SELECT idMarca, marca FROM marcas;";
        const char* c = consulta.c_str();
        if (!mysql_query(cn.getConector(), c)) {
            resultado = mysql_store_result(cn.getConector());
            while ((fila = mysql_fetch_row(resultado))) {
                cout << "ID: " << fila[0] << " | Marca: " << fila[1] << endl;
            }
        }
        else {
            cout << "Error al consultar las marcas.\n";
        }
    }
    else {
        cout << "Error al conectar con la base de datos.\n";
    }
    cn.cerrar_conexion();
}


void menuProductos() {
    Productos prod;
    int opcion = 0;

    do {
        cout << "\n--- Menu Productos ---\n";
        cout << "1. Crear\n2. Leer\n3. Actualizar\n4. Borrar\n5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            string producto, descripcion, imagen, fecha_ingreso;
            int idMarca, existencias;
            double precio_costo, precio_venta;

            cout << "Producto: "; getline(cin, producto);
            mostrarTablaMarcas();
            cout << "ID Marca: "; cin >> idMarca; cin.ignore();
            cout << "Descripcion: "; getline(cin, descripcion);
            cout << "Imagen: "; getline(cin, imagen);
            cout << "Precio costo: "; cin >> precio_costo; cin.ignore();
            cout << "Precio venta: "; cin >> precio_venta; cin.ignore();
            cout << "Existencias: "; cin >> existencias; cin.ignore();

            prod = Productos(0, producto, idMarca, descripcion, imagen, precio_costo, precio_venta, existencias, fecha_ingreso);
            prod.crear();
            break;
        }
        case 2:
            prod.leer();
            break;
        case 3: {
            int id, idMarca, existencias;
            string producto, descripcion, imagen, fecha_ingreso;
            double precio_costo, precio_venta;

            cout << "ID del producto a actualizar: "; cin >> id; cin.ignore();
            cout << "Producto: "; getline(cin, producto);
            mostrarTablaMarcas();
            cout << "ID Marca: "; cin >> idMarca; cin.ignore();
            cout << "Descripcion: "; getline(cin, descripcion);
            cout << "Imagen: "; getline(cin, imagen);
            cout << "Precio costo: "; cin >> precio_costo; cin.ignore();
            cout << "Precio venta: "; cin >> precio_venta; cin.ignore();
            cout << "Existencias: "; cin >> existencias; cin.ignore();

            prod.setIdProducto(id);
            prod.setProducto(producto);
            prod.setIdMarca(idMarca);
            prod.setDescripcion(descripcion);
            prod.setImagen(imagen);
            prod.setPrecioCosto(precio_costo);
            prod.setPrecioVenta(precio_venta);
            prod.setExistencias(existencias);
            prod.setFechaIngreso(fecha_ingreso);
            prod.actualizar();
            break;
        }
        case 4: {
            int id;
            cout << "ID del producto a eliminar: "; cin >> id; cin.ignore();
            prod.setIdProducto(id);
            prod.borrar();
            break;
        }
        case 5:
            cout << "Saliendo del menu de productos...\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 5);
}


void menuVentas() {
    Ventas venta;
    int opcion = 0;

    do {
        cout << "\n--- Menu Ventas ---\n";
        cout << "1. Crear Venta con Detalle\n";
        cout << "2. Leer Ventas\n";
        cout << "3. Actualizar Venta con Detalle\n";
        cout << "4. Eliminar Venta con Detalle\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
  
            venta.crearVentaConDetalle();
            break;
        }
        case 2:
            venta.leerVentas();
            break;
        case 3:
            venta.actualizarVenta();  
            break;
        case 4: {
            int id;
            cout << "ID de la venta a eliminar: "; cin >> id; cin.ignore();
            venta.setIdVenta(id);
            venta.eliminarVentaConDetalle();
            break;
        }
        case 5:
            cout << "Saliendo del menu de ventas...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 5);
}

void menuCompras() {
    Compras compra;
    int opcion = 0;

    do {
        cout << "\n--- Menu Compras ---\n";
        cout << "1. Crear Compra con Detalle\n";
        cout << "2. Leer Compras\n";
        cout << "3. Eliminar Compra con Detalle\n";
        cout << "4. Actualizar Compra con Detalle\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            int noOrden, proveedor;
            string fecha;

            cout << "Número de orden: "; cin >> noOrden; cin.ignore();
            cout << "ID Proveedor: "; cin >> proveedor; cin.ignore();

            compra.setNoOrdenCompra(noOrden);
            compra.setIdProveedor(proveedor);

            compra.crearCompraConDetalle();
            break;
        }
        case 2:
            compra.leerCompras();
            break;
        case 3: {
            int id;
            cout << "ID de la compra a eliminar: "; cin >> id; cin.ignore();
            compra.setIdCompra(id);
            compra.eliminarCompraConDetalle();
            break;
        }
        case 4: {
            int id, noOrden, proveedor;
            string fecha;

            cout << "ID de la compra a actualizar: "; cin >> id; cin.ignore();
            compra.setIdCompra(id);

            cout << "Nuevo numero de orden: "; cin >> noOrden; cin.ignore();
            cout << "Nuevo ID proveedor: "; cin >> proveedor; cin.ignore();

            compra.setNoOrdenCompra(noOrden);
            compra.setIdProveedor(proveedor);
            compra.setFechaOrden(fecha);

            compra.actualizarCompraConDetalle();
            break;
        }
        case 5:
            cout << "Saliendo del menú de compras...\n";
            break;
        default:
            cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 5);
}


void buscarClientePorNitYCrearSiNoExiste() {
    Clientes cliente;
    string nit;
    cout << "Ingrese NIT del cliente: ";
    getline(cin, nit);

    if (cliente.buscarPorNit(nit)) {
        cout << "Cliente encontrado:\n";
        cout << "ID: " << cliente.getIdCliente() << endl;
        cout << "Nombres: " << cliente.getNombres() << endl;
        cout << "Apellidos: " << cliente.getApellidos() << endl;
        cout << "NIT: " << cliente.getNIT() << endl;
        cout << "Genero: " << (cliente.getGenero() ? "Masculino" : "Femenino") << endl;
        cout << "Telefono: " << cliente.getTelefono() << endl;
        cout << "Correo: " << cliente.getCorreo() << endl;
       
    }
    else {
        cout << "Cliente no encontrado. Desea crear uno nuevo? (s/n): ";
        char opc; cin >> opc; cin.ignore();
        if (tolower(opc) == 's') {
            string nombres, apellidos, telefono, correo, fechaIngreso;
            bool genero;

            cout << "Ingrese nombres: "; getline(cin, nombres);
            cout << "Ingrese apellidos: "; getline(cin, apellidos);
            cout << "Ingrese genero (1 para masculino, 0 para femenino): "; cin >> genero; cin.ignore();
            cout << "Ingrese telefono: "; getline(cin, telefono);
            cout << "Ingrese correo electronico: "; getline(cin, correo);
            

            cliente.setNIT(nit);
            cliente.setNombres(nombres);
            cliente.setApellidos(apellidos);
            cliente.setGenero(genero);
            cliente.setTelefono(telefono);
            cliente.setCorreo(correo);
            cliente.setFechaIngreso(fechaIngreso);

            cliente.crear();
        }
        else {
            cout << "No se creó ningún cliente.\n";
        }
    }
}




int main() {
    int opcionPrincipal = 0;
    do {
        cout << "\n--- Menu Principal ---\n";
        cout << "1. Puestos\n2. Empleados\n3. Clientes\n4. Proveedores\n5. Marcas\n6. Productos\n7. Ventas\n8. Compras\n9.Busqueda de Clientes por medio de NIT\n10. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;
        cin.ignore();

        switch (opcionPrincipal) {
        case 1:
            menuPuestos();
            break;
        case 2:
            menuEmpleados();
            break;
        case 3:
            menuClientes();
            break;
        case 4:
            menuProveedores();
            break;
        case 5:
            menuMarcas();
            break;
        case 6:
            menuProductos();
            break;
        case 7:
            menuVentas();
            break;
        case 8:
            menuCompras();
            break;
        case 9:
            buscarClientePorNitYCrearSiNoExiste();
            break;
        case 10:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcionPrincipal != 10);

    return 0;
}
