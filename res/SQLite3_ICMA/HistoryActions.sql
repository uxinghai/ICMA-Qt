/*
 Navicat Premium Data Transfer

 Source Server         : ICMA
 Source Server Type    : SQLite
 Source Server Version : 3035005 (3.35.5)
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3035005 (3.35.5)
 File Encoding         : 65001

 Date: 11/01/2025 15:14:28
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for HistoryActions
-- ----------------------------
DROP TABLE IF EXISTS "HistoryActions";
CREATE TABLE "HistoryActions" (
  "action_id" integer NOT NULL PRIMARY KEY AUTOINCREMENT,
  "file_id" integer,
  "action_name" text NOT NULL,
  "action_date" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  "action_details" TEXT,
  CONSTRAINT "fk1" FOREIGN KEY ("file_id") REFERENCES "Files" ("file_id") ON DELETE SET NULL ON UPDATE NO ACTION
);

-- ----------------------------
-- Auto increment value for HistoryActions
-- ----------------------------

PRAGMA foreign_keys = true;
