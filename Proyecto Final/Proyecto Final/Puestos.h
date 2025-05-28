

#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <sstream>
#include <string>

using namespace std;

class Puestos {
protected:
    int idPuestos;
    string Puesto;
public:
    Puestos() {}
    Puestos(int id_puesto, string puesto) {
        idPuestos = id_puesto;
        Puesto = puesto;
    }

    // Setters
    void setIdPuesto(int id) { idPuestos = id; }
    void setPuesto(string p) { Puesto = p; }


    // Getters
    int getIdPuestr() { return idPuestos; }
    string getPuesto() { return Puesto; }

    // CRUD
    void crear() {
        int q_estado;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "INSERT INTO puestos (idPuesto, puesto) VALUES (" + to_string(idPuestos) + ", '" + Puesto + "');";

            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Puesto agregado exitosamente.\n";
                int id = mysql_insert_id(cn.getConector());
                cout << "ID asignado: " << id << endl;
            }
            else {
                cout << "Error al insertar puesto.\n" << mysql_error(cn.getConector());
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
        cout << "________________Datos de los Puestos__________________\n" << endl;
        if (cn.getConector()) {
            string consulta = "SELECT * FROM puestos;";
            const char* c = consulta.c_str();
            mysql_query(cn.getConector(), c);

            resultado = mysql_store_result(cn.getConector());

            while ((fila = mysql_fetch_row(resultado))) {
                cout << "ID: " << fila[0] << ", Puesto: " << fila[1]  << "\n-------------------------------------------------------------------" << endl;
            }
        }
        else {
            cout << "Error en la conexion.\n";
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idStr = to_string(idPuestos);
            string consulta = "UPDATE puestos SET puesto='" + Puesto +
                "' WHERE idPuesto=" + idStr + ";";

            const char* c = consulta.c_str();
            if (!mysql_query(cn.getConector(), c)) {
                cout << "Puesto actualizado correctamente.\n";
            }
            else {
                cout << "Error al actualizar puesto.\n" << mysql_error(cn.getConector()) << endl;
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
            string idStr = to_string(idPuestos);
            string consulta = "DELETE FROM puestos WHERE idPuesto=" + idStr + ";";
            const char* c = consulta.c_str();

            if (!mysql_query(cn.getConector(), c)) {
                cout << "Puesto eliminado correctamente.\n";
            }
            else {
                cout << "Error al eliminar puesto.\n" << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }

};
