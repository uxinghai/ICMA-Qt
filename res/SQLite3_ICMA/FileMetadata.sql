/*
 Navicat Premium Data Transfer

 Source Server         : ICMA
 Source Server Type    : SQLite
 Source Server Version : 3035005 (3.35.5)
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3035005 (3.35.5)
 File Encoding         : 65001

 Date: 11/01/2025 15:13:47
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for FileMetadata
-- ----------------------------
DROP TABLE IF EXISTS "FileMetadata";
CREATE TABLE "FileMetadata" (
  "file_id" INTEGER NOT NULL,
  "metadata_key" TEXT NOT NULL,
  "metadata_value" TEXT,
  PRIMARY KEY ("file_id", "metadata_key"),
  CONSTRAINT "fk1" FOREIGN KEY ("file_id") REFERENCES "Files" ("file_id") ON DELETE CASCADE ON UPDATE NO ACTION
);

PRAGMA foreign_keys = true;
