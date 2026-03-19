#include "ticketdialog.h"
#include "ui_ticketdialog.h"

TicketDialog::TicketDialog(Mode mode, QWidget *parent)
    : QDialog(parent), ui(new Ui::TicketDialog), currentMode(mode) {
    ui->setupUi(this);
    applyMode();

    connect(ui->editTitle, &QLineEdit::textChanged, this, &TicketDialog::validateForm);
    connect(ui->btnEdit, &QPushButton::clicked, this, &TicketDialog::onEditClicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::close);
    connect(ui->btnCancel, &QPushButton::clicked, this, &QDialog::close);
    connect(ui->btnSave, &QPushButton::clicked, this, &QDialog::accept);

    validateForm();
}

TicketDialog::~TicketDialog() { delete ui; }

void TicketDialog::setTicket(const Ticket &t) {
    ui->editTitle->setText(t.title);
    ui->comboPriority->setCurrentText(t.priority);
    ui->comboStatus->setCurrentText(t.status);
    validateForm();
}

Ticket TicketDialog::getTicket() const {
    Ticket t;
    t.title = ui->editTitle->text().trimmed();
    t.priority = ui->comboPriority->currentText();
    t.status = ui->comboStatus->currentText();
    return t;
}

bool TicketDialog::isValid() const {
    return !ui->editTitle->text().trimmed().isEmpty();
}

void TicketDialog::validateForm() {
    if (currentMode != Mode::View) {
        ui->btnSave->setEnabled(isValid());
    }
}

void TicketDialog::applyMode() {
    bool isReadOnly = (currentMode == Mode::View);
    ui->editTitle->setReadOnly(isReadOnly);
    ui->comboPriority->setEnabled(!isReadOnly);
    ui->comboStatus->setEnabled(!isReadOnly);

    ui->btnEdit->setVisible(isReadOnly);
    ui->btnClose->setVisible(isReadOnly);
    ui->btnSave->setVisible(!isReadOnly);
    ui->btnCancel->setVisible(!isReadOnly);

    validateForm();
}

void TicketDialog::onEditClicked() {
    currentMode = Mode::Edit;
    applyMode();
}
