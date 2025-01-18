#include "PS.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMimeData>
#include <QThreadPool>

#include  "../../../UI/ui_FaceTest.h"
#include  "../../../UI/ui_PS.h"
#include "../../Manager/Config/iniManager.h"
#include "../../Network/GetBaiduToken.h"
#include "../../Utils/Tools/LoadingGif.h"
#include "../../Utils/Tools/MovableFramelessWindow.h"
#include "faceTest/FaceTest.h"

PS::PS()
  : ui(new Ui::PS),
    scene(new QGraphicsScene(this)),
    mySceneItem(new QGraphicsPixmapItem())

{
  ui->setupUi(this);

  init();
  getBaiduAIToken(); ///< 后台获取 Token
  setupConnections();
}

void PS::init()
{
  ui->GraphicsView->setScene(scene);

  auto font = this->font();
  font.setPointSize(14);
  scene->addSimpleText(tr("拖入图片到此窗口或点击打开图片"), font);
}

void PS::setupConnections()
{
  connect(ui->btnOpenImg, &QToolButton::clicked,
          this, &PS::doOpenImg);

  // 人脸检测
  connect(ui->FaceTestToolBtn, &QToolButton::clicked, [this] {
    const auto faceTestWidget = new FaceTest();
    faceTestWidget->setAttribute(Qt::WA_DeleteOnClose);
    faceTestWidget->show();
  });
}

void PS::doOpenImg()
{
  QString filter = tr("图片文件(");
  for (const auto& suffix : suffixList) { filter += "*." + suffix + " "; }
  filter += ")";
  const QString pixFilePath = QFileDialog::getOpenFileName(this, tr("打开图片"),
    "../", filter);

  showImgToUi(pixFilePath);
}

void PS::showImgToUi(const QString& imgPath)
{
  if (const auto img = QImage(imgPath);
    !img.isNull()) {
    mySceneItem->setPixmap(QPixmap::fromImage(img));
    scene->clear();
    scene->addItem(mySceneItem);

    setEnableButton(true);
  }
}

void PS::setEnableButton(const bool enable) const
{
  ui->btnReset->setEnabled(enable);
  ui->btnUndo->setEnabled(enable);
  ui->btnComparison->setEnabled(enable);
  ui->btnSaveAs->setEnabled(enable);
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

void PS::dragEnterEvent(QDragEnterEvent* event)
{
  ///< 拖入事件
  if (const auto mimeDate = event->mimeData();
    mimeDate->hasUrls()) {
    const QString localFile = mimeDate->urls().first().toLocalFile();
    if (const QFileInfo info(localFile);
      suffixList.contains(info.suffix().toUpper())) {
      event->acceptProposedAction();
      return;
    }
  }
  QWidget::dragEnterEvent(event);
}

void PS::dropEvent(QDropEvent* event)
{
  if (!event) { return; }

  if (const auto* mimeData = event->mimeData();
    mimeData->hasUrls()) {
    const QString localFile = mimeData->urls().first().toLocalFile();
    showImgToUi(localFile);
  }
  QWidget::dropEvent(event);
}
