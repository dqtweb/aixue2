#include "mroster.h"

MRoster::MRoster(QObject *parent) :
    QObject(parent)
{
}

QString MRoster::name() const
{
    return m_name;
}

void MRoster::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

MRoster::~MRoster()
{
    //delete data;
}
