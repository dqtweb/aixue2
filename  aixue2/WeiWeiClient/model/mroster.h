#ifndef MROSTER_H
#define MROSTER_H


#include <QObject>

class MRoster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    MRoster(QObject *parent = 0);
    QString name() const;
    void setName(const QString &name);
    ~MRoster();
signals:
    void nameChanged();
public slots:
private:
    QString m_name;
};

#endif // MROSTER_H
