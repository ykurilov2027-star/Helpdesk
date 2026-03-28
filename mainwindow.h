#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "tickettablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onActionNew();
    void onActionEdit();
    void onActionDelete();
    void onActionView();
    void onTableDoubleClicked(const QModelIndex &index);
    void onSearchTextChanged(const QString &text);
    void onStatusFilterChanged(const QString &status);
    void updateActions();

private:
    Ui::MainWindow *ui;
    TicketTableModel *model;
    QSortFilterProxyModel *proxyModel;
    void setupTableView();
};

#endif
