#ifndef TICKET_H
#define TICKET_H

#include <QString>
#include <QStringList>

struct Ticket {
    int id;
    QString title;
    QString priority;
    QString status;
    QString createdAt;

    static QStringList csvHeader() {
        return {"ID", "Title", "Priority", "Status", "CreatedAt"};
    }

    QStringList toCsvRow() const {
        return {QString::number(id), title, priority, status, createdAt};
    }

    static Ticket fromCsvRow(const QStringList &row) {
        Ticket t;
        if (row.size() >= 5) {
            t.id = row[0].toInt();
            t.title = row[1];
            t.priority = row[2];
            t.status = row[3];
            t.createdAt = row[4];
        }
        return t;
    }
};

#endif
