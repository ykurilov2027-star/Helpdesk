#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include <QPushButton>

TicketDialog::TicketDialog(Mode mode, QWidget *parent)
    : QDialog(parent), ui(new Ui::TicketDialog), currentMode(mode) {
    ui->setupUi(this);
    applyMode();

    connect(ui->btnEdit, &QPushButton::clicked, this, &TicketDialog::onEditClicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::close);
    connect(ui->btnCancel, &QPushButton::clicked, this, &QDialog::close);
    connect(ui->btnSave, &QPushButton::clicked, this, &QDialog::accept);
}

void TicketDialog::applyMode() {
    bool isReadOnly = (currentMode == Mode::View);

    ui->editTitle->setReadOnly(isReadOnly);
    ui->editDescription->setReadOnly(isReadOnly);
    ui->comboPriority->setEnabled(!isReadOnly);
    ui->comboStatus->setEnabled(!isReadOnly);

    ui->btnEdit->setVisible(isReadOnly);
    ui->btnClose->setVisible(isReadOnly);
    ui->btnSave->setVisible(!isReadOnly);
    ui->btnCancel->setVisible(!isReadOnly);

    if (currentMode == Mode::View) setWindowTitle("View Ticket");
    else if (currentMode == Mode::Edit) setWindowTitle("Edit Ticket");
    else setWindowTitle("New Ticket");
}

void TicketDialog::onEditClicked() {
    currentMode = Mode::Edit;
    applyMode();
}

TicketDialog::~TicketDialog() {
    delete ui;
}
