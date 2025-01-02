// #include "FileTransfer.h"
//
// #include "lib/AClient.h"
// #include "lib/AServer.h"
// #include "ui_FileTransfer.h"
//
// FileTrans::FileTrans(QWidget *parent)
//     : QWidget(parent), ui(new Ui::FileTrans) {
//   ui->setupUi(this);
// }
//
// FileTrans::~FileTrans() {
//   delete ui;
// }
//
// void FileTrans::on_btnSender_clicked() {
//   aClient = QSharedPointer<AClient>::create();
//   this->hide();
//   aClient->show();
// }
//
// void FileTrans::on_btnReciver_clicked() {
//   aServer = QSharedPointer<AServer>::create();
//   this->hide();
//   aServer->show();
// }