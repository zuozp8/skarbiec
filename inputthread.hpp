#ifndef COMMUNICATIONTHREAD_HPP
#define COMMUNICATIONTHREAD_HPP

#include <QThread>

#define TAG_ZAJMOWANIE_ZASOBOW 1
#define TAG_ZWALNIANIE_ZASOBOW 2

extern int size, rank;

class InputThread : public QThread
{
	Q_OBJECT
public:
	explicit InputThread(QObject *parent = 0);
	
signals:
	void wiadomoscOZwolnieniuZasobow(int czas, int kto, int ile);
	void wiadomoscOZajeciuZasobow(int czas, int kto, int ile);
public slots:

protected:
	int exec();

};

#endif // COMMUNICATIONTHREAD_HPP
