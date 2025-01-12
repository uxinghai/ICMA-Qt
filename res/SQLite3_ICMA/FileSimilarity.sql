/*
 Navicat Premium Data Transfer

 Source Server         : ICMA
 Source Server Type    : SQLite
 Source Server Version : 3035005 (3.35.5)
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3035005 (3.35.5)
 File Encoding         : 65001

 Date: 11/01/2025 15:14:11
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for FileSimilarity
-- ----------------------------
DROP TABLE IF EXISTS "FileSimilarity";
CREATE TABLE "FileSimilarity" (
  "file_id1" integer NOT NULL,
  "file_id2" integer NOT NULL,
  " similarity_score" real,
  "similarity_type" TEXT,
  "calculation_date" DATETIME DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY ("file_id1", "file_id2"),
  CONSTRAINT "fk1" FOREIGN KEY ("file_id1") REFERENCES "Files" ("file_id") ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT "fk2" FOREIGN KEY ("file_id2") REFERENCES "Files" ("file_id") ON DELETE CASCADE ON UPDATE NO ACTION
);

PRAGMA foreign_keys = true;
