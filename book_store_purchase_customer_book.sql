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
-- Table structure for table `purchase_customer_book`
--

DROP TABLE IF EXISTS `purchase_customer_book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `purchase_customer_book` (
  `purchase_id` int NOT NULL,
  `book_id` int NOT NULL,
  `book_eddition_id` int DEFAULT NULL,
  `price` int NOT NULL,
  PRIMARY KEY (`purchase_id`,`book_id`),
  KEY `book_id_pcb_idx` (`book_id`),
  KEY `book_eddition_id_pcb_idx` (`book_eddition_id`),
  CONSTRAINT `book_id_pcb` FOREIGN KEY (`book_id`) REFERENCES `book` (`book_id`),
  CONSTRAINT `purchase_id_pcb` FOREIGN KEY (`purchase_id`) REFERENCES `purchase_customer` (`purchase_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase_customer_book`
--

LOCK TABLES `purchase_customer_book` WRITE;
/*!40000 ALTER TABLE `purchase_customer_book` DISABLE KEYS */;
INSERT INTO `purchase_customer_book` VALUES (1,1,1,30),(1,2,10,120),(2,2,11,200),(3,7,3,29),(4,9,0,58),(5,3,12,389),(5,5,0,78),(6,6,0,331),(7,9,0,120),(8,5,13,78),(8,7,0,56),(9,1,9,19),(10,7,0,79),(11,9,0,120),(12,3,0,700),(12,16,0,600);
/*!40000 ALTER TABLE `purchase_customer_book` ENABLE KEYS */;
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
