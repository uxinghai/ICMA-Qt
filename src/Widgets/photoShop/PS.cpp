#include "PS.h"

#include <QThreadPool>

#include  "../../../UI/ui_FaceTest.h"
#include  "../../../UI/ui_PS.h"
#include "../../Manager/Config/iniManager.h"
#include "../../Utils/threadWorkers/GetBaiduTokenWorker.h"
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
    !lastDate.isValid() || lastDate.addDays(30) > QDate::currentDate()) {
    qDebug() << "request token";
    getBaiduTokenWorker = new GetBaiduTokenWorker(this);
    connect(getBaiduTokenWorker, &GetBaiduTokenWorker::baiduTokenReady,
            this, &PS::doGetTokenReady);
    connect(getBaiduTokenWorker, &GetBaiduTokenWorker::finished,
            getBaiduTokenWorker, &QObject::deleteLater);
    getBaiduTokenWorker->start();
  }
}

void PS::doGetTokenReady(const QString& token)
{
  auto settings = iniManager::getIniSetting();
  Token = token;
  qDebug() << "get token" << token;
  settings.setValue("BaiduAI/BaiduToken", Token);
  settings.setValue("BaiduAI/LastGetTokenTime", QDate::currentDate());
}

PS::~PS() { delete ui; }
