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
-- Table structure for table `purchase_store`
--

DROP TABLE IF EXISTS `purchase_store`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `purchase_store` (
  `purchase_id` int NOT NULL AUTO_INCREMENT,
  `book_id` int DEFAULT NULL,
  `purchase_from` enum('private_person','stockpile') NOT NULL,
  `book_price` int NOT NULL,
  `count` int NOT NULL DEFAULT '1',
  `purchase_date` date NOT NULL,
  PRIMARY KEY (`purchase_id`),
  KEY `book_id_ps_idx` (`book_id`),
  CONSTRAINT `book_id_ps` FOREIGN KEY (`book_id`) REFERENCES `book` (`book_id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase_store`
--

LOCK TABLES `purchase_store` WRITE;
/*!40000 ALTER TABLE `purchase_store` DISABLE KEYS */;
INSERT INTO `purchase_store` VALUES (1,1,'private_person',20,5,'2006-12-01'),(2,2,'stockpile',15,10,'2010-07-01'),(3,3,'private_person',30,12,'1998-12-01'),(4,7,'private_person',12,5,'2019-12-01'),(5,9,'stockpile',25,4,'2019-10-11'),(6,5,'stockpile',20,1,'2013-01-01'),(7,6,'stockpile',19,1,'2001-01-01'),(8,12,'private_person',5,1,'2002-01-01'),(9,13,'private_person',2,1,'2001-02-11'),(10,16,'private_person',12,1,'2001-02-12');
/*!40000 ALTER TABLE `purchase_store` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-08-05 23:36:51
