#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Marcas {
private:
    int idMarca = 0;
    string marca;

public:
    Marcas() {}

    Marcas(int id, string m) : idMarca(id), marca(m) {}

    void setIdMarca(int id) { idMarca = id; }
    void setMarca(string m) { marca = m; }

    int getIdMarca() { return idMarca; }
    string getMarca() { return marca; }

    void crear() {
        int q_estado;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "INSERT INTO marcas (marca) VALUES ('" + marca + "');";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Marca agregada exitosamente.\n";
                int id = mysql_insert_id(cn.getConector());
                cout << "Nuevo ID asignado: " << id << endl;
            }
            else {
                cout << "Error al insertar marca.\n";
            }
        }
        else {
            cout << "Error en la conexión a la base de datos.\n";
        }
        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        if (cn.getConector()) {
            string consulta = "SELECT * FROM marcas ORDER BY idMarca;";
            const char* c = consulta.c_str();
            mysql_query(cn.getConector(), c);
            resultado = mysql_store_result(cn.getConector());

            cout << "\n--- Lista de Marcas ---\n";
            while ((fila = mysql_fetch_row(resultado))) {
                cout << "ID: " << fila[0] << ", Marca: " << fila[1] << endl;
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idStr = to_string(idMarca);
            string consulta = "UPDATE marcas SET marca='" + marca + "' WHERE idMarca=" + idStr + ";";
            const char* c = consulta.c_str();
            if (!mysql_query(cn.getConector(), c)) {
                cout << "Marca actualizada correctamente.\n";
            }
            else {
                cout << "Error al actualizar marca.\n";
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idStr = to_string(idMarca);
            string consulta = "DELETE FROM marcas WHERE idMarca=" + idStr + ";";
            const char* c = consulta.c_str();

            if (!mysql_query(cn.getConector(), c)) {
                cout << "Marca eliminada correctamente.\n";
            }
            else {
                cout << "Error al eliminar marca.\n";
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }
};