#include "PS.h"

#include <QThreadPool>

#include  "../../../UI/ui_FaceTest.h"
#include  "../../../UI/ui_PS.h"
#include "../../Controls/Network/GetBaiduToken.h"
#include "../../Manager/Config/iniManager.h"
#include "faceTest/FaceTest.h"

PS::PS() : ui(new Ui::PS)
{
  ui->setupUi(this);

  // 后台获取 Token
  getBaiduAIToken();

  setupConnections();
}

void PS::setupConnections()
{
  // 人脸检测
  connect(ui->FaceTestToolBtn, &QToolButton::clicked, [this] {
    const auto faceTestWidget = new FaceTest();
    faceTestWidget->setAttribute(Qt::WA_DeleteOnClose);
    faceTestWidget->show();
  });
}

void PS::getBaiduAIToken()
{
  const auto settings = iniManager::getIniSetting();

  if (const auto lastDate = settings.value("BaiduAI/LastGetTokenTime").toDate();
    !lastDate.isValid() || lastDate.addDays(30) < QDate::currentDate()) {
    qDebug() << "request token";
    // 不能使用智能指针，因为析构时线程的工作可能还没完成！
    // 线程的对象析构最好用信号槽
    const auto getBaiduTokenWorker = new GetBaiduToken();
    connect(getBaiduTokenWorker, &GetBaiduToken::baiduTokenReady,
            this, &PS::doGetTokenReady);
    connect(getBaiduTokenWorker, &GetBaiduToken::finished,
            getBaiduTokenWorker, &QObject::deleteLater); ///< 完成释放内存
    getBaiduTokenWorker->start();
  }
  else {
    // 构建人脸检测时用到的 url
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("access_token",
                          settings.value("BaiduAI/TOKEN").toString());
    requestFaceDetectUrl.setQuery(urlQuery);
  }
}

void PS::doGetTokenReady(const QString& token)
{
  auto settings = iniManager::getIniSetting();
  settings.setValue("BaiduAI/TOKEN", token);
  settings.setValue("BaiduAI/LastGetTokenTime", QDate::currentDate());
  qDebug() << "get token" << token;

  // 构建人脸检测时用到的 url
  QUrlQuery urlQuery;
  urlQuery.addQueryItem("access_token",
                        settings.value("BaiduAI/TOKEN").toString());
  requestFaceDetectUrl.setQuery(urlQuery);
}

PS::~PS() { delete ui; }
