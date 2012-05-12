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
                caloscWielbladow = ileWielbladow;
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
        connect(this,SIGNAL(wiadomosc(int,int,int,int)),outputThread,SLOT(wyslij(int,int,int,int)),Qt::QueuedConnection);
	outputThread->start();

        zegarLamporta = 0;
        QTimer::singleShot(500 + 500*(qrand()%20),this, SLOT(rabowanie()));

}

void MainObject::rabowanie()
{
        potrzebneWielblady =( qrand()%9 + 1)/2;
        zegarLamporta++;
        wiadomosc(zegarLamporta ,potrzebneWielblady ,-1 ,TAG_ZAJMOWANIE_ZASOBOW );
		kolejka.push_back(utworzRequest(zegarLamporta,rank,potrzebneWielblady));
        przetworzKolejke();
}

void MainObject::dostalWiadomosc()
{
        //std::cout<<rank<<'|'<<"Odebralem: czas="<<inputThread->bufor[0]<<" ile="<<inputThread->bufor[1]<<" od="<<inputThread->status.MPI_SOURCE<<" tag="<<inputThread->status.MPI_TAG<<std::endl;
        this->czas_odbierania[inputThread->status.MPI_SOURCE] = inputThread->bufor[0];
        zegarLamporta = qMax(zegarLamporta, inputThread->bufor[0]);
        if(inputThread->status.MPI_TAG == TAG_ZWALNIANIE_ZASOBOW)
        {
			this->ileWielbladow += inputThread->bufor[1];
        }
        else if (inputThread->status.MPI_TAG == TAG_ZAJMOWANIE_ZASOBOW)
        {
			kolejka.push_back(utworzRequest(inputThread->bufor[0],inputThread->status.MPI_SOURCE,inputThread->bufor[1]));
            zegarLamporta++;
            wiadomosc(zegarLamporta,inputThread->bufor[1],inputThread->status.MPI_SOURCE, TAG_POTWIERDZENIE_ODBIORU);
        }
        inputThread->start();
        przetworzKolejke();
}

void MainObject::przetworzKolejke()
{
	qSort(kolejka.begin(),kolejka.end());
		while( !kolejka.empty() && ileWielbladow >= potrzebneWielblady && minimalnyCzasOdbioru() > kolejka.begin()->requestTime )
        {
            ileWielbladow -= kolejka.begin()->ile;
            if(kolejka.begin()->banditId == rank)
            {
                QTimer::singleShot(500 + 500*(qrand()%20),this,SLOT(skonczylemRabowac()));
            }
        }
}

void MainObject::skonczylemRabowac()
{
        ileWielbladow += potrzebneWielblady;
        wiadomosc(zegarLamporta ,potrzebneWielblady ,-1 ,TAG_ZWALNIANIE_ZASOBOW );
        potrzebneWielblady = 0;
        QTimer::singleShot(500 + 500*(qrand()%20),this, SLOT(rabowanie()));
}

void MainObject::wyslalem()
{
        std::cout<< "Wyslalem" << std::endl << std::flush;
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

Request MainObject::utworzRequest(int requestTime, int banditId ,int ile)
{
        Request request;
        request.banditId = banditId;
        request.requestTime = requestTime;
        request.ile = ile;
        return request;
}

int MainObject::minimalnyCzasOdbioru()
{
    int minCO = 2000000000;
    for(int i=0;i<size;i++)
    {
        if(czas_odbierania[i] < minCO)
        {
            minCO = czas_odbierania[i];
        }
    }
    return minCO;
}

bool operator<(const Request& A, const Request& B) {
	if (A.requestTime == B.requestTime) return A.banditId < B.banditId;
	return A.requestTime < B.requestTime;
}
