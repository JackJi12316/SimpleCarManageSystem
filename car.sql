/*
 Navicat Premium Data Transfer

 Source Server         : jack
 Source Server Type    : MySQL
 Source Server Version : 80024
 Source Host           : localhost:3306
 Source Schema         : car

 Target Server Type    : MySQL
 Target Server Version : 80024
 File Encoding         : 65001

 Date: 24/06/2021 12:24:12
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for bus
-- ----------------------------
DROP TABLE IF EXISTS `bus`;
CREATE TABLE `bus`  (
  `no` int NOT NULL AUTO_INCREMENT COMMENT '编号',
  `head_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '前车牌',
  `tail_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '后车牌',
  `driver` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '司机',
  `brand` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '品牌',
  `mileage` float(255, 2) NULL DEFAULT NULL COMMENT '里程数',
  `price` decimal(10, 2) NULL DEFAULT NULL COMMENT '价格',
  PRIMARY KEY (`no`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of bus
-- ----------------------------
INSERT INTO `bus` VALUES (1, '鲁B', '12345', '张三', '宇通', 25000.65, 300.00);
INSERT INTO `bus` VALUES (2, '鲁A', '12345', '李丽', '奔驰', 2000.00, 400.00);

-- ----------------------------
-- Table structure for saloon
-- ----------------------------
DROP TABLE IF EXISTS `saloon`;
CREATE TABLE `saloon`  (
  `no` int NOT NULL AUTO_INCREMENT,
  `head_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `tail_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `driver` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `brand` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mileage` float(255, 2) NULL DEFAULT NULL,
  `price` decimal(10, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`no`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of saloon
-- ----------------------------
INSERT INTO `saloon` VALUES (1, '鲁B', '23456', '李四', '奔驰', 2000.00, 80.00);

-- ----------------------------
-- Table structure for suv
-- ----------------------------
DROP TABLE IF EXISTS `suv`;
CREATE TABLE `suv`  (
  `no` int NOT NULL AUTO_INCREMENT,
  `head_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `tail_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `driver` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `brand` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mileage` float(255, 2) NULL DEFAULT NULL,
  `price` decimal(10, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`no`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of suv
-- ----------------------------
INSERT INTO `suv` VALUES (1, '鲁B', '34567', '王五', 'Jeep', 2000.00, 20.00);

-- ----------------------------
-- Table structure for truck
-- ----------------------------
DROP TABLE IF EXISTS `truck`;
CREATE TABLE `truck`  (
  `no` int NOT NULL AUTO_INCREMENT,
  `head_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `tail_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `driver` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `brand` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mileage` float(255, 2) NULL DEFAULT NULL,
  `price` decimal(10, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`no`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of truck
-- ----------------------------
INSERT INTO `truck` VALUES (1, '鲁B', '45678', '赵六', '奔驰', 3000.00, 100.00);

-- ----------------------------
-- Table structure for van
-- ----------------------------
DROP TABLE IF EXISTS `van`;
CREATE TABLE `van`  (
  `no` int NOT NULL AUTO_INCREMENT,
  `head_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `tail_num` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `driver` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `brand` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mileage` float(255, 2) NULL DEFAULT NULL,
  `price` decimal(10, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`no`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of van
-- ----------------------------
INSERT INTO `van` VALUES (1, '鲁B', '65478', '李华', '长安', 2000.00, 10.00);

SET FOREIGN_KEY_CHECKS = 1;
