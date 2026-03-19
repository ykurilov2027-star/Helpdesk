#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticketdialog.h"
#include "ticketrepository.h"
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    model = new TicketTableModel(this);
    ui->tableView->setModel(model);

    TicketRepository repo("tickets.csv");
    model->setTickets(repo.load());

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::updateActions);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    updateActions();
}

MainWindow::~MainWindow() {
    TicketRepository repo("tickets.csv");
    repo.save(model->getAllTickets());
    delete ui;
}

void MainWindow::onActionNew() {
    TicketDialog dlg(TicketDialog::Mode::New, this);
    if (dlg.exec() == QDialog::Accepted) {
        Ticket t = dlg.getTicket();
        t.id = model->getNextId();
        t.createdAt = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
        model->addTicket(t);
        TicketRepository("tickets.csv").save(model->getAllTickets());
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
        TicketRepository("tickets.csv").save(model->getAllTickets());
    }
}

void MainWindow::onActionDelete() {
    QModelIndex idx = ui->tableView->currentIndex();
    if (!idx.isValid()) return;
    if (QMessageBox::question(this, "Confirm", "Delete ticket?") == QMessageBox::Yes) {
        model->removeTicket(idx.row());
        TicketRepository("tickets.csv").save(model->getAllTickets());
    }
}

void MainWindow::onActionView() {
    QModelIndex idx = ui->tableView->currentIndex();
    if (!idx.isValid()) return;
    TicketDialog dlg(TicketDialog::Mode::View, this);
    dlg.setTicket(model->getTicket(idx.row()));
    dlg.exec();
}

void MainWindow::updateActions() {
    bool hasSelection = ui->tableView->selectionModel()->hasSelection();
    ui->actionEdit->setEnabled(hasSelection);
    ui->actionDelete->setEnabled(hasSelection);
    ui->actionView->setEnabled(hasSelection);
}
