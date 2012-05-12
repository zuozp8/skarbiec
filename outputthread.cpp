#include "outputthread.hpp"
#include "inputthread.hpp"
#include <mpi/mpi.h>
#include <iostream>

OutputThread::OutputThread(QObject *parent) :
    QThread(parent)
{
	moveToThread(this);
	czyRabuje=false;
}

void OutputThread::timerEvent(QTimerEvent*)
{
	int tag  = (rand()%2?TAG_ZWALNIANIE_ZASOBOW:TAG_ZAJMOWANIE_ZASOBOW);
	for (int i=0; i<size; i++) {
		if (i == rank) continue;
		int bufor[2];
		bufor[0] = qrand()%100;//czas
		bufor[1] = qrand()%4+1;//ile
		std::cout <<rank<<'|'<< bufor[0]<<": Wysylam do " << i << " że " << (tag==TAG_ZWALNIANIE_ZASOBOW ? "zwalniam" : "zajmuje") << " " << bufor[1] << std::endl;
		MPI_Send(bufor, 2, MPI_INT, i, tag, MPI_COMM_WORLD);
		emit wyslalem();
	}
}


void OutputThread::run()
{
	qsrand(time(0)+100*rank);
	int timerID = startTimer(500 + 500*(qrand()%20));
	exec();
}
