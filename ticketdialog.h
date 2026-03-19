#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
#include "ticket.h"

namespace Ui { class TicketDialog; }

class TicketDialog : public QDialog {
    Q_OBJECT

public:
    enum class Mode { New, View, Edit };
    explicit TicketDialog(Mode mode, QWidget *parent = nullptr);
    ~TicketDialog();

    void setTicket(const Ticket &t);
    Ticket getTicket() const;

private slots:
    void onEditClicked();
    void validateForm();

private:
    Ui::TicketDialog *ui;
    Mode currentMode;
    void applyMode();
    bool isValid() const;
};

#endif
