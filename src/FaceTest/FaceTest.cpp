#include "FaceTest.h"

#include <QBuffer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QNetworkReply>
#include <QThread>
#include <QTimer>
#include <QUrlQuery>

#include "Worker.h"
#include "ui_FaceTest.h"

// API相关常量定义
const QString FaceTest::API_BASE_URL = "https://aip.baidubce.com";
const QString FaceTest::API_KEY = "AXpJSMWfCfUzd0omZJheU7QZ";
const QString FaceTest::SECRET_KEY = "TidB30gDa9QTdFIVqpjeN8ced15JMdmX";

FaceTest::FaceTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FaceTest)
    , scene(std::make_unique<QGraphicsScene>())
    , camera(std::make_unique<QCamera>())
    , captureSession(std::make_unique<QMediaCaptureSession>())
    , imageCapture(std::make_unique<QImageCapture>()) {
    ui->setupUi(this);

    // 初始化各个组件
    initializeCamera();
    initializeNetworkManagers();
    initializeConnections();

    // 获取AI服务token并启动相机
    requestAIToken();
    openCamera();
}

FaceTest::~FaceTest() {
    // 清理资源
    if (camera) {
        camera->stop();
    }
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
    }
    delete ui;
}

void FaceTest::initializeCamera() {
    // 设置GraphicsView不可见
    ui->graphicsView->setVisible(false);

    // 设置相机和视图组件
    captureSession->setCamera(camera.get());
    captureSession->setImageCapture(imageCapture.get());
    ui->graphicsView->setScene(scene.get());
}

void FaceTest::initializeNetworkManagers() {
    // 初始化网络请求管理器
    tokenManager = new QNetworkAccessManager(this);
    faceDetectManager = new QNetworkAccessManager(this);

    // 检查HTTPS支持
    const auto schemes = tokenManager->supportedSchemes();
    if (!schemes.contains("https", Qt::CaseInsensitive)) {
        showErrorMessage(tr("系统不支持HTTPS请求，无法使用人脸检测服务"));
    }
}

void FaceTest::initializeConnections() {
    // 设置信号槽连接
    connect(tokenManager, &QNetworkAccessManager::finished,
            this, &FaceTest::handleTokenResponse);
    connect(faceDetectManager, &QNetworkAccessManager::finished,
            this, &FaceTest::handleFaceDetectResponse);
    connect(imageCapture.get(), &QImageCapture::imageCaptured,
            this, &FaceTest::handleImageCaptured);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, [this]() {
                imageCapture->capture();
            });
    timer->start(20); // 1秒钟50张图像
}

void FaceTest::openCamera() {
    // 创建并配置视频输出项
    videoItem = new QGraphicsVideoItem;
    scene->addItem(videoItem);

    // // 设置视图缩放和翻转
    // ui->graphicsView->fitInView(videoItem, Qt::KeepAspectRatio);
    // ui->graphicsView->scale(1.65, 2.95);

    // // 水平翻转图像
    // QTransform transform;
    // transform.scale(-1, 1);
    // videoItem->setTransform(transform);

    // 启动相机
    captureSession->setVideoOutput(videoItem);
    camera->start();
}

void FaceTest::on_btnOPCamera_clicked() {
    if (ui->btnCaptureImage->isEnabled()) {
        camera->stop();
        ui->btnOPCamera->setText(tr("打开摄像头"));
        ui->btnCaptureImage->setEnabled(false);
    } else {
        camera->start();
        ui->btnOPCamera->setText(tr("关闭摄像头"));
        ui->btnCaptureImage->setEnabled(true);
    }
}

void FaceTest::on_btnCaptureImage_clicked() {
    // 开始拍照并显示进度条
    // imageCapture->capture();
    prepareImageData();
    ui->progressBar->setRange(0, 0);
    ui->btnCaptureImage->setEnabled(false);
}

void FaceTest::handleImageCaptured(int id, const QImage &image) {
    Q_UNUSED(id);
    // 更新捕获到的图像
    capturedImage = image;
    QPixmap tmp = QPixmap::fromImage(image);
    // // 水平翻转图像
    // QTransform transform;
    // transform.scale(-1, 1);
    // tmp = tmp.transformed(transform);  // 将变换后的图像重新赋值给 tmp
    ui->lbDisplay->setPixmap(tmp); // 显示翻转后的图像
}

void FaceTest::requestAIToken() {
    // 构建token请求URL
    QUrl url(API_BASE_URL + "/oauth/2.0/token");
    QUrlQuery query;
    query.addQueryItem("grant_type", "client_credentials");
    query.addQueryItem("client_id", API_KEY);
    query.addQueryItem("client_secret", SECRET_KEY);
    url.setQuery(query);

    // 发送请求
    tokenManager->get(QNetworkRequest(url));
}

void FaceTest::handleTokenResponse(QNetworkReply *reply) {
    // 处理token响应
    if (reply->error() != QNetworkReply::NoError) {
        handleNetworkError(reply, tr("获取Token失败"));
        return;
    }

    // 解析响应数据
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (doc.isObject()) {
        // 保留token
        accessToken = doc.object()["access_token"].toString();
    }

    reply->deleteLater();
}

void FaceTest::prepareImageData() {
    // 在工作线程中处理图像数据
    workerThread = new QThread;
    auto *worker = new Worker;
    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &FaceTest::processImage, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &FaceTest::processFaceDetection);

    workerThread->start();
    emit processImage(capturedImage);
}

void FaceTest::processFaceDetection(QByteArray postData) {
    // 停止工作线程
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
    }

    // 构建人脸检测请求
    QUrl url(API_BASE_URL + "/rest/2.0/face/v3/detect");
    QUrlQuery query;
    query.addQueryItem("access_token", accessToken);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送请求
    faceDetectManager->post(request, postData);
}

void FaceTest::handleFaceDetectResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        handleNetworkError(reply, tr("人脸检测失败"));
        return;
    }

    // 解析响应数据
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (doc.isObject()) {
        QJsonObject obj = doc.object();

        // 检查是否存在错误
        if (obj["error_code"].toInt() != 0) {
            showErrorMessage(tr("请不要遮挡面部，请再试一次"));
            ui->progressBar->setRange(0, 1);
            ui->progressBar->setValue(0);
        } else {
            // 更新UI显示结果
            QJsonArray faceList = obj["result"].toObject()["face_list"].toArray();
            if (!faceList.isEmpty()) {
                QJsonObject faceInfo = faceList[0].toObject();
                updateUIWithFaceInfo(faceInfo);

                // 提取人脸位置信息并绘制
                FaceLocation location;
                location.left = faceInfo["location"].toObject()["left"].toDouble();
                location.top = faceInfo["location"].toObject()["top"].toDouble();
                location.width = faceInfo["location"].toObject()["width"].toDouble();
                location.height = faceInfo["location"].toObject()["height"].toDouble();

                drawFaceRectangle(location);
            }
        }
    }

    ui->btnCaptureImage->setEnabled(true);
    reply->deleteLater();
}

void FaceTest::updateUIWithFaceInfo(const QJsonObject &faceInfo) {
    // 脸型映射
    static const QMap<QString, QString> faceShapeMap = {
        {"square", "正方形"},
        {"triangle", "三角形"},
        {"oval", "椭圆"},
        {"heart", "心形"},
        {"round", "圆形"}};

    // 情绪映射
    static const QMap<QString, QString> emotionMap = {
        {"angry", "愤怒"},
        {"disgust", "厌恶"},
        {"fear", "恐惧"},
        {"happy", "高兴"},
        {"sad", "伤心"},
        {"surprise", "惊讶"},
        {"neutral", "无表情"},
        {"pouty", "撅嘴"},
        {"grimace", "鬼脸"}};

    // 获取各项属性
    QString faceShape = faceShapeMap.value(
        faceInfo["face_shape"].toObject()["type"].toString());
    QString gender = faceInfo["gender"].toObject()["type"].toString() == "female"
                         ? "小姐姐"
                         : "小哥哥";
    QString emotion = emotionMap.value(
        faceInfo["emotion"].toObject()["type"].toString());

    // 更新UI显示
    ui->gender->setText(tr("性别：%1").arg(gender));
    ui->age->setText(tr("年龄：%1").arg(faceInfo["age"].toInt()));
    ui->face_shape->setText(tr("脸型：%1").arg(faceShape));
    ui->emotion->setText(tr("情绪：%1").arg(emotion));
    ui->beauty->setText(tr("颜值：%1").arg(faceInfo["beauty"].toDouble()));

    // 更新进度条
    ui->progressBar->setRange(0, 1);
    ui->progressBar->setValue(1);
}

void FaceTest::handleNetworkError(QNetworkReply *reply, const QString &operation) {
    showErrorMessage(tr("%1: %2").arg(operation, reply->errorString()));
    reply->deleteLater();
}

void FaceTest::showErrorMessage(const QString &message) {
    QMessageBox::warning(this, tr("错误"), message);
}

void FaceTest::drawFaceRectangle(const FaceLocation &location) {
    // 创建新的矩形项
    QPen pen(Qt::red); // 使用红色边框
    pen.setWidth(2);   // 设置边框宽度

    currentFaceRect = scene->addRect(QRect(location.left, location.top, location.width, location.height), pen);

    // 设置矩形的变换（水平翻转，与相机图像保持一致）
    QTransform transform;
    transform.scale(-1, 1); // 水平翻转
    currentFaceRect->setTransform(transform);
}
