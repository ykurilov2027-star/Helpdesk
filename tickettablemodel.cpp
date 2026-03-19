#include "tickettablemodel.h"

TicketTableModel::TicketTableModel(QObject* parent) : QAbstractTableModel(parent) {}

int TicketTableModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : tickets_.size();
}

int TicketTableModel::columnCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : ColCount;
}

QVariant TicketTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return QVariant();
    switch (section) {
    case IdCol: return "ID";
    case TitleCol: return "Title";
    case PriorityCol: return "Priority";
    case StatusCol: return "Status";
    case CreatedAtCol: return "Created At";
    default: return QVariant();
    }
}

QVariant TicketTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();
    const Ticket& t = tickets_.at(index.row());
    switch (index.column()) {
    case IdCol: return t.id;
    case TitleCol: return t.title;
    case PriorityCol: return t.priority;
    case StatusCol: return t.status;
    case CreatedAtCol: return t.createdAt;
    default: return QVariant();
    }
}

void TicketTableModel::addTicket(const Ticket& ticket) {
    int row = tickets_.size();
    beginInsertRows(QModelIndex(), row, row);
    tickets_.push_back(ticket);
    endInsertRows();
}

void TicketTableModel::updateTicket(int row, const Ticket& ticket) {
    if (row < 0 || row >= tickets_.size()) return;
    tickets_[row] = ticket;
    emit dataChanged(index(row, 0), index(row, ColCount - 1));
}

void TicketTableModel::removeTicket(int row) {
    if (row < 0 || row >= tickets_.size()) return;
    beginRemoveRows(QModelIndex(), row, row);
    tickets_.removeAt(row);
    endRemoveRows();
}

Ticket TicketTableModel::getTicket(int row) const {
    return tickets_.at(row);
}
