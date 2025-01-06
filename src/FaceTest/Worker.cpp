#include "Worker.h"

#include <QBuffer>
#include <QJsonDocument>
#include <QJsonObject>

Worker::Worker(QObject *parent)
    : QObject{parent} {
    // setAutoDelete(true);
}

void Worker::doWork(const QImage &image) {
    // 图像转成base64编码 这个比较耗时
    QByteArray array;
    QBuffer buffer(&array);     // 需要Qbuffer把QbyteArray作为IO对象
    image.save(&buffer, "png"); // 以png存入array

    QString base64str = static_cast<QString>(array.toBase64(QByteArray::Base64Encoding));
    if (base64str.isEmpty())
        return;

    // 拼接json，请求体body参数设置
    QJsonObject postJson;

    postJson.insert("image", base64str);
    postJson.insert("image_type", "BASE64");
    postJson.insert("face_field",
                    "age,expression,face_shape,gender,"
                    "glasses,emotion,face_type,mask,beauty");
    QJsonDocument doc(postJson);
    QByteArray postData = doc.toJson(QJsonDocument::Compact);

    emit resultReady(postData);
}
