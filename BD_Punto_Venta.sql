CREATE DATABASE IF NOT EXISTS PuntoVenta;
USE PuntoVenta;

CREATE TABLE Puestos (
    idPuesto SMALLINT PRIMARY KEY,
    puesto VARCHAR(50)
);

CREATE TABLE Empleados (
    idEmpleado INT PRIMARY KEY,
    nombres VARCHAR(60),
    apellidos VARCHAR(60),
    direccion VARCHAR(80),
    telefono VARCHAR(25),
    DPI VARCHAR(15),
    genero BIT,
    fecha_nacimiento DATE,
    idPuesto SMALLINT,
    fecha_inicio_labores DATE,
    fechaingreso DATETIME,
    FOREIGN KEY (idPuesto) REFERENCES Puestos(idPuesto)
);

CREATE TABLE Clientes (
    idCliente INT PRIMARY KEY,
    nombres VARCHAR(60),
    apellidos VARCHAR(60),
    NIT VARCHAR(12),
    genero BIT,
    telefono VARCHAR(25),
    correo_electronico VARCHAR(45),
    fechaingreso DATETIME
);


CREATE TABLE Marcas (
    idMarca SMALLINT PRIMARY KEY,
    marca VARCHAR(50)
);


CREATE TABLE Productos (
    idProducto INT PRIMARY KEY,
    producto VARCHAR(50),
    idMarca SMALLINT,
    Descripcion VARCHAR(100),
    Imagen VARCHAR(30),
    precio_costo DECIMAL(8,2),
    precio_venta DECIMAL(8,2),
    existencia INT,
    fecha_ingreso DATETIME,
    FOREIGN KEY (idMarca) REFERENCES Marcas(idMarca)
);


CREATE TABLE Ventas (
    idVenta INT PRIMARY KEY,
    nofactura INT,
    serie CHAR(1),
    fechafactura DATE,
    idCliente INT,
    idEmpleado INT,
    fechaingreso DATETIME,
    FOREIGN KEY (idCliente) REFERENCES Clientes(idCliente),
    FOREIGN KEY (idEmpleado) REFERENCES Empleados(idEmpleado)
);

-- Tabla: Ventas_detalle
CREATE TABLE Ventas_detalle (
    idventa_detalle BIGINT PRIMARY KEY,
    idVenta INT,
    idProducto INT,
    cantidad VARCHAR(45),
    precio_unitario DECIMAL(8,2),
    FOREIGN KEY (idVenta) REFERENCES Ventas(idVenta),
    FOREIGN KEY (idProducto) REFERENCES Productos(idProducto)
);

CREATE TABLE Proveedores (
    idProveedor INT PRIMARY KEY,
    proveedor VARCHAR(60),
    nit VARCHAR(12),
    direccion VARCHAR(80),
    telefono VARCHAR(25)
);


CREATE TABLE Compras (
    idCompra INT PRIMARY KEY,
    no_orden_compra INT,
    idProveedor INT,
    fecha_orden DATE,
    fechaingreso DATETIME,
    FOREIGN KEY (idProveedor) REFERENCES Proveedores(idProveedor)
);

CREATE TABLE Compras_detalle (
    idcompra_detalle BIGINT PRIMARY KEY,
    idCompra INT,
    idProducto INT,
    cantidad INT,
    precio_costo_unitario DECIMAL(8,2),
    FOREIGN KEY (idCompra) REFERENCES Compras(idCompra),
    FOREIGN KEY (idProducto) REFERENCES Productos(idProducto)
);
