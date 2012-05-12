#include "mainobject.hpp"
#include <mpi/mpi.h>
#include <iostream>

MainObject::MainObject(QObject *parent) :
    QObject(parent)
{
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	czas_odbierania = new unsigned int[size];
	for (int i=0; i<size; i++) {
		czas_odbierania[i] = (i==rank ? -1 : 0);
	}

	//std::cout << "Thread: " << QThread::currentThreadId() << std::endl << std::flush;
	if (rank==0) {
		std::cout<<"Podaj ilosc wileladow: "<< std::flush << std::flush;
		std::cin>>ileWielbladow;
		std::cout<<"Wczytano ilosc wileladow:"<<ileWielbladow << std::endl << std::flush;
	}

	MPI_Bcast( &ileWielbladow, 1, MPI_INT, 0, MPI_COMM_WORLD );
	std::cout << "Hello, world!  I am " << rank << " of " << size << std::endl << std::flush;
	//std::cout << "There are " << ileWielbladow << " camels " << std::endl;

	inputThread = new InputThread;
	connect(inputThread,SIGNAL(finished()),SLOT(dostalWiadomosc()),Qt::QueuedConnection);
	inputThread->start();
	outputThread = new OutputThread;
	connect(outputThread,SIGNAL(wyslalem()),SLOT(wyslalem()),Qt::QueuedConnection);
	connect(outputThread,SIGNAL(finished()),SLOT(dostalWiadomosc()),Qt::QueuedConnection);
	outputThread->start();

}

void MainObject::zabierzWielblady(int ile)
{
	ileWielbladow-=ile;
}

bool MainObject::sprobujZabracWielblady(int ile)
{
	if (ileWielbladow>=ile) {
		ileWielbladow-=ile;
		return true;
	}
	return false;
}

void MainObject::dostalWiadomosc()
{
	std::cout<<rank<<'|'<<"Odebralem: czas="<<inputThread->bufor[0]<<" ile="<<inputThread->bufor[1]<<" od="<<inputThread->status.MPI_SOURCE<<" tag="<<inputThread->status.MPI_TAG<<std::endl;
	inputThread->start();
}

void MainObject::wyslalem()
{
	std::cout<< "Wyslalem" << std::endl << std::flush;
}

bool operator<(const Request& A, const Request& B) {
	if (A.requestTime == B.requestTime) return A.banditId < B.banditId;
	return A.requestTime < B.requestTime;
}
