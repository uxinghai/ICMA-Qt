/**
 * @file ShareSrc.h
 *
 * @Breife PS模块共享资源
 *
 * @version 1.0
 * @date 2025/1/17
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QImage>
#include <QMap>
#include <QString>
#include <QUrl>

struct FaceLocation {
  double left;
  double top;
  int width;
  int height;
  int rotation;
  FaceLocation() = default;

  FaceLocation(const double left, const double top, const int width,
               const int height, const int rotation = 0)
    : left(left), top(top), width(width), height(height), rotation(rotation) {}
};

struct FaceInfo {
  QString faceGender;          ///< 性别
  int faceAge{};               ///< 年龄
  QString faceShape;           ////< 脸型
  QString faceEmotion;         ///< 情绪
  QString expression;          ////< 笑容
  QString faceType;            ///< type: happy sad
  double faceBeauty{};         ///< 佩戴美丽值
  QString faceGlass;           ///< 佩戴眼镜
  QString faceMask;            ///< 佩戴口罩
  FaceLocation faceLocation{}; ///< 面部在位置
};

// 眼镜映射
const QMap<QString, QString> glassMap = {
  {"none", "未佩戴眼镜"},
  {"sun", "墨镜"},
  {"common", "普通眼镜"},
};

// 笑容映射
const QMap<QString, QString> expressionMap = {
  {"none", "自然"},
  {"smile", "微笑"},
  {"laugh", "大笑"}
};

// 脸型映射
const QMap<QString, QString> faceShapeMap = {
  {"square", "正方形"},
  {"triangle", "三角形"},
  {"oval", "椭圆"},
  {"heart", "心形"},
  {"round", "圆形"}
};

// 情绪映射
const QMap<QString, QString> emotionMap = {
  {"angry", "愤怒"},
  {"disgust", "厌恶"},
  {"fear", "恐惧"},
  {"happy", "高兴"},
  {"sad", "伤心"},
  {"surprise", "惊讶"},
  {"neutral", "自然"},
  {"pouty", "撅嘴"},
  {"grimace", "鬼脸"}
};

// 共享给 threadImageToBase64 线程
inline QImage captureImgCopy; ///< 捕获图像的拷贝

// 共享给 AIDoFaceDetect 线程
inline QString imgBase64Copy; ///< base64编码的拷贝
inline FaceInfo faceInfo;     ///< 共享人脸信息的结构

// URL
// 人脸请求
inline QUrl requestFaceDetectUrl{
  "https://aip.baidubce.com/rest/2.0/face/v3/detect"
};

// 获取token
inline QString getTokenUrl = "https://aip.baidubce.com/oauth/2.0/token";
