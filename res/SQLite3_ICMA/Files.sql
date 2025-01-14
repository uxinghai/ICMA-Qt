/*
 Navicat Premium Data Transfer

 Source Server         : ICMA
 Source Server Type    : SQLite
 Source Server Version : 3035005 (3.35.5)
 Source Schema         : main

 Target Server Type    : SQLite
 Target Server Version : 3035005 (3.35.5)
 File Encoding         : 65001

 Date: 11/01/2025 15:14:01
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for Files
-- ----------------------------
DROP TABLE IF EXISTS "Files";
CREATE TABLE "Files"
(
    "file_id"           integer PRIMARY KEY AUTOINCREMENT,
    "file_name"         text NOT NULL, --qtCreator.exe
    "file_path"         text NOT NULL, --C:\Qt
    "file_absFilePath"  text,          --完整路径 C:\Qt\qtCreator.exe
    "directory_id"      integer,
    "file_size"         integer,
    "file_type"         text,
    "creation_date"     DATETIME,
    "modification_date" DATETIME,
    "last_access_date"  DATETIME,
    "md5_hash"          text    DEFAULT '',
    "is_encrypted"      BOOLEAN DEFAULT 0,
    "indexed_status "   BOOLEAN DEFAULT 0,
    "mime_type"         text    DEFAULT '',
    "icon_path"         text,
    UNIQUE ("file_absFilePath" ASC),
    FOREIGN KEY ("directory_id") REFERENCES "Directory" ("directory_id") ON DELETE CASCADE
);

-- ----------------------------
-- Auto increment value for Files
-- ----------------------------

PRAGMA foreign_keys = true;
