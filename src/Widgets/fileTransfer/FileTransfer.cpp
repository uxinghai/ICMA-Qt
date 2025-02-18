#include "FileTransfer.h"

#include "../../../UI/ui_FileTransfer.h"
#include "client/AClient.h"
#include "server/AServer.h"

FileTrans::FileTrans(QWidget* parent)
  : QWidget(parent), ui(new Ui::FileTrans)
{
  ui->setupUi(this);
  setupConnections();
  this->setAttribute(Qt::WA_DeleteOnClose);
}

void FileTrans::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
  QWidget::closeEvent(event);
}

void FileTrans::doOpenSender()
{
  aClient = QSharedPointer<AClient>::create();
  connect(aClient.get(), &AClient::WindowClose, this, &FileTrans::close);
  this->hide();
  aClient->show();
}

void FileTrans::doOpenReceiver()
{
  aServer = QSharedPointer<AServer>::create();
  connect(aServer.get(), &AServer::WindowClose, this, &FileTrans::close);
  this->hide();
  aServer->show();
}

void FileTrans::setupConnections()
{
  connect(ui->btnSender, &QPushButton::clicked,
          this, &FileTrans::doOpenSender);
  connect(ui->btnReceiver, &QPushButton::clicked,
          this, &FileTrans::doOpenReceiver);
}

FileTrans::~FileTrans()
{
  qDebug() << "文件传输被正常析构";
  delete ui;
}
