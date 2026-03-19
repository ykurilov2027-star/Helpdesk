#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticketdialog.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    model = new TicketTableModel(this);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::updateActions);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    updateActions();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateActions() {
    bool hasSelection = ui->tableView->selectionModel()->hasSelection();
    ui->actionEdit->setEnabled(hasSelection);
    ui->actionDelete->setEnabled(hasSelection);
    ui->actionView->setEnabled(hasSelection);
}

void MainWindow::onActionNew() {
    TicketDialog dlg(TicketDialog::Mode::New, this);
    if (dlg.exec() == QDialog::Accepted) {
        Ticket t = dlg.getTicket();
        t.id = model->rowCount() + 1;
        t.createdAt = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
        model->addTicket(t);
    }
}

void MainWindow::onActionEdit() {
    QModelIndex idx = ui->tableView->currentIndex();
    if (!idx.isValid()) return;
    Ticket t = model->getTicket(idx.row());
    TicketDialog dlg(TicketDialog::Mode::Edit, this);
    dlg.setTicket(t);
    if (dlg.exec() == QDialog::Accepted) {
        Ticket updated = dlg.getTicket();
        updated.id = t.id;
        updated.createdAt = t.createdAt;
        model->updateTicket(idx.row(), updated);
    }
}

void MainWindow::onActionView() {
    QModelIndex idx = ui->tableView->currentIndex();
    if (!idx.isValid()) return;
    TicketDialog dlg(TicketDialog::Mode::View, this);
    dlg.setTicket(model->getTicket(idx.row()));
    dlg.exec();
}

void MainWindow::onActionDelete() {
    QModelIndex idx = ui->tableView->currentIndex();
    if (idx.isValid()) model->removeTicket(idx.row());
}
