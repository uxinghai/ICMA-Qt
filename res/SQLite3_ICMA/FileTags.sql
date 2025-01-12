/*
 Navicat Premium Data Transfer

 Source Server         : ICMA
 Source Server Type    : SQLite
 Source Server Version : 3035005 (3.35.5)
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3035005 (3.35.5)
 File Encoding         : 65001

 Date: 11/01/2025 15:14:17
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for FileTags
-- ----------------------------
DROP TABLE IF EXISTS "FileTags";
CREATE TABLE "FileTags" (
  "file_id" INTEGER,
  "tag_id" INTEGER,
  "tagged_date" DATETIME DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY ("file_id", "tag_id"),
  CONSTRAINT "fk1" FOREIGN KEY ("file_id") REFERENCES "Files" ("file_id") ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT "fk2" FOREIGN KEY ("tag_id") REFERENCES "Tags" ("tag_id") ON DELETE CASCADE ON UPDATE NO ACTION
);

PRAGMA foreign_keys = true;
