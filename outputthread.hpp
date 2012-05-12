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
	void wyslalem();
public slots:
protected:
	void run();
	void timerEvent(QTimerEvent *);
	
};

#endif // RANDOMINGTHREAD_HPP
