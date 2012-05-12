/****************************************************************************
** Meta object code from reading C++ file 'mainobject.hpp'
**
** Created: Sat May 12 17:12:08 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainobject.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainobject.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainObject[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   11,   11,   11, 0x0a,
      50,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainObject[] = {
    "MainObject\0\0dostalesWielblady()\0"
    "dostalWiadomosc()\0wyslalem()\0"
};

const QMetaObject MainObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainObject,
      qt_meta_data_MainObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainObject))
        return static_cast<void*>(const_cast< MainObject*>(this));
    return QObject::qt_metacast(_clname);
}

int MainObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dostalesWielblady(); break;
        case 1: dostalWiadomosc(); break;
        case 2: wyslalem(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MainObject::dostalesWielblady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
