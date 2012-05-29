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
	void wyslij(int czas,int ileW, int odbiorca, int tag);
protected:
	void run();

private:
	int bufor[2];
	int tag;
	int odbiorca;
	
};

#endif // RANDOMINGTHREAD_HPP
