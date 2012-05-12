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

	if (rank==0) {
		std::cout<<"Podaj ilosc wileladow: "<< std::flush << std::flush;
		std::cin>>ileWielbladow;
		std::cout<<"Wczytano ilosc wileladow:"<<ileWielbladow << std::endl << std::flush;
	}

	MPI_Bcast( &ileWielbladow, 1, MPI_INT, 0, MPI_COMM_WORLD );
	std::cout << "Hello, world!  I am " << rank << " of " << size << std::endl << std::flush;
	//std::cout << "There are " << ileWielbladow << " camels " << std::endl;

	inputThread = new InputThread;
	connect(inputThread,SIGNAL(wiadomoscOZajeciuZasobow(int,int,int)),SLOT(wiadomoscOZajeciuZasobow(int,int,int)));
	connect(inputThread,SIGNAL(wiadomoscOZwolnieniuZasobow(int,int,int)),SLOT(wiadomoscOZwolnieniuZasobow(int,int,int)));
	outputThread = new OutputThread;

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

void MainObject::wiadomoscOZwolnieniuZasobow(int czas, int kto, int ile)
{
	std::cout << time(0) << "Ktoś zwolnił wielbłądy" << std::endl << std::flush;
}

void MainObject::wiadomoscOZajeciuZasobow(int czas, int kto, int ile)
{
	std::cout << time(0) << "Ktoś zajął wielbłądy" << std::endl << std::flush;
}

bool operator<(const Request& A, const Request& B) {
	if (A.requestTime == B.requestTime) return A.banditId < B.banditId;
	return A.requestTime < B.requestTime;
}
