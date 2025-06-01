#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>
#include <iomanip> // Para setw

using namespace std;

class Compras {
private:
    int idCompra = 0;
    int noOrdenCompra, idProveedor;
    string fechaOrden;

public:
    // Setters
    void setIdCompra(int id) { idCompra = id; }
    void setNoOrdenCompra(int no) { noOrdenCompra = no; }
    void setIdProveedor(int prov) { idProveedor = prov; }
    void setFechaOrden(string fecha) { fechaOrden = fecha; }


    void mostrarProductos(MYSQL* con) {
        string query = "SELECT idProducto, producto, precio_costo FROM productos;";
        if (!mysql_query(con, query.c_str())) {
            MYSQL_RES* res = mysql_store_result(con);
            MYSQL_ROW row;
            cout << "\n----- PRODUCTOS DISPONIBLES -----\n";
            while ((row = mysql_fetch_row(res))) {
                cout << "ID: " << row[0] << ", Nombre: " << row[1] << ", Costo Unitario: " << row[2] << " " << row[3] << endl;
            }
            mysql_free_result(res);
        }
        else {
            cout << "Error al mostrar PRODUCTOS: " << mysql_error(con) << endl;
        }
    }


    // Crear compra con detalles
    void crearCompraConDetalle() {
        ConexionBD cn;
        
        cn.abrir_conexion();
       
        if (cn.getConector()) {
        
            // Obtener el último número de orden de compra
            int nuevoOrden = 1;
            
            string consultaOrden = "SELECT MAX(no_orden_compra) FROM compras;";
            if (!mysql_query(cn.getConector(), consultaOrden.c_str())) {
                MYSQL_RES* res = mysql_store_result(cn.getConector());
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row[0] != nullptr) {
                    nuevoOrden = atoi(row[0]) + 1;
                }
                mysql_free_result(res);
            }
           
            string query = "INSERT INTO compras(no_orden_compra, idProveedor, fecha_orden, fechaingreso) VALUES (" +
                to_string(nuevoOrden) + ", " + to_string(idProveedor) + ", now(), now());";

            if (!mysql_query(cn.getConector(), query.c_str())) {
                idCompra = mysql_insert_id(cn.getConector());
                cout << "\nCompra creada con ID: " << idCompra << ", Orden No: " << nuevoOrden << endl;

                int cantidadDetalles;
                cout << "Ingrese la cantidad de productos: ";
                cin >> cantidadDetalles;

                for (int i = 0; i < cantidadDetalles; i++) {
                    int idProducto, cantidad;
                    double precio = 0.0;
                    mostrarProductos(cn.getConector());
                    cout << "\nID Producto: "; cin >> idProducto;
                    cout << "Cantidad: "; cin >> cantidad;

                    // Obtener precio_costo desde la tabla productos
                    string consultaPrecio = "SELECT precio_costo FROM productos WHERE idProducto = " + to_string(idProducto) + " LIMIT 1;";
                    if (!mysql_query(cn.getConector(), consultaPrecio.c_str())) {
                        MYSQL_RES* res = mysql_store_result(cn.getConector());
                        MYSQL_ROW row = mysql_fetch_row(res);
                        if (row && row[0] != nullptr) {
                            precio = atof(row[0]);
                        }
                        else {
                            cout << "Producto no encontrado o sin precio. Se omite este detalle.\n";
                            mysql_free_result(res);
                            continue;
                        }
                        mysql_free_result(res);
                    }
                    else {
                        cout << "Error al obtener precio del producto: " << mysql_error(cn.getConector()) << endl;
                        continue;
                    }

                    string detalleQuery = "INSERT INTO compras_detalle(idCompra, idProducto, cantidad, precio_costo_unitario) VALUES (" +
                        to_string(idCompra) + ", " + to_string(idProducto) + ", " + to_string(cantidad) + ", " + to_string(precio) + ");";

                    if (!mysql_query(cn.getConector(), detalleQuery.c_str())) {
                        cout << "Detalle agregado correctamente.\n";
                    }
                    else {
                        cout << "Error al insertar detalle: " << mysql_error(cn.getConector()) << endl;
                    }
                }
                leer_puerto();
                // Imprimir factura al finalizar
                imprimirFacturaCompra();
            }
            else {
                
                cout << "Error al crear compra: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
        else {
            //leer_puerto();
            cout << "Fallo la conexión a la base de datos.\n";
        }
    }

    // Imprimir factura
    void imprimirFacturaCompra() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL_ROW fila, filaDetalle;
        MYSQL_RES* resultado, * resultadoDetalle;

        if (cn.getConector()) {
            string query =
                "SELECT c.idCompra, c.no_orden_compra, c.fecha_orden, p.proveedor, p.nit, c.fechaingreso "
                "FROM compras c "
                "JOIN proveedores p ON c.idProveedor = p.idProveedor "
                "WHERE c.idCompra = " + to_string(idCompra) + " LIMIT 1;";

            if (!mysql_query(cn.getConector(), query.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                if ((fila = mysql_fetch_row(resultado))) {
                    cout << "\n============================================\n";
                    cout << "             FACTURA DE COMPRA              \n";
                    cout << "============================================\n";
                    cout << "ID Compra: " << fila[0] << " | Orden: " << fila[1] << endl;
                    cout << "Fecha Orden: " << fila[2] << endl;
                    cout << "Proveedor: " << fila[3] << endl;
                    cout << "NIT Proveedor: " << fila[4] << endl;
                    cout << "Fecha Ingreso: " << fila[5] << endl;
                    cout << "--------------------------------------------\n";
                }
                mysql_free_result(resultado);
            }

            // Mostrar detalles
            string queryDetalle =
                "SELECT p.producto, cd.cantidad, cd.precio_costo_unitario, "
                "(cd.cantidad * cd.precio_costo_unitario) AS total "
                "FROM compras_detalle cd "
                "JOIN productos p ON cd.idProducto = p.idProducto "
                "WHERE cd.idCompra = " + to_string(idCompra) + ";";

            if (!mysql_query(cn.getConector(), queryDetalle.c_str())) {
                resultadoDetalle = mysql_store_result(cn.getConector());
                double totalGeneral = 0.0;

                cout << left << setw(20) << "Producto" << setw(10) << "Cant." << setw(15) << "P. Unitario" << setw(10) << "Total" << endl;
                cout << "--------------------------------------------\n";

                while ((filaDetalle = mysql_fetch_row(resultadoDetalle))) {
                    double subtotal = atof(filaDetalle[3]);
                    totalGeneral += subtotal;
                    cout << left << setw(20) << filaDetalle[0]
                        << setw(10) << filaDetalle[1]
                        << setw(15) << filaDetalle[2]
                        << setw(10) << filaDetalle[3] << endl;
                }
                cout << "--------------------------------------------\n";
                cout << right << setw(35) << "TOTAL: Q " << totalGeneral << endl;
                cout << "============================================\n";

                mysql_free_result(resultadoDetalle);
            }

            cn.cerrar_conexion();
        }
        else {
            cout << "Error al conectar para imprimir la factura.\n";
        }
    }

    // Leer compras con detalles
    void leerCompras() {
        ConexionBD cn;
        MYSQL_ROW fila, filaDetalle;
        MYSQL_RES* resultado, * resultadoDetalle;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query =
                "SELECT c.idCompra, c.no_orden_compra, c.fecha_orden, p.proveedor, c.fechaingreso "
                "FROM compras c "
                "JOIN proveedores p ON c.idProveedor = p.idProveedor "
                "ORDER BY c.fechaingreso DESC;";
            cout << "________________Datos de las Compras__________________\n";
            if (!mysql_query(cn.getConector(), query.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                while ((fila = mysql_fetch_row(resultado))) {
                    cout
                        << "\n-------------------------------------------------------------------\n"
                        << "\nID Compra: " << fila[0]
                        << ", Orden: " << fila[1]
                        << ", Fecha Orden: " << fila[2]
                        << ", Proveedor: " << fila[3]
                        << ", Ingreso: " << fila[4]
                        << endl;

                    string queryDetalle =
                        "SELECT cd.idProducto, p.producto, cd.cantidad, cd.precio_costo_unitario "
                        "FROM compras_detalle cd "
                        "JOIN productos p ON cd.idProducto = p.idProducto "
                        "WHERE cd.idCompra = " + string(fila[0]) + ";";

                    if (!mysql_query(cn.getConector(), queryDetalle.c_str())) {
                        resultadoDetalle = mysql_store_result(cn.getConector());
                        while ((filaDetalle = mysql_fetch_row(resultadoDetalle))) {
                            cout << "  -> Producto: " << filaDetalle[1]
                                << ", Cantidad: " << filaDetalle[2]
                                << ", Precio Costo Unitario: " << filaDetalle[3]
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
                cout << "Error al leer compras: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
    }

    void actualizarCompraConDetalle() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "UPDATE compras SET " +
                string("idProveedor = ") + to_string(idProveedor) +
                ", fecha_orden = now() " +
                "WHERE idCompra = " + to_string(idCompra) + ";";


            if (!mysql_query(cn.getConector(), query.c_str())) {
                cout << "\nCompra actualizada correctamente.\n";

                string borrarDetalles = "DELETE FROM compras_detalle WHERE idCompra = " + to_string(idCompra) + ";";
                if (!mysql_query(cn.getConector(), borrarDetalles.c_str())) {
                    int cantidadDetalles;
                    cout << "Ingrese la nueva cantidad de productos: ";
                    cin >> cantidadDetalles;

                    for (int i = 0; i < cantidadDetalles; i++) {
                        int idProducto;
                        int cantidad;
                        double precio;

                        cout << "\nID Producto: "; cin >> idProducto;
                        cout << "Cantidad: "; cin >> cantidad;
                        cout << "Precio costo unitario: "; cin >> precio;

                        string detalleQuery = "INSERT INTO compras_detalle(idCompra, idProducto, cantidad, precio_costo_unitario) VALUES (" +
                            to_string(idCompra) + ", " + to_string(idProducto) + ", " +
                            to_string(cantidad) + ", " + to_string(precio) + ");";

                        if (!mysql_query(cn.getConector(), detalleQuery.c_str())) {
                            cout << "Detalle agregado correctamente.\n";
                        }
                        else {
                            cout << "Error al insertar detalle: " << mysql_error(cn.getConector()) << endl;
                        }
                    }
                }
                else {
                    cout << "Error al eliminar detalles anteriores: " << mysql_error(cn.getConector()) << endl;
                }
            }
            else {
                cout << "Error al actualizar compra: " << mysql_error(cn.getConector()) << endl;
            }

            cn.cerrar_conexion();
        }
        else {
            cout << "Fallo la conexión a la base de datos.\n";
        }
    }

    void eliminarCompraConDetalle() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string borrarDetalles = "DELETE FROM compras_detalle WHERE idCompra = " + to_string(idCompra) + ";";
            string borrarCompra = "DELETE FROM compras WHERE idCompra = " + to_string(idCompra) + ";";

            if (!mysql_query(cn.getConector(), borrarDetalles.c_str()) &&
                !mysql_query(cn.getConector(), borrarCompra.c_str())) {
                cout << "Compra y detalles eliminados correctamente.\n";
            }
            else {
                cout << "Error al eliminar: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
    }
    int leer_puerto() {
        HANDLE hSerial = CreateFile(
            L"COM3",              // Nombre del puerto (cámbialo según el que use tu Arduino)
            GENERIC_WRITE,       // Solo vamos a escribir en el puerto
            0,                   // No compartimos el puerto
            NULL,                // Seguridad predeterminada
            OPEN_EXISTING,       // Abrir el puerto solo si ya existe
            0,                   // Sin banderas adicionales
            NULL);               // Sin plantilla de archivo

        // 2. Verificamos si se abrió correctamente
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "Error abriendo el puerto COM" << std::endl;
            return 1;  // Salir con código de error
        }

        // 3. Estructura para configurar el puerto serie
        DCB dcbSerialParams = { 0 };              // Estructura para parámetros del puerto
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);  // Tamaño de la estructura

        // 4. Obtener configuración actual del puerto
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "No se pudo obtener la configuración del puerto" << std::endl;
            CloseHandle(hSerial);  // Cerramos el puerto antes de salir
            return 1;
        }

        // 5. Configurar parámetros del puerto (deben coincidir con Serial.begin(9600))
        dcbSerialParams.BaudRate = CBR_9600;    // Velocidad de transmisión (baudios)
        dcbSerialParams.ByteSize = 8;           // 8 bits por byte
        dcbSerialParams.StopBits = ONESTOPBIT;  // 1 bit de parada
        dcbSerialParams.Parity = NOPARITY;    // Sin paridad

        // 6. Aplicamos la configuración
        if (!SetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "No se pudo configurar el puerto" << std::endl;
            CloseHandle(hSerial);
            return 1;
        }

        // 7. Configurar timeouts de escritura (opcional pero recomendable)
        COMMTIMEOUTS timeouts = { 0 };
        timeouts.WriteTotalTimeoutConstant = 50;  // Tiempo máximo total para escritura
        SetCommTimeouts(hSerial, &timeouts);

        // 8. Preparar el dato a enviar
        DWORD bytesWritten;            // Variable que almacenará cuántos bytes se escribieron
        char data[] = "1";             // Este es el carácter que enviamos al Arduino

        // 9. Enviar el dato por el puerto serial
        if (!WriteFile(hSerial, data, sizeof(data) - 1, &bytesWritten, NULL)) {
            std::cerr << "Error escribiendo en el puerto" << std::endl;
            CloseHandle(hSerial);
            return 1;
        }

        // 10. Confirmar que el pulso fue enviado
        std::cout << "Pulso enviado al Arduino." << std::endl;

        // 11. Cerrar el puerto COM al terminar
        CloseHandle(hSerial);

    };
};
