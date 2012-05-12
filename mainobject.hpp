#ifndef MAINOBJECT_HPP
#define MAINOBJECT_HPP

#include <QObject>
#include <QSet>
#include <QTimer>

#include "inputthread.hpp"
#include "outputthread.hpp"

struct Request {
	int requestTime, banditId, ile;
};

bool operator<(const Request& A, const Request& B);
bool operator==(const Request& A, const Request& B);

class MainObject : public QObject
{
	Q_OBJECT
public:
	explicit MainObject(QObject *parent = 0);

signals:
        void wiadomosc(int,int,int,int);
	void dostalesWielblady(); //TODO: polancz z odliczaniem do oddania wielbladow

public slots:
	void dostalWiadomosc();
	void wyslalem();
	//void zrabowalemICzekamNaWielblady(int czas, int ile);
        void skonczylemRabowac();
private:
        int minimalnyCzasOdbioru();
        void rabowanie();
        void przetworzKolejke();
	void zabierzWielblady(int ile);
	bool sprobujZabracWielblady(int ile);
        Request utworzRequest(int requestTime, int banditId ,int ile);
        InputThread* inputThread;
	OutputThread* outputThread;
	QSet<Request> kolejka;
	unsigned int* czas_odbierania;

        int caloscWielbladow;
        int potrzebneWielblady;
	int ileWielbladow;
        int zegarLamporta;
};

#endif // MAINOBJECT_HPP
