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
    "directory_id"          integer NOT NULL PRIMARY KEY AUTOINCREMENT,
    "directory_name"        text    NOT NULL, --Qt
    "directory_path"        text    NOT NULL, --C:\
    "directory_absFilePath" text,             --完整路径 C:\Qt
    "parent_directory_id"   integer,
    "creation_date"         DATETIME,
    "modification_date"     DATETIME,
    "last_access_date"      DATETIME,
    "md5_hash"              text    DEFAULT '',
    "is_encrypted"          BOOLEAN DEFAULT 0,
    "isHide"                BOOLEAN DEFAULT 0,
    "icon_path"             text,
    UNIQUE ("directory_absFilePath" ASC)
);

-- ----------------------------
-- Auto increment value for Directory
-- ----------------------------

PRAGMA foreign_keys = true;
