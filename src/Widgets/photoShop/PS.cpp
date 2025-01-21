#include "PS.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QMimeData>
#include <QStandardPaths>
#include <QThreadPool>

#include  "../../../UI/ui_FaceTest.h"
#include  "../../../UI/ui_PS.h"
#include "../../Manager/Config/iniManager.h"
#include "../../Network/GetBaiduToken.h"
#include "../../Utils/Tools/LoadingGif.h"
#include "../../Utils/Tools/MovableFramelessWindow.h"
#include "../../Utils/Tools/MyInformationBox.h"
#include "Crop.h"
#include "faceTest/FaceTest.h"
#include "Resize.h"

PS::PS(QWidget* parent) : QWidget(parent), ui(new Ui::PS),
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
  // 基础操作
  connect(ui->btnOpenImg, &QToolButton::clicked, this, &PS::doImageOpen);
  connect(ui->btnUndo, &QToolButton::clicked, this, &PS::doUndo);
  connect(ui->btnReset, &QToolButton::clicked,
          [this] { showImgToUi(srcPixmap); });

  // 图像对比
  connect(ui->btnComparison, &QToolButton::pressed,
          [this] {
            ui->btnComparison->setIcon(QIcon(":/ps/res/ps/OpenEye.png"));
            showImgToUi(srcPixmap);
          });
  connect(ui->btnComparison, &QToolButton::released,
          [this] {
            ui->btnComparison->setIcon(QIcon(":/ps/res/ps/CloseEye.png"));
            showImgToUi(historyPixmap.top());
          });

  // 保存操作
  connect(ui->btnDireSave, &QToolButton::clicked,
          [this] { doImageSave(false); });
  connect(ui->btnSaveAs, &QToolButton::clicked,
          [this] { doImageSave(true); });

  // 图像处理
  connect(ui->toolBox, &QToolBox::currentChanged, this, &PS::doToolBoxChanged);
  connect(ui->cropList, &QListWidget::currentRowChanged, this,
          &PS::doCropChange);
  connect(ui->sizeList, &QListWidget::currentRowChanged, this,
          &PS::doResizeChange);

  // 尺寸输入
  connect(ui->leSizeW, &QLineEdit::textEdited, this, &PS::doSizeChange);
  connect(ui->leSizeH, &QLineEdit::textEdited, this, &PS::doSizeChange);

  // 人脸检测
  connect(ui->FaceTestToolBtn, &QToolButton::clicked, this,
          &PS::doShowFaceTest);
}

void PS::doImageOpen()
{
  QString filter = tr("图片文件(");
  for (const auto& suffix : suffixList) { filter += "*." + suffix + " "; }
  filter += ")";
  pixFilePath = QFileDialog::getOpenFileName(this, tr("打开图片"),
                                             "../", filter);
  if (pixFilePath.isEmpty()) { return; }

  // 成功打开图片
  srcPixmap = QPixmap::fromImage(QImage(pixFilePath));
  showImgToUi(srcPixmap);
  pushToHistory(srcPixmap);
  updateUIState(true);
  ui->toolBox->setEnabled(true);
}

void PS::showImgToUi(const QPixmap& pixmap) const
{
  if (pixmap.isNull()) { return; }

  /// 亮度跨度明显才保存
  // 先清理场景
  scene->clear();

  // 创建并添加新的图片项
  auto* pixmapItem = new QGraphicsPixmapItem(pixmap);
  scene->addItem(pixmapItem);

  // 设置场景范围为图片大小!!
  scene->setSceneRect(pixmap.rect());

  // 居中显示 确保内容完全可见
  ui->GraphicsView->setSceneRect(scene->sceneRect());
  ui->GraphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
  ui->GraphicsView->ensureVisible(scene->sceneRect(), 0, 0);

  showImgSize(pixmap);
}

void PS::doUndo() const
{
  if (historyPixmap.size() > 2) {
    historyPixmap.pop();
    showImgToUi(historyPixmap.top());
  }
  else { ui->btnReset->click(); }
}

void PS::doSizeChange() const
{
  ui->sizeList->setCurrentRow(0);
  const auto pixmap = Resize::resizePixmapBy(
    shouldBeProcessed,
    0,
    ui->lockedWHRatio->isChecked(),
    ui->leSizeW->text().toInt(),
    ui->leSizeH->text().toInt()
  );
  showImgToUi(pixmap);
  showImgSize(pixmap);
}

void PS::doShowFaceTest()
{
  const auto faceTestWidget = new FaceTest();
  faceTestWidget->setAttribute(Qt::WA_DeleteOnClose);
  faceTestWidget->show();
}

void PS::doImageSave(const bool isSaveAs)
{
  if (!isSaveAs) {
    if (QMessageBox::information(this, tr("询问"), tr("是否要替换文件"),
                                 QMessageBox::Ok | QMessageBox::Cancel) !=
      QMessageBox::Ok) { return; }
  }
  else {
    pixFilePath = QFileDialog::getSaveFileName(
      this,
      tr("另存为"),
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      "*.png;;*.jpg;;*.jpeg"
    );
    if (pixFilePath.isEmpty()) { return; }
  }

  if (historyPixmap.top().save(pixFilePath)) {
    showInformationMessage(tr("保存成功"), true);
    //
    historyPixmap.afterSavePixmap();
    srcPixmap = historyPixmap.top();
    shouldBeProcessed = historyPixmap.top();
  }
  else { showInformationMessage(tr("保存失败"), false); }
}

void PS::showInformationMessage(const QString& message, const bool isSuccess)
{
  auto* information = new MyInformationBox(this);
  if (isSuccess) { information->setText(message); }
  else { information->setText(tr("保存失败")); }
  information->show();
}

void PS::doToolBoxChanged(const int index)
{
  Q_UNUSED(index);
  shouldBeProcessed = historyPixmap.top();
}

void PS::doCropChange(const int row) const
{
  const auto pixmap = Crop::cropPixmapBy(shouldBeProcessed, row);
  showImgToUi(pixmap);
  pushToHistory(pixmap);
}

void PS::doResizeChange(const int row) const
{
  const QPixmap pixmap = Resize::resizePixmapBy(
    shouldBeProcessed, row, ui->lockedWHRatio->isChecked());
  showImgToUi(pixmap);
  pushToHistory(pixmap);
}

void PS::updateUIState(const bool enable) const
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

void PS::pushToHistory(const QPixmap& pixmap)
{
  historyPixmap.pushBack(pixmap);
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
    const QPixmap pixmap = QPixmap::fromImage(QImage(localFile));
    showImgToUi(pixmap);
    // 使工具栏可用并存入历史
    srcPixmap = pixmap;
    ui->toolBox->setEnabled(true);
    historyPixmap.pushBack(pixmap);
    pixFilePath = localFile;
  }
  QWidget::dropEvent(event);
}

PS::~PS() { delete ui; }
