/****************************************************************************
** Meta object code from reading C++ file 'TwitterConnection.hh'
**
** Created: Mon May 28 15:52:39 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TwitterConnection.hh"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TwitterConnection.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TwitterConnection[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      30,   18,   18,   18, 0x08,
      42,   40,   18,   18, 0x08,
      71,   18,   18,   18, 0x08,
     106,   97,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TwitterConnection[] = {
    "TwitterConnection\0\0tmpToken()\0success()\0"
    ",\0accessToken(QString,QString)\0"
    "onAuthorizedRequestDone()\0response\0"
    "ready(QByteArray)\0"
};

const QMetaObject TwitterConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TwitterConnection,
      qt_meta_data_TwitterConnection, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TwitterConnection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TwitterConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TwitterConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TwitterConnection))
        return static_cast<void*>(const_cast< TwitterConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int TwitterConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tmpToken(); break;
        case 1: success(); break;
        case 2: accessToken((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: onAuthorizedRequestDone(); break;
        case 4: ready((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
