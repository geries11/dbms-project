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
-- Table structure for table `deliveries`
--

DROP TABLE IF EXISTS `deliveries`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `deliveries` (
  `deliveries_id` int NOT NULL,
  `purchase_id` int NOT NULL,
  `delivery_company` int NOT NULL,
  `status` enum('in_preparation','sent','arrived_and_waiting_for_collection','delivered') NOT NULL,
  `delivery_type` enum('RASHUM','SHLICHIM','fast','pickup','home') NOT NULL,
  `price` int NOT NULL,
  `delivery_date` date NOT NULL,
  PRIMARY KEY (`deliveries_id`),
  KEY `purchase_id_del_idx` (`purchase_id`),
  KEY `delivery_company_idx` (`delivery_company`),
  CONSTRAINT `delivery_company_d` FOREIGN KEY (`delivery_company`) REFERENCES `delivery_company` (`company_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `purchase_id_del` FOREIGN KEY (`purchase_id`) REFERENCES `purchase_customer` (`purchase_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `deliveries`
--

LOCK TABLES `deliveries` WRITE;
/*!40000 ALTER TABLE `deliveries` DISABLE KEYS */;
INSERT INTO `deliveries` VALUES (1,1,1,'delivered','pickup',15,'2020-07-29'),(2,2,1,'in_preparation','home',35,'2020-08-01'),(3,3,2,'sent','RASHUM',8,'2020-06-30'),(5,8,2,'arrived_and_waiting_for_collection','RASHUM',8,'2020-08-15'),(6,3,2,'delivered','SHLICHIM',12,'2020-08-10'),(7,8,1,'delivered','fast',25,'2020-08-10'),(8,12,2,'sent','RASHUM',8,'2010-06-30');
/*!40000 ALTER TABLE `deliveries` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-08-05 23:36:52
