#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <algorithm>
#include "Clientes.h"

using namespace std;

inline bool validarNIT(string nit) {
    // Eliminar espacios y convertir a mayúsculas
    nit.erase(remove(nit.begin(), nit.end(), ' '), nit.end());
    transform(nit.begin(), nit.end(), nit.begin(), ::toupper);

    // Casos especiales
    if (nit == "CF" || nit == "C/F" || nit == "CONSUMIDORFINAL") return true;

    // Eliminar guiones
    nit.erase(remove(nit.begin(), nit.end(), '-'), nit.end());

    if (nit.length() < 2) return false;

    string cuerpo = nit.substr(0, nit.length() - 1);
    char verificador = nit.back();

    if (!all_of(cuerpo.begin(), cuerpo.end(), ::isdigit)) return false;

    int factor = cuerpo.length() + 1;
    int suma = 0;

    for (char c : cuerpo) {
        suma += (c - '0') * factor;
        factor--;
    }

    int modulo = suma % 11;
    char esperado = (modulo == 10) ? 'K' : (char)('0' + modulo);

    return verificador == esperado;
}


class Ventas {


private:
    int idVenta = 0;
    int noFactura, idCliente, idEmpleado;
    string serie, fechaFactura, nitCliente;

public:
    // Setters
    void setIdVenta(int v) { idVenta = v; }
    void setNoFactura(int n) { noFactura = n; }
    void setSerie(string s) { serie = s; }
    void setFechaFactura(string f) { fechaFactura = f; }
    void setIdCliente(int c) { idCliente = c; }
    void setNitCliente(string nc) { nitCliente = nc; }
    void setIdEmpleado(int e) { idEmpleado = e; }


    int generarNoFactura(MYSQL* con) {
        string query = "SELECT IFNULL(MAX(nofactura), 0) + 1 FROM ventas;";
        if (!mysql_query(con, query.c_str())) {
            MYSQL_RES* res = mysql_store_result(con);
            MYSQL_ROW row = mysql_fetch_row(res);
            int nuevoNo = row ? stoi(row[0]) : 1;
            mysql_free_result(res);
            return nuevoNo;
        }
        return 1; // Por defecto si falla
    }

    string generarSerie(int noFactura) {
        // Ejemplo: Cambiar de serie cada 100 facturas
        char letra = 'A' + (noFactura / 100);
        return string(1, letra);
    }

    void mostrarClientes(MYSQL* con) {
        string query = "SELECT NIT, nombres, apellidos FROM clientes;";
        if (!mysql_query(con, query.c_str())) {
            MYSQL_RES* res = mysql_store_result(con);
            MYSQL_ROW row;
            cout << "\n----- CLIENTES DISPONIBLES -----\n";
            while ((row = mysql_fetch_row(res))) {
                cout << "NIT: " << row[0] << ", Nombre: " << row[1] << " " << row[2] << endl;
            }
            mysql_free_result(res);
        }
        else {
            cout << "Error al mostrar clientes: " << mysql_error(con) << endl;
        }
    }


    void mostrarEmpleados(MYSQL* con) {
        string query = "SELECT idEmpleado, nombres, apellidos FROM empleados;";
        if (!mysql_query(con, query.c_str())) {
            MYSQL_RES* res = mysql_store_result(con);
            MYSQL_ROW row;
            cout << "\n----- EMPLEADOS DISPONIBLES -----\n";
            while ((row = mysql_fetch_row(res))) {
                cout << "ID: " << row[0] << ", Nombre: " << row[1] << " " << row[2] << endl;
            }
            mysql_free_result(res);
        }
        else {
            cout << "Error al mostrar empleados: " << mysql_error(con) << endl;
        }
    }

    void mostrarProductos(MYSQL* con) {
        string query = "SELECT idProducto, producto, existencia FROM productos;";
        if (!mysql_query(con, query.c_str())) {
            MYSQL_RES* res = mysql_store_result(con);
            MYSQL_ROW row;
            cout << "\n----- PRODUCTOS DISPONIBLES -----\n";
            while ((row = mysql_fetch_row(res))) {
                cout << "ID: " << row[0] << ", Nombre: " << row[1] << ",Existencia: " << row[2]<< " " << row[3] << endl;
            }
            mysql_free_result(res);
        }
        else {
            cout << "Error al mostrar productos: " << mysql_error(con) << endl;
        }
    }



    void crearVentaConDetalle() {
        ConexionBD cn;
        cn.abrir_conexion();

        if (cn.getConector()) {
            mostrarClientes(cn.getConector());
            //cout << "\nIngrese NIT Cliente: ";
            //cin >> nitCliente;

            string nit;
            cout << "Ingrese NIT del cliente (o C/F): ";
            cin >> nit;

            if (!validarNIT(nit)) {
                cout << "NIT invalido. Operacion cancelada.\n";
                cn.cerrar_conexion();
                return;
            }

            // Verificar si el NIT existe en la tabla de clientes
            string consultaNIT = "SELECT idCliente FROM clientes WHERE nit = '" + nit + "';";
            int idClienteLocal = 0;
            string nitNormalizado = nit;
            transform(nitNormalizado.begin(), nitNormalizado.end(), nitNormalizado.begin(), ::toupper);

            string consultaCliente;

            if (nitNormalizado == "CF" || nitNormalizado == "C/F") {
                // Buscar si ya existe un cliente "C/F"
                consultaCliente = "SELECT idCliente FROM clientes WHERE UPPER(nit) IN ('C/F', 'CF');";

                if (!mysql_query(cn.getConector(), consultaCliente.c_str())) {
                    MYSQL_RES* res = mysql_store_result(cn.getConector());
                    MYSQL_ROW row = mysql_fetch_row(res);

                    if (row) {
                        idClienteLocal = stoi(row[0]);
                        mysql_free_result(res);
                        cout << "Cliente 'Consumidor Final' encontrado con ID: " << idClienteLocal << endl;
                    }
                    else {
                        // Crear cliente genérico "C/F"
                        string insertar = "INSERT INTO clientes (nombres, apellidos, nit, genero, telefono, correo_electronico, fechaingreso) "
                            "VALUES ('Consumidor', 'Final', 'C/F', 1, '00000000', 'cf@email.com', NOW());";
                        if (!mysql_query(cn.getConector(), insertar.c_str())) {
                            idClienteLocal = mysql_insert_id(cn.getConector());
                            cout << "Cliente 'Consumidor Final' creado con ID: " << idClienteLocal << endl;
                        }
                        else {
                            cout << "Error al crear cliente genérico: " << mysql_error(cn.getConector()) << endl;
                            cn.cerrar_conexion();
                            return;
                        }
                    }
                }
                else {
                    cout << "Error al buscar cliente genérico: " << mysql_error(cn.getConector()) << endl;
                    cn.cerrar_conexion();
                    return;
                }
            }
            else {
                // Buscar si el NIT ya está registrado
                consultaCliente = "SELECT idCliente FROM clientes WHERE nit = '" + nit + "';";
                if (!mysql_query(cn.getConector(), consultaCliente.c_str())) {
                    MYSQL_RES* res = mysql_store_result(cn.getConector());
                    if (mysql_num_rows(res) > 0) {
                        MYSQL_ROW row = mysql_fetch_row(res);
                        idClienteLocal = stoi(row[0]);
                        mysql_free_result(res);
                        cout << "Cliente encontrado con ID: " << idClienteLocal << endl;
                    }
                    else {
                        mysql_free_result(res);
                        // Crear nuevo cliente solicitando datos
                        string nombres, apellidos, telefono, correo;
                        bool genero;
                        cin.ignore();
                        cout << "Cliente no encontrado. Ingrese datos para nuevo cliente:\n";
                        cout << "Nombres: "; getline(cin, nombres);
                        cout << "Apellidos: "; getline(cin, apellidos);
                        cout << "Genero (1=Masculino, 0=Femenino): "; cin >> genero; cin.ignore();
                        cout << "Telefono: "; getline(cin, telefono);
                        cout << "Correo: "; getline(cin, correo);

                        string insertar = "INSERT INTO clientes (nombres, apellidos, nit, genero, telefono, correo_electronico, fechaingreso) VALUES ('" +
                            nombres + "', '" + apellidos + "', '" + nit + "', " + to_string(genero) + ", '" + telefono + "', '" + correo + "', NOW());";

                        if (!mysql_query(cn.getConector(), insertar.c_str())) {
                            idClienteLocal = mysql_insert_id(cn.getConector());
                            cout << "Nuevo cliente creado con ID: " << idClienteLocal << endl;
                        }
                        else {
                            cout << "Error al insertar nuevo cliente: " << mysql_error(cn.getConector()) << endl;
                            cn.cerrar_conexion();
                            return;
                        }
                    }
                }
                else {
                    cout << "Error al buscar cliente: " << mysql_error(cn.getConector()) << endl;
                    cn.cerrar_conexion();
                    return;
                }
            }

            // Asignar ID cliente y NIT al objeto
            idCliente = idClienteLocal;
            nitCliente = nit;

            mostrarEmpleados(cn.getConector());
            cout << "\nIngrese ID Empleado: ";
            cin >> idEmpleado;

            setNitCliente(nitCliente);
            setIdEmpleado(idEmpleado);

            noFactura = generarNoFactura(cn.getConector());
            serie = generarSerie(noFactura);

            string query = "INSERT INTO ventas (noFactura, serie, fechafactura, idCliente, idEmpleado, fechaingreso) VALUES (" +
                to_string(noFactura) + ", '" + serie + "', now(), " +
                to_string(idClienteLocal) + ", " + to_string(idEmpleado) + ", now());";

            if (!mysql_query(cn.getConector(), query.c_str())) {
                idVenta = mysql_insert_id(cn.getConector());
                cout << "\nVenta creada con ID: " << idVenta << endl;

                char respuesta = 's';

                while (respuesta == 's' || respuesta == 'S') {
                    int idProducto;
                    int cantidad;
                    mostrarProductos(cn.getConector());
                    cout << "\nID Producto: ";
                    cin >> idProducto;

                    cout << "Cantidad: ";
                    cin >> cantidad;

                    // Consultar el precio_costo del producto
                    string consultaProducto = "SELECT precio_costo FROM productos WHERE idProducto = " + to_string(idProducto) + ";";
                    if (!mysql_query(cn.getConector(), consultaProducto.c_str())) {
                        MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                        MYSQL_ROW fila = mysql_fetch_row(resultado);

                        if (fila) {
                            double precio = stod(fila[0]);
                            mysql_free_result(resultado);

                            string detalleQuery = "INSERT INTO ventas_detalle(idVenta, idProducto, cantidad, precio_unitario) VALUES (" +
                                to_string(idVenta) + ", " + to_string(idProducto) + ", " + to_string(cantidad) + ", " + to_string(precio) + ");";

                            if (!mysql_query(cn.getConector(), detalleQuery.c_str())) {
                                cout << "Detalle agregado correctamente.\n";
                            }
                            else {
                                cout << "Error al insertar detalle: " << mysql_error(cn.getConector()) << endl;
                            }
                        }
                        else {
                            cout << "Producto no encontrado.\n";
                            mysql_free_result(resultado);
                        }
                    }
                    else {
                        cout << "Error consultando producto: " << mysql_error(cn.getConector()) << endl;
                    }

                    cout << "¿Desea agregar otro producto? (s/n): ";
                    cin >> respuesta;
                }
            }
            else {
                cout << "Error al crear venta: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
        else {
            cout << "Fallo la conexion a la base de datos.\n";
        }
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
                string nombres, apellidos, telefono, correo, nit, fechaIngreso;
                bool genero;

                cout << "Ingrese nombres: "; getline(cin, nombres);
                cout << "Ingrese apellidos: "; getline(cin, apellidos);
                cout << "Ingrese nit: "; getline(cin, nit);
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




    void leerVentas() {
        ConexionBD cn;
        MYSQL_ROW fila, filaDetalle;
        MYSQL_RES* resultado, * resultadoDetalle;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query =
                "SELECT v.idVenta, v.nofactura, v.serie, v.fechafactura, "
                "c.nombres AS nombreCliente, e.nombres AS nombreEmpleado, v.fechaingreso "
                "FROM ventas v "
                "JOIN clientes c ON v.idCliente = c.idCliente "
                "JOIN empleados e ON v.idEmpleado = e.idEmpleado "
                "ORDER BY v.fechaingreso DESC;";
            cout<< "________________Datos de las Ventas__________________\n";
            if (!mysql_query(cn.getConector(), query.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                while ((fila = mysql_fetch_row(resultado))) {
                   
                    cout
                     <<
                        "\n-------------------------------------------------------------------\n"
                        << "ID Venta: " << fila[0]
                        << ", Factura: " << fila[1]
                        << ", Serie: " << fila[2]
                        << ", Fecha: " << fila[3]
                        << ", Cliente: " << fila[4]
                        << ", Empleado: " << fila[5]
                        << ", Ingreso: " << fila[6]
                        << endl;

                    // Traer detalles de esta venta
                    string queryDetalle =
                        "SELECT vd.idProducto, p.producto, m.marca, vd.cantidad, vd.precio_unitario "
                        "FROM ventas_detalle vd "
                        "JOIN productos p ON vd.idProducto = p.idProducto "
                        "JOIN marcas m ON p.idMarca = m.idMarca "
                        "WHERE vd.idVenta = " + string(fila[0]) + ";";

                    if (!mysql_query(cn.getConector(), queryDetalle.c_str())) {
                        resultadoDetalle = mysql_store_result(cn.getConector());
                        while ((filaDetalle = mysql_fetch_row(resultadoDetalle))) {
                            cout << "  -> ID Producto: " << filaDetalle[0]
                                << ", Producto: " << filaDetalle[1]
                                << ", Marca: " << filaDetalle[2]
                                << ", Cantidad: " << filaDetalle[3]
                                << ", Precio Unitario: " << filaDetalle[4]
                                << endl;
                        }
                        mysql_free_result(resultadoDetalle);
                    }
                    else {
                        cout << "Error al leer detalles: " << mysql_error(cn.getConector()) << endl;
                    }

                }
                mysql_free_result(resultado);
            }
            else {
                cout << "Error al leer ventas: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
    }

    void actualizarVenta() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            cout << "Ingrese el ID de la venta que desea actualizar: ";
            cin >> idVenta;

            cout << "Nuevo numero de factura: ";
            cin >> noFactura;
            cout << "Nueva serie: ";
            cin >> serie;
            cout << "Nueva fecha (YYYY-MM-DD): ";
            cin >> fechaFactura;
            cout << "Nuevo ID cliente: ";
            cin >> idCliente;
            cout << "Nuevo ID empleado: ";
            cin >> idEmpleado;

            string query = "UPDATE ventas SET nofactura = " + to_string(noFactura) +
                ", serie = '" + serie + "', fechafactura = '" + fechaFactura +
                "', idCliente = " + to_string(idCliente) +
                ", idEmpleado = " + to_string(idEmpleado) +
                " WHERE idVenta = " + to_string(idVenta) + ";";

            if (!mysql_query(cn.getConector(), query.c_str())) {
                cout << "Venta actualizada correctamente.\n";

                // Eliminar detalles anteriores
                string eliminarDetalles = "DELETE FROM ventas_detalle WHERE idVenta = " + to_string(idVenta) + ";";
                if (!mysql_query(cn.getConector(), eliminarDetalles.c_str())) {
                    int cantidadDetalles;
                    cout << "Ingrese la cantidad de productos nuevos: ";
                    cin >> cantidadDetalles;

                    for (int i = 0; i < cantidadDetalles; i++) {
                        int idProducto;
                        string cantidad;
                        double precio;

                        cout << "\nID Producto: "; cin >> idProducto;
                        cout << "Cantidad: "; cin >> cantidad;
                        cout << "Precio unitario: "; cin >> precio;

                        string detalleQuery = "INSERT INTO ventas_detalle(idVenta, idProducto, cantidad, precio_unitario) VALUES (" +
                            to_string(idVenta) + ", " + to_string(idProducto) + ", '" + cantidad + "', " + to_string(precio) + ");";

                        if (!mysql_query(cn.getConector(), detalleQuery.c_str())) {
                            cout << "Detalle agregado correctamente.\n";
                        }
                        else {
                            cout << "Error al agregar detalle: " << mysql_error(cn.getConector()) << endl;
                        }
                    }
                }
                else {
                    cout << "Error al eliminar detalles anteriores: " << mysql_error(cn.getConector()) << endl;
                }
            }
            else {
                cout << "Error al actualizar venta: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
        else {
            cout << "Fallo la conexion a la base de datos.\n";
        }
    }



    void eliminarVentaConDetalle() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string borrarDetalles = "DELETE FROM ventas_detalle WHERE idVenta = " + to_string(idVenta) + ";";
            string borrarVenta = "DELETE FROM ventas WHERE idVenta = " + to_string(idVenta) + ";";

            if (!mysql_query(cn.getConector(), borrarDetalles.c_str()) &&
                !mysql_query(cn.getConector(), borrarVenta.c_str())) {
                cout << "Venta y detalles eliminados correctamente.\n";
            }
            else {
                cout << "Error al eliminar: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
    }
};
