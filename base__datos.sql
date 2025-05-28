-- MySQL dump 10.13  Distrib 8.0.41, for Win64 (x86_64)
--
-- Host: localhost    Database: proyectofinal
-- ------------------------------------------------------
-- Server version	8.0.41

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Dumping data for table `clientes`
--

LOCK TABLES `clientes` WRITE;
/*!40000 ALTER TABLE `clientes` DISABLE KEYS */;
INSERT INTO `clientes` VALUES (2,'Keily','Perez','54415-9',_binary '','47486250','ll981755@gmail.com','2022-01-31 23:59:59'),(3,'Kevin','Chinchilla','58563-9',_binary '','5454','lll','2025-01-31 23:59:59'),(4,'Fernanda','Solares','51203-9',_binary '\0','4444','pppp','2024-01-21 23:59:59'),(5,'HELEN','PPP','44',_binary '\0','5252','LLHJ5','2025-05-27 22:41:52');
/*!40000 ALTER TABLE `clientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `compras`
--

LOCK TABLES `compras` WRITE;
/*!40000 ALTER TABLE `compras` DISABLE KEYS */;
INSERT INTO `compras` VALUES (1,84,2,'2015-09-09','2025-05-24 13:17:35'),(2,52,2,'2014-09-09','2025-05-24 13:17:35'),(3,4,2,'2015-09-09','2025-05-25 12:35:55');
/*!40000 ALTER TABLE `compras` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `compras_detalle`
--

LOCK TABLES `compras_detalle` WRITE;
/*!40000 ALTER TABLE `compras_detalle` DISABLE KEYS */;
INSERT INTO `compras_detalle` VALUES (3,2,2,5,52.00),(4,1,2,58,54.00),(5,3,1,2,45.00),(6,3,2,2,45.00);
/*!40000 ALTER TABLE `compras_detalle` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `empleados`
--

LOCK TABLES `empleados` WRITE;
/*!40000 ALTER TABLE `empleados` DISABLE KEYS */;
INSERT INTO `empleados` VALUES (1,'Luis','Luch','Guatemala','5223','12345697',_binary '','2005-06-06',1,'2010-02-02','2010-01-01 15:30:00'),(2,'Luisa','Perez','Belice','415263','14795623',_binary '\0','2002-09-16',4,'2010-09-06','2009-12-31 23:59:59'),(4,'Abner','Lopez','Mexico','9562','1459632014',_binary '','2010-04-01',6,'2023-06-19','2023-07-25 17:15:10'),(6,'Melissa','Castillo','Guatemala','45123','321654972',_binary '\0','2004-06-06',7,'2022-09-09','2022-11-20 14:45:30'),(11,'pp','p','p','p','p',_binary '','2010-09-09',2,'2020-03-03','2022-01-31 23:59:59'),(12,'k','k','k','k','k',_binary '','2010-05-05',8,'2040-08-08','2022-01-31 23:59:59'),(13,'keily','lopez','mexico','454545','4545454',_binary '\0','2006-09-09',3,'2016-06-06','2013-03-03 08:05:05'),(14,'l','l','l','4','4',_binary '','2016-09-09',2,'2015-08-08','2025-05-25 12:27:53'),(15,'luis','curtidor','mecio','4747','4444444',_binary '','2006-09-09',3,'2015-06-06','2025-05-27 21:55:09');
/*!40000 ALTER TABLE `empleados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `marcas`
--

LOCK TABLES `marcas` WRITE;
/*!40000 ALTER TABLE `marcas` DISABLE KEYS */;
INSERT INTO `marcas` VALUES (1,'Toyota '),(2,'Granada');
/*!40000 ALTER TABLE `marcas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `productos`
--

LOCK TABLES `productos` WRITE;
/*!40000 ALTER TABLE `productos` DISABLE KEYS */;
INSERT INTO `productos` VALUES (1,'cafe',1,'kkkk','l',54.00,59.00,6,'2010-09-09 00:00:00'),(2,'chocolate',2,'chocolatee','lol',10.00,15.00,90,'2025-09-07 10:05:08'),(3,'tortriz',2,'lll','lll',1.00,2.00,500,'2026-09-07 10:05:08'),(4,'tostadas',2,'lol','l',20.00,25.00,500,'2025-05-27 22:17:14');
/*!40000 ALTER TABLE `productos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `proveedores`
--

LOCK TABLES `proveedores` WRITE;
/*!40000 ALTER TABLE `proveedores` DISABLE KEYS */;
INSERT INTO `proveedores` VALUES (1,'juanito','45123-7','mexico','4745120'),(2,'maria','4545-7','guatemala','320152');
/*!40000 ALTER TABLE `proveedores` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `puestos`
--

LOCK TABLES `puestos` WRITE;
/*!40000 ALTER TABLE `puestos` DISABLE KEYS */;
INSERT INTO `puestos` VALUES (1,'Gerente'),(2,'Supervisor'),(3,'Cajero'),(4,'Vendedor'),(5,'Operario'),(6,'Contador'),(7,'Recepcionista'),(8,'Tecnico'),(12,'Recursos Humanos');
/*!40000 ALTER TABLE `puestos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `ventas`
--

LOCK TABLES `ventas` WRITE;
/*!40000 ALTER TABLE `ventas` DISABLE KEYS */;
INSERT INTO `ventas` VALUES (4,5,'1','2016-09-09',2,2,'2025-05-24 12:19:42'),(5,4745,'8','2014-08-08',3,6,'2025-05-24 12:27:12'),(6,5454,'2','2015-09-09',2,2,'2025-05-25 12:03:43'),(7,454,'4','2016-09-09',2,2,'2025-05-25 12:16:29'),(8,454,'5','2015-09-09',2,2,'2025-05-25 12:29:56'),(9,44,'4','2010-05-05',2,2,'2025-05-27 21:02:21'),(10,5455,'w','2025-05-27',2,2,'2025-05-27 21:17:03'),(13,5456,'w','2025-05-27',2,14,'2025-05-27 21:33:24'),(14,5457,'w','2025-05-27',4,11,'2025-05-27 21:38:46'),(15,5458,'w','2025-05-27',3,4,'2025-05-27 21:41:36'),(16,5459,'w','2025-05-27',3,6,'2025-05-27 21:42:59'),(17,5460,'w','2025-05-27',4,12,'2025-05-27 21:46:00'),(18,5461,'w','2025-05-27',4,4,'2025-05-27 21:46:22'),(19,5462,'w','2025-05-27',2,1,'2025-05-27 21:47:26'),(20,5463,'w','2025-05-27',2,1,'2025-05-27 21:48:22');
/*!40000 ALTER TABLE `ventas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `ventas_detalle`
--

LOCK TABLES `ventas_detalle` WRITE;
/*!40000 ALTER TABLE `ventas_detalle` DISABLE KEYS */;
INSERT INTO `ventas_detalle` VALUES (1,4,1,'4',54.00),(2,4,1,'4',56.00),(3,4,1,'6',58.00),(4,4,1,'9',544.00),(6,5,2,'5',18.00),(7,6,1,'45',45.00),(8,7,1,'1',1.00),(9,7,1,'1',1.00),(10,8,1,'2',45.00),(11,10,2,'2',42.00),(12,10,2,'2',5.00),(13,15,1,'1',54.00),(14,15,2,'1',10.00),(15,16,1,'5',54.00),(16,17,1,'5',54.00),(17,20,2,'5',10.00);
/*!40000 ALTER TABLE `ventas_detalle` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'proyectofinal'
--

--
-- Dumping routines for database 'proyectofinal'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-05-27 22:51:50
