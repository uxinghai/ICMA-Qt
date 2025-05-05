/**
 * @file EncryptFile.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/4/20
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>

/**
 * @brief 加密文件
 * @param sourceFilePath 源文件（待价密文件）
 * @param destFilePath 目标文件（加密后文件）
 * @param key 密钥
 * @param iv 初始化向量
 * @return true 或 false
 */
inline bool aesEncryptFile(const QString& sourceFilePath, const QString& destFilePath,
                           const QByteArray& key, const QByteArray& iv)
{
  // 打开源文件
  QFile sourceFile(sourceFilePath);
  if (!sourceFile.open(QIODevice::ReadOnly)) {
    qDebug() << "无法打开源文件:" << sourceFile.errorString();
    return false;
  }

  // 打开目标文件
  QFile destFile(destFilePath);
  if (!destFile.open(QIODevice::WriteOnly)) {
    qDebug() << "无法打开目标文件:" << destFile.errorString();
    sourceFile.close();
    return false;
  }

  // 读取源文件数据
  const QByteArray data = sourceFile.readAll();
  sourceFile.close();

  // 初始化OpenSSL
  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  if (!ctx) {
    qDebug() << "无法创建加密上下文";
    return false;
  }

  // 初始化加密操作
  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                              reinterpret_cast<const unsigned char*>(key.constData()),
                              reinterpret_cast<const unsigned char*>(iv.constData()))) {
    qDebug() << "无法初始化加密";
    EVP_CIPHER_CTX_free(ctx);
    return false;
  }

  // 为加密后的数据分配足够的空间
  int outLen1 = 0;
  int outLen2 = 0;
  QByteArray outBuf(data.size() + AES_BLOCK_SIZE, 0); // 额外的块大小用于填充

  // 加密数据
  if (1 != EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(outBuf.data()),
                             &outLen1,
                             reinterpret_cast<const unsigned char*>(data.constData()),
                             data.size())) {
    qDebug() << "加密失败";
    EVP_CIPHER_CTX_free(ctx);
    return false;
  }

  // 最终处理
  if (1 != EVP_EncryptFinal_ex(
    ctx, reinterpret_cast<unsigned char*>(outBuf.data() + outLen1), &outLen2)) {
    qDebug() << "最终加密处理失败";
    EVP_CIPHER_CTX_free(ctx);
    return false;
  }

  // 清理
  EVP_CIPHER_CTX_free(ctx);

  // 写入加密后的数据
  destFile.write(outBuf.left(outLen1 + outLen2));
  destFile.close();

  return true;
}

/**
 * @brief 解密文件
 * @param sourceFilePath
 * @param destFilePath
 * @param key
 * @param iv
 * @return
 */
inline bool aesDecryptFile(const QString& sourceFilePath, const QString& destFilePath,
                           const QByteArray& key, const QByteArray& iv)
{
  // 打开源文件
  QFile sourceFile(sourceFilePath);
  if (!sourceFile.open(QIODevice::ReadOnly)) {
    qDebug() << "无法打开源文件:" << sourceFile.errorString();
    return false;
  }

  // 打开目标文件
  QFile destFile(destFilePath);
  if (!destFile.open(QIODevice::WriteOnly)) {
    qDebug() << "无法打开目标文件:" << destFile.errorString();
    sourceFile.close();
    return false;
  }

  // 读取加密的数据
  const QByteArray encData = sourceFile.readAll();
  sourceFile.close();

  // 初始化OpenSSL
  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  if (!ctx) {
    qDebug() << "无法创建解密上下文";
    return false;
  }

  // 初始化解密操作
  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                              reinterpret_cast<const unsigned char*>(key.constData()),
                              reinterpret_cast<const unsigned char*>(iv.constData()))) {
    qDebug() << "无法初始化解密";
    EVP_CIPHER_CTX_free(ctx);
    return false;
  }

  // 为解密后的数据分配空间
  int outLen1 = 0;
  int outLen2 = 0;
  QByteArray outBuf(encData.size(), 0);

  // 解密数据
  if (1 != EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(outBuf.data()),
                             &outLen1,
                             reinterpret_cast<const unsigned char*>(encData.constData()),
                             encData.size())) {
    qDebug() << "解密失败";
    EVP_CIPHER_CTX_free(ctx);
    return false;
  }

  // 最终处理
  if (1 != EVP_DecryptFinal_ex(
    ctx, reinterpret_cast<unsigned char*>(outBuf.data() + outLen1), &outLen2)) {
    qDebug() << "最终解密处理失败";
    EVP_CIPHER_CTX_free(ctx);
    return false;
  }

  // 清理
  EVP_CIPHER_CTX_free(ctx);

  // 写入解密后的数据
  destFile.write(outBuf.left(outLen1 + outLen2));
  destFile.close();

  return true;
}

/*// 使用示例
void encryptDecryptExample()
{
  // 生成32字节密钥和16字节IV
  QByteArray key = QCryptographicHash::hash("your-password-here",
                                            QCryptographicHash::Sha256);
  QByteArray iv("0123456789012345"); // 16字节的IV

  bool result = aesEncryptFile("input.txt", "encrypted.dat", key, iv);
  if (result) {
    qDebug() << "加密成功!";

    result = aesDecryptFile("encrypted.dat", "decrypted.txt", key, iv);
    if (result) { qDebug() << "解密成功!"; }
  }
}*/
