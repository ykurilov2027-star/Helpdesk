#include "ticketrepository.h"

TicketRepository::TicketRepository(const QString &filePath) : m_filePath(filePath) {}

QVector<Ticket> TicketRepository::load() {
    QVector<Ticket> tickets;
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return tickets;

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    if (!in.atEnd()) in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        if (fields.size() >= 5) {
            tickets.append(Ticket::fromCsvRow(fields));
        }
    }
    file.close();
    return tickets;
}

void TicketRepository::save(const QVector<Ticket> &tickets) {
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << Ticket::csvHeader().join(";") << "\n";

    for (const auto &t : tickets) {
        out << t.toCsvRow().join(";") << "\n";
    }
    file.close();
}
