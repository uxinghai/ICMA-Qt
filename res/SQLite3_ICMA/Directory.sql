/*
 Navicat Premium Data Transfer

 Source Server         : ICMA
 Source Server Type    : SQLite
 Source Server Version : 3035005 (3.35.5)
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3035005 (3.35.5)
 File Encoding         : 65001

 Date: 11/01/2025 15:13:18
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for Directory
-- ----------------------------
DROP TABLE IF EXISTS "Directory";
CREATE TABLE "Directory"
(
    "directory_id"      integer NOT NULL PRIMARY KEY AUTOINCREMENT,
    "directory_name"    text    NOT NULL,
    "directory_path"    text    NOT NULL,
    "creation_date"     DATETIME,
    "modification_date" DATETIME,
    "last_access_date"  DATETIME,
    "md5_hash"          text,
    "is_encrypted"      BOOLEAN DEFAULT 0,
    "isHide"            BOOLEAN DEFAULT 0,
    "icon_path"         text
);

-- ON DELETE CASCADE表示该键值被删除时，该键值对应的行也会被删除
-- ----------------------------
-- Auto increment value for Directory
-- ----------------------------

PRAGMA foreign_keys = true;
