#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticketdialog.h"
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Title", "Priority", "Status", "Created At"});
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->statusbar->showMessage("Ready");
    lblStats = new QLabel("Total: 0  Filtered: 0", this);
    ui->statusbar->addPermanentWidget(lblStats);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearFilters);
}

void MainWindow::onActionNew() {
    TicketDialog *dlg = new TicketDialog(TicketDialog::Mode::New, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::onActionView() {
    TicketDialog *dlg = new TicketDialog(TicketDialog::Mode::View, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::onActionEdit() {
    TicketDialog *dlg = new TicketDialog(TicketDialog::Mode::Edit, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::onClearFilters() {
    ui->comboFilterStatus->setCurrentIndex(0);
    ui->comboFilterPriority->setCurrentIndex(0);
    ui->editSearch->clear();
}

MainWindow::~MainWindow() {
    delete ui;
}
