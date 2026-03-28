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
    proxyModel = new QSortFilterProxyModel(this);

    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(TicketTableModel::TitleCol);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    setupTableView();

    TicketRepository repo("tickets.csv");
    model->setTickets(repo.load());

    connect(ui->editSearch, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(ui->comboFilterStatus, &QComboBox::currentTextChanged, this, &MainWindow::onStatusFilterChanged);
    connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::onTableDoubleClicked);

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

void MainWindow::setupTableView() {
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(TicketTableModel::TitleCol, QHeaderView::Stretch);
    ui->tableView->sortByColumn(TicketTableModel::IdCol, Qt::DescendingOrder);
}

void MainWindow::onSearchTextChanged(const QString &text) {
    proxyModel->setFilterKeyColumn(TicketTableModel::TitleCol);
    proxyModel->setFilterFixedString(text);
}

void MainWindow::onStatusFilterChanged(const QString &status) {
    if (status == "All") {
        proxyModel->setFilterKeyColumn(-1);
        proxyModel->setFilterFixedString("");
    } else {
        proxyModel->setFilterKeyColumn(TicketTableModel::StatusCol);
        proxyModel->setFilterFixedString(status);
    }
}

void MainWindow::onTableDoubleClicked(const QModelIndex &index) {
    onActionView();
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
    QModelIndex proxyIdx = ui->tableView->currentIndex();
    if (!proxyIdx.isValid()) return;

    QModelIndex sourceIdx = proxyModel->mapToSource(proxyIdx);
    Ticket t = model->getTicket(sourceIdx.row());

    TicketDialog dlg(TicketDialog::Mode::Edit, this);
    dlg.setTicket(t);
    if (dlg.exec() == QDialog::Accepted) {
        Ticket updated = dlg.getTicket();
        updated.id = t.id;
        updated.createdAt = t.createdAt;
        model->updateTicket(sourceIdx.row(), updated);
        TicketRepository("tickets.csv").save(model->getAllTickets());
    }
}

void MainWindow::onActionView() {
    QModelIndex proxyIdx = ui->tableView->currentIndex();
    if (!proxyIdx.isValid()) return;

    QModelIndex sourceIdx = proxyModel->mapToSource(proxyIdx);
    TicketDialog dlg(TicketDialog::Mode::View, this);
    dlg.setTicket(model->getTicket(sourceIdx.row()));
    dlg.exec();
}

void MainWindow::onActionDelete() {
    QModelIndex proxyIdx = ui->tableView->currentIndex();
    if (!proxyIdx.isValid()) return;

    if (QMessageBox::question(this, "Confirm", "Delete selected ticket?") == QMessageBox::Yes) {
        QModelIndex sourceIdx = proxyModel->mapToSource(proxyIdx);
        model->removeTicket(sourceIdx.row());
        TicketRepository("tickets.csv").save(model->getAllTickets());
    }
}

void MainWindow::updateActions() {
    bool hasSelection = ui->tableView->selectionModel()->hasSelection();
    ui->actionEdit->setEnabled(hasSelection);
    ui->actionDelete->setEnabled(hasSelection);
    ui->actionView->setEnabled(hasSelection);
}
