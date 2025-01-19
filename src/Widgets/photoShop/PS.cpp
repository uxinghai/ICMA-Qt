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
#include "Crop.h"
#include "faceTest/FaceTest.h"

PS::PS()
  : ui(new Ui::PS),
    scene(new QGraphicsScene(this))
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

  connect(ui->cropList, &QListWidget::currentRowChanged,
          [this](const int currentRow) {
            showImgToUi(Crop::cropPixmapBy(historyPixmap.top(), currentRow));
          });

  connect(ui->btnUndo, &QToolButton::clicked, this, &PS::doUndo);

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
  if (pixFilePath.isEmpty()) { return; }

  // 成功打开图片
  srcPixmap = QPixmap::fromImage(QImage(pixFilePath));
  showImgToUi(srcPixmap);
  // 更新界面状态
  ui->toolBox->setEnabled(true);
  setEnableButton(true);
  historyPixmap.pushBack(srcPixmap);
}

void PS::showImgToUi(const QPixmap& showPixmap)
{
  if (showPixmap.isNull()) { return; }

  // 先清理场景
  scene->clear();

  // 创建并添加新的图片项
  auto* pixmapItem = new QGraphicsPixmapItem(showPixmap);
  scene->addItem(pixmapItem);

  // 设置场景范围为图片大小!!
  scene->setSceneRect(showPixmap.rect());

  // 居中显示
  ui->GraphicsView->setSceneRect(scene->sceneRect());
  ui->GraphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

  // 确保内容完全可见
  ui->GraphicsView->ensureVisible(scene->sceneRect(), 0, 0);

  showImgSize(showPixmap);
}

void PS::doUndo()
{
  QPixmap showPixmap;
  // 撤回对于 tempStk是显示上一个
  if (tempStk.size() > 1) {
    tempStk.pop();
    showPixmap = tempStk.top();
  }
  else {
    showPixmap = historyPixmap.top();
    if (historyPixmap.size() > 1) { historyPixmap.pop(); }
    tempStk.clear(); ///< 注意清空
  }
  showImgToUi(showPixmap);
}

void PS::setEnableButton(const bool enable) const
{
  ui->btnReset->setEnabled(enable);
  ui->btnUndo->setEnabled(enable);
  ui->btnComparison->setEnabled(enable);
  ui->btnSaveAs->setEnabled(enable);
  ui->btnDireSave->setEnabled(enable);
}

void PS::showImgSize(const QPixmap& showPixmap) const
{
  if (!showPixmap.isNull()) {
    const QString height = QString::number(showPixmap.height());
    const QString width = QString::number(showPixmap.width());
    ui->leSizeH->setText(height);
    ui->leSizeH2->setText(height);
    ui->leSizeW->setText(width);
    ui->leSizeW2->setText(width);
  }
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
    showImgToUi(QPixmap::fromImage(QImage(localFile)));
  }
  QWidget::dropEvent(event);
}

PS::~PS() { delete ui; }
