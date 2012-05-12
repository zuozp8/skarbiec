#ifndef RANDOMINGTHREAD_HPP
#define RANDOMINGTHREAD_HPP

#include <QThread>

class OutputThread : public QThread
{
	Q_OBJECT
public:
	explicit OutputThread(QObject *parent = 0);
	bool czyRabuje;
signals:
	
public slots:

protected:
	int exec();
	
};

#endif // RANDOMINGTHREAD_HPP
