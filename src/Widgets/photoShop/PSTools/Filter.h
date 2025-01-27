/**
 * @file Filter.h
 *
 * @Breife 特效滤镜算法模块
 *
 * @version 1.0
 * @date 2025/1/26
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

namespace DoFilter
{
  // mat 是 RGB 格式
  inline cv::Mat filter(const cv::Mat& mat, const int row)
  {
    cv::Mat resMat = cv::Mat::zeros(mat.rows, mat.cols, CV_8UC3);
    switch (row) {
    case 0: ///< 大师黑白
      cvtColor(mat, resMat, cv::COLOR_RGB2GRAY);
      cvtColor(resMat, resMat, cv::COLOR_GRAY2RGB);
      break;
    case 1: ///< 粉笔画
      cvtColor(mat, resMat, cv::COLOR_RGB2GRAY);
      GaussianBlur(resMat, resMat, cv::Size(3, 3), 0);
      adaptiveThreshold(resMat, resMat, 255,
                        cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11,
                        2);
      cvtColor(resMat, resMat, cv::COLOR_GRAY2RGB);
      break;
    case 2: ///< 浮雕滤镜
      {
        cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
          -1, -1, 0,
          -1, 0, 1,
          0, 1, 1);
        filter2D(mat, resMat, mat.depth(), kernel);
        resMat += cv::Scalar(128, 128, 128); // 调整亮度
      }
      break;
    case 3: ///< 复古胶片
      {
        const cv::Mat sepiaKernel = (cv::Mat_<float>(3, 3) <<
          0.393, 0.769, 0.189,
          0.349, 0.686, 0.168,
          0.272, 0.534, 0.131);
        mat.convertTo(resMat, CV_32F);
        transform(resMat, resMat, sepiaKernel);
        resMat.convertTo(resMat, CV_8U);
      }
      break;
    case 4: ///< 铅笔素描
      {
        cv::Mat grayMat, edges, inv;
        cvtColor(mat, grayMat, cv::COLOR_RGB2GRAY);
        GaussianBlur(grayMat, grayMat, cv::Size(3, 3), 0);
        Laplacian(grayMat, edges, CV_8U, 3);
        threshold(edges, edges, 80, 255, cv::THRESH_BINARY_INV);
        cvtColor(edges, resMat, cv::COLOR_GRAY2RGB);
      }
      break;
    case 5: ///< 彩色铅笔画
      {
        cv::Mat grayMat, edges;
        cvtColor(mat, grayMat, cv::COLOR_RGB2GRAY);
        GaussianBlur(grayMat, grayMat, cv::Size(3, 3), 0);
        Laplacian(grayMat, edges, CV_8U, 3);
        threshold(edges, edges, 80, 255, cv::THRESH_BINARY_INV);

        // 确保edges和mat类型一致
        edges.convertTo(edges, mat.type());

        // 创建遮罩
        cv::Mat mask;
        edges.convertTo(mask, CV_32F, 1.0 / 255);

        // 转换mat为浮点类型
        cv::Mat floatMat;
        mat.convertTo(floatMat, CV_32F, 1.0 / 255);

        // 逐像素处理
        for (int i = 0; i < mat.rows; ++i) {
          for (int j = 0; j < mat.cols; ++j) {
            auto& pixel = floatMat.at<cv::Vec3f>(i, j);
            float maskVal = mask.at<float>(i, j);
            pixel *= maskVal;
          }
        }

        // 转换回8位图像
        floatMat.convertTo(resMat, CV_8U, 255);
      }
      break;
    case 6: ///< 卡通动漫
      {
        cv::Mat grayMat, edges;
        cvtColor(mat, grayMat, cv::COLOR_RGB2GRAY);
        medianBlur(mat, resMat, 7);
        Laplacian(grayMat, edges, CV_8U, 3);
        threshold(edges, edges, 80, 255, cv::THRESH_BINARY_INV);

        // 合并边缘和简化颜色的图像
        for (int i = 0; i < mat.rows; ++i) {
          for (int j = 0; j < mat.cols; ++j) {
            if (edges.at<uchar>(i, j) == 255) {
              resMat.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
            }
          }
        }
      }
      break;
    default: resMat = mat; // 默认返回原图
      break;
    }

    return resMat;
  }

  inline cv::Mat filter2(const cv::Mat& mat, const int row)
  {
    cv::Mat resMat = mat.clone();
    switch (row) {
    case 0: ///< 哥特油画
      {
        cv::Mat quantized;
        resMat.convertTo(quantized, CV_8U, 1, -128);
        quantized = quantized / 64 * 64 + 32;
        quantized.convertTo(resMat, CV_8UC3);
      }
      break;
    case 1: ///< 薰衣草油画
      {
        cv::Mat lavender;
        cvtColor(mat, lavender, cv::COLOR_BGR2HSV);
        std::vector<cv::Mat> channels;
        split(lavender, channels);
        channels[0] = channels[0] * 1.2; // 增加色调饱和度
        channels[1] = channels[1] * 1.3;
        merge(channels, lavender);
        cvtColor(lavender, resMat, cv::COLOR_HSV2BGR);
      }
      break;
    case 2: ///< 奇异油画
      {
        cv::Mat distorted = mat.clone();

        // 创建变形映射
        cv::Mat mapX(mat.size(), CV_32F);
        cv::Mat mapY(mat.size(), CV_32F);

        for (int y = 0; y < mat.rows; y++) {
          for (int x = 0; x < mat.cols; x++) {
            // 添加正弦波形变换
            mapX.at<float>(y, x) = x + 10 * sin(y / 30.0);
            mapY.at<float>(y, x) = y + 10 * cos(x / 30.0);
          }
        }

        // 重映射
        remap(mat, distorted, mapX, mapY, cv::INTER_LINEAR,
              cv::BORDER_REFLECT);

        // 添加色彩噪声
        cv::Mat noise(mat.size(), CV_8UC3);
        randn(noise, cv::Scalar(0, 0, 0), cv::Scalar(20, 20, 20));
        addWeighted(distorted, 0.9, noise, 0.1, 0, resMat);
      }
      break;
    case 3: ///< 神奈川冲浪里油画
      {
        cv::Mat waves;
        mat.copyTo(waves);

        // 波浪形变换
        for (int y = 0; y < waves.rows; y++) {
          for (int x = 0; x < waves.cols; x++) {
            if (int offset = static_cast<int>(10 * sin(x / 50.0));
              y + offset >= 0 && y + offset < waves.rows) {
              waves.at<cv::Vec3b>(y, x) = mat.at<cv::Vec3b>(y + offset, x);
            }
          }
        }

        resMat = waves;
      }
      break;
    case 4: ///< 呐喊油画
      {
        cv::Mat scream;
        cvtColor(mat, scream, cv::COLOR_BGR2GRAY);
        equalizeHist(scream, scream);

        // 强调边缘
        cv::Mat edges;
        Canny(scream, edges, 100, 200);

        // 混合原图和边缘
        cvtColor(scream, scream, cv::COLOR_GRAY2BGR);
        for (int y = 0; y < mat.rows; y++) {
          for (int x = 0; x < mat.cols; x++) {
            if (edges.at<uchar>(y, x) > 0) {
              scream.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
            }
          }
        }

        resMat = scream;
      }
      break;
    case 5: ///< 彩色糖块油画
      {
        cv::Mat candy;
        mat.copyTo(candy);

        // 色彩量化
        for (int y = 0; y < candy.rows; y++) {
          for (int x = 0; x < candy.cols; x++) {
            auto& pixel = candy.at<cv::Vec3b>(y, x);
            pixel[0] = pixel[0] / 64 * 64 + 32;
            pixel[1] = pixel[1] / 64 * 64 + 32;
            pixel[2] = pixel[2] / 64 * 64 + 32;
          }
        }

        resMat = candy;
      }
      break;
    default: break;
    }
    return resMat;
  }
}
