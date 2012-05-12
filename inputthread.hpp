#ifndef COMMUNICATIONTHREAD_HPP
#define COMMUNICATIONTHREAD_HPP

#include <QThread>
#include <mpi/mpi.h>

#define TAG_ZAJMOWANIE_ZASOBOW 1
#define TAG_ZWALNIANIE_ZASOBOW 2
#define TAG_POTWIERDZENIE_ODBIORU 3

extern int size, rank;

class InputThread : public QThread
{
	Q_OBJECT
public:
	explicit InputThread(QObject *parent = 0);
	int bufor[2]; //czas, ilosc
	MPI_Status status;
signals:
public slots:
	void listen();

protected:
	void run();
};

#endif // COMMUNICATIONTHREAD_HPP
