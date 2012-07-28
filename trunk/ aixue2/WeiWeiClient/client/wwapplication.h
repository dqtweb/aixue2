#ifndef WWAPPLICATION_H
#define WWAPPLICATION_H

#include <QApplication>


class WWApplication : public QApplication
{
	Q_OBJECT

public:
	WWApplication(QObject *parent);
	~WWApplication();

private:
	
};

#endif // WWAPPLICATION_H
