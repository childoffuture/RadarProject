#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "client.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Client * client = new Client();

    QThread * thread = new QThread(this);
    client->moveToThread(thread);

    connect(ui->pushButton, &QPushButton::pressed, client, &Client::start);
    connect(client, &Client::dataRecieved, ui->widget, &RadarWidget::updateObjects);

    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

