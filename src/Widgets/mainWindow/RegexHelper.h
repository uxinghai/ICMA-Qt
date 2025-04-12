/**
 * @file RegexHelper.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/4/4
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once
#include <QHash>

// 数字代表 ComboBox 的索引
namespace RegexHelper
{
  // 全用大写，用户搜索时转为大写后匹配
  inline const QHash<QString, quint8> keywordCategory{
    // **图片类别**
    {"图片：", 6}, {"图片:", 6}, {"IMAGE:", 6},
    {"JPG:", 6}, {"JPEG:", 6}, {"PNG:", 6},
    {"GIF:", 6}, {"BMP:", 6}, {"SVG:", 6},
    {"WEBP:", 6}, {"TIFF:", 6},

    // **音频类别**
    {"音乐：", 1}, {"音乐:", 1},
    {"MP3:", 1}, {"WAV:", 1}, {"FLAC:", 1},
    {"AAC:", 1}, {"OGG:", 1}, {"M4A:", 1},
    {"WMA:", 1}, {"AMR:", 1},

    // **视频类别**
    {"视频：", 7}, {"视频:", 7},
    {"MP4:", 7}, {"AVI:", 7}, {"MKV:", 7},
    {"MOV:", 7}, {"WMV:", 7}, {"FLV:", 7},
    {"MPEG:", 7}, {"MPG:", 7}, {"WEBM:", 7},

    // **文档类别**
    {"文档：", 3}, {"文档:", 3},
    {"DOC:", 3}, {"DOCX:", 3}, {"PDF:", 3},
    {"TXT:", 3}, {"PPT:", 3}, {"PPTX:", 3},
    {"XLS:", 3}, {"XLSX:", 3}, {"CSV:", 3},
    {"EXCEL:", 3}, {"WORD:", 3}, {"SLIDES:", 3},

    // **压缩文件**
    {"ZIP:", 2}, {"RAR:", 2},
    {"7Z:", 2}, {"TAR:", 2},
    {"GZ:", 2}, {"ISO:", 2},

    // **可执行文件**
    {"EXE:", 4}, {"APP:", 4},
    {"BAT:", 4}, {"CMD:", 4},
    {"SH:", 4}, {"RUN:", 4},

    // **文件夹**
    {"FOLDER:", 5}, {"目录:", 5}, {"文件夹:", 5}
  };

  inline const QMap<quint8, QString> filterTypeMap = {
    {1, "'mp3', 'wav', 'flac', 'aac', 'ogg'"},                        // 音频
    {2, "'zip', 'rar', '7z', 'tar', 'gz'"},                           // 压缩文件
    {3, "'pdf', 'doc', 'docx', 'xls', 'xlsx', 'ppt', 'pptx', 'txt'"}, // 文档
    {4, "'exe', 'dll', 'bin', 'sh'"},                                 // 可执行文件
    {5, "'folder'"},                                                  // 文件夹
    {6, "'jpg', 'jpeg', 'png', 'gif', 'bmp', 'svg'"},                 // 图片
    {7, "'mp4', 'avi', 'mkv', 'mov', 'flv'"}                          // 视频
  };
};
