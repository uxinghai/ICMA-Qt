/**
 * @file Adjust.h
 *
 * @Breife PS中调整模块 亮度、对比度、饱和度、反相
 *
 * @version 1.0
 * @date 2025/1/23
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

namespace Adjust
{
  /**
 * @brief 调整图像
 * @param mat 待修改图像（MatRGB格式）
 * @param bright 亮度
 * @param contrast 对比度
 * @param saturation 饱和度
 * @param reverse  反相 0%-100%
 */
  inline cv::Mat adjustMat(const cv::Mat& mat, const double bright,
                           const double contrast, const double saturation,
                           const double reverse)
  {
    // 确保输入图像为RGB格式
    if (mat.empty() || mat.channels() != 3)
      return mat.clone();

    cv::Mat resMat;

    // 亮度和对比度调整
    mat.convertTo(resMat, CV_8UC3, contrast, bright);

    // 饱和度调整
    cv::Mat hsv;
    cvtColor(resMat, hsv, cv::COLOR_RGB2HSV);
    std::vector<cv::Mat> hsv_planes;
    split(hsv, hsv_planes);

    // 调整饱和度，确保值在范围内
    hsv_planes[1] = hsv_planes[1] * saturation;
    threshold(hsv_planes[1], hsv_planes[1], 255, 255, cv::THRESH_TRUNC);

    merge(hsv_planes, hsv);
    cvtColor(hsv, resMat, cv::COLOR_HSV2RGB);

    // 反相处理，基于百分比
    if (reverse > 0) {
      cv::Mat inv;
      bitwise_not(resMat, inv);
      addWeighted(resMat, 1.0 - reverse / 100.0,
                  inv, reverse / 100.0, 0, resMat);
    }

    return resMat;
  }
}
