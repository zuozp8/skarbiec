#ifndef MAINOBJECT_HPP
#define MAINOBJECT_HPP

#include <QObject>
#include <QSet>

#include "inputthread.hpp"
#include "outputthread.hpp"

struct Request {
	int requestTime, banditId, ile;
};

bool operator<(const Request& A, const Request& B);

class MainObject : public QObject
{
	Q_OBJECT
public:
	explicit MainObject(QObject *parent = 0);

signals:
	void dostalesWielblady();
	void oddalesWielblady();

public slots:
	void wiadomoscOZwolnieniuZasobow(int czas, int kto, int ile);
	void wiadomoscOZajeciuZasobow(int czas, int kto, int ile);
	
private:
	void zabierzWielblady(int ile);
	bool sprobujZabracWielblady(int ile);
	InputThread* inputThread;
	OutputThread* outputThread;
	QSet<Request> kolejka;
	unsigned int* czas_odbierania;

	int ileWielbladow;
};

#endif // MAINOBJECT_HPP
