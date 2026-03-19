#ifndef TICKETREPOSITORY_H
#define TICKETREPOSITORY_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "ticket.h"

class TicketRepository {
public:
    explicit TicketRepository(const QString &filePath);

    QVector<Ticket> load();
    void save(const QVector<Ticket> &tickets);

private:
    QString m_filePath;
};

#endif
