-- MySQL dump 10.13  Distrib 8.0.19, for Win64 (x86_64)
--
-- Host: localhost    Database: book_store
-- ------------------------------------------------------
-- Server version	8.0.19

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
-- Table structure for table `purchase_customer`
--

DROP TABLE IF EXISTS `purchase_customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `purchase_customer` (
  `purchase_id` int NOT NULL AUTO_INCREMENT,
  `customer_id` int NOT NULL,
  `employee_id` int DEFAULT NULL,
  `way` enum('random','specific_book','call_phone') NOT NULL,
  `purchase_date` date NOT NULL,
  `payment_method` enum('bit','credit-card','bank-transfer') NOT NULL,
  PRIMARY KEY (`purchase_id`),
  KEY `customer_id_pc_idx` (`customer_id`),
  KEY `employee_id_pc_idx` (`employee_id`),
  CONSTRAINT `customer_id_pc` FOREIGN KEY (`customer_id`) REFERENCES `customer` (`customer_id`),
  CONSTRAINT `employee_id_pc` FOREIGN KEY (`employee_id`) REFERENCES `employees` (`employee_id`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase_customer`
--

LOCK TABLES `purchase_customer` WRITE;
/*!40000 ALTER TABLE `purchase_customer` DISABLE KEYS */;
INSERT INTO `purchase_customer` VALUES (1,1,1,'call_phone','2020-07-27','bank-transfer'),(2,2,1,'random','2020-07-28','bit'),(3,3,2,'specific_book','2020-06-27','bit'),(4,4,2,'random','2020-07-02','bit'),(5,5,2,'call_phone','2015-01-09','bit'),(6,2,3,'specific_book','2020-08-01','bank-transfer'),(7,4,4,'random','2021-05-12','bit'),(8,2,5,'call_phone','2020-08-05','credit-card'),(9,1,5,'call_phone','2020-07-29','bank-transfer'),(10,11,2,'specific_book','2012-12-02','bank-transfer'),(11,2,5,'call_phone','2020-08-05','credit-card'),(12,11,2,'specific_book','2017-02-25','bit');
/*!40000 ALTER TABLE `purchase_customer` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-08-05 23:36:53
