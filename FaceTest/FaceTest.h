/**
 * @file FaceTest
 * @brief 人脸信息检测类
 *
 *
 *
 * @author uxinghai
 * @date 2024.10.28
 */

#ifndef IMAGETEST_H
#define IMAGETEST_H

#include <QCamera>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QImageCapture>
#include <QJsonObject>
#include <QMediaCaptureSession>  // 中间件
#include <QNetworkAccessManager> // 中间件
#include <QWidget>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class FaceTest;
}
QT_END_NAMESPACE

class FaceTest : public QWidget {
    Q_OBJECT

public:
    FaceTest(QWidget *parent = nullptr);
    ~FaceTest();

private slots:
    // 相机操作相关槽函数
    void openCamera();
    void on_btnOPCamera_clicked();     // 点击关闭摄像头
    void on_btnCaptureImage_clicked(); // 点击拍照
    void handleImageCaptured(int id, const QImage &image);

    // 网络请求相关槽函数
    void handleTokenResponse(QNetworkReply *reply);
    void handleFaceDetectResponse(QNetworkReply *reply);
    void processFaceDetection(QByteArray postData);

signals:
    // 发送图像处理信号
    void processImage(const QImage &image);

private:
    // 初始化函数
    void initializeCamera();
    void initializeNetworkManagers();
    void initializeConnections();

    // AI Token获取与人脸检测
    void requestAIToken();
    void prepareImageData();
    void updateUIWithFaceInfo(const QJsonObject &faceInfo);

    // 错误处理
    void handleNetworkError(QNetworkReply *reply, const QString &operation);
    void showErrorMessage(const QString &message);

    // UI组件
    Ui::FaceTest *ui;
    std::unique_ptr<QGraphicsScene> scene;

    // 相机组件
    std::unique_ptr<QCamera> camera;
    std::unique_ptr<QMediaCaptureSession> captureSession;
    std::unique_ptr<QImageCapture> imageCapture;
    QGraphicsVideoItem *videoItem;
    QTimer *timer;

    // 网络请求组件
    QNetworkAccessManager *tokenManager{nullptr};      // 用于获取Token
    QNetworkAccessManager *faceDetectManager{nullptr}; // 用于人脸检测
    QString accessToken;                               // 保留token。后续每次调用AIP都需要
    QImage capturedImage;                              // 保留捕获的图像

    // 工作线程
    QThread *workerThread{nullptr};

    // 常量定义
    static const QString API_BASE_URL;
    static const QString API_KEY;
    static const QString SECRET_KEY;

    // 人脸位置
    struct FaceLocation {
        double left, top;     // 左顶点
        double width, height; // 宽高
    };
    // 人脸绘制相关
    void drawFaceRectangle(const FaceLocation &location);
    QGraphicsRectItem *currentFaceRect;
};

#endif // IMAGETEST_H
