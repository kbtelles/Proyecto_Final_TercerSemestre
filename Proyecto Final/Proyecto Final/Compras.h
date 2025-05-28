#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

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

    // Crear compra con detalles
    void crearCompraConDetalle() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO compras(no_orden_compra, idProveedor, fecha_orden, fechaingreso) VALUES (" +
                to_string(noOrdenCompra) + ", " + to_string(idProveedor) + ", now(), now());";


            if (!mysql_query(cn.getConector(), query.c_str())) {
                idCompra = mysql_insert_id(cn.getConector());
                cout << "\nCompra creada con ID: " << idCompra << endl;

                int cantidadDetalles;
                cout << "Ingrese la cantidad de productos: ";
                cin >> cantidadDetalles;

                for (int i = 0; i < cantidadDetalles; i++) {
                    int idProducto, cantidad;
                    double precio;

                    cout << "\nID Producto: "; cin >> idProducto;
                    cout << "Cantidad: "; cin >> cantidad;
                    cout << "Precio Costo Unitario: "; cin >> precio;

                    string detalleQuery = "INSERT INTO compras_detalle(idCompra, idProducto, cantidad, precio_costo_unitario) VALUES (" +
                        to_string(idCompra) + ", " + to_string(idProducto) + ", " + to_string(cantidad) + ", " + to_string(precio) + ");";

                    if (!mysql_query(cn.getConector(), detalleQuery.c_str())) {
                        cout << "Detalle agregado correctamente.\n";
                    }
                    else {
                        cout << "Error al insertar detalle: " << mysql_error(cn.getConector()) << endl;
                    }
                }
            }
            else {
                cout << "Error al crear compra: " << mysql_error(cn.getConector()) << endl;
            }
            cn.cerrar_conexion();
        }
        else {
            cout << "Fallo la conexion a la base de datos.\n";
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
            cout << "________________Datos de las Ventas__________________\n";
            if (!mysql_query(cn.getConector(), query.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                while ((fila = mysql_fetch_row(resultado))) {
                    cout 
                        <<"\n-------------------------------------------------------------------\n" 
                        << "\nID Compra: " << fila[0]
                        << ", Orden: " << fila[1]
                        << ", Fecha Orden: " << fila[2]
                        << ", Proveedor: " << fila[3]
                        << ", Ingreso: " << fila[4]
                        << endl;

                    // Detalles
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
            // 1. Actualizar datos principales de la compra
            string query = "UPDATE compras SET no_orden_compra = " + to_string(noOrdenCompra) +
                ", idProveedor = " + to_string(idProveedor) +
                ", fecha_orden = '" + fechaOrden + "' " +
                "WHERE idCompra = " + to_string(idCompra) + ";";

            if (!mysql_query(cn.getConector(), query.c_str())) {
                cout << "\nCompra actualizada correctamente.\n";

                // 2. Borrar detalles viejos para insertar los nuevos
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



    // Eliminar compra con detalles
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
};
   


