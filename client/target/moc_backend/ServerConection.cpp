/****************************************************************************
** Meta object code from reading C++ file 'ServerConection.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/backend/ServerConection.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ServerConection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ServerConection_t {
    uint offsetsAndSizes[36];
    char stringdata0[16];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[8];
    char stringdata5[4];
    char stringdata6[15];
    char stringdata7[9];
    char stringdata8[16];
    char stringdata9[5];
    char stringdata10[12];
    char stringdata11[6];
    char stringdata12[23];
    char stringdata13[19];
    char stringdata14[18];
    char stringdata15[10];
    char stringdata16[8];
    char stringdata17[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ServerConection_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ServerConection_t qt_meta_stringdata_ServerConection = {
    {
        QT_MOC_LITERAL(0, 15),  // "ServerConection"
        QT_MOC_LITERAL(16, 13),  // "loginResponse"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 4),  // "resp"
        QT_MOC_LITERAL(36, 7),  // "logData"
        QT_MOC_LITERAL(44, 3),  // "log"
        QT_MOC_LITERAL(48, 14),  // "logDataNumbers"
        QT_MOC_LITERAL(63, 8),  // "logTable"
        QT_MOC_LITERAL(72, 15),  // "genericResponse"
        QT_MOC_LITERAL(88, 4),  // "data"
        QT_MOC_LITERAL(93, 11),  // "onlineUsers"
        QT_MOC_LITERAL(105, 5),  // "users"
        QT_MOC_LITERAL(111, 22),  // "IncidentsResponseTable"
        QT_MOC_LITERAL(134, 18),  // "IncidentsChartData"
        QT_MOC_LITERAL(153, 17),  // "IncidentsResolved"
        QT_MOC_LITERAL(171, 9),  // "HostsEnum"
        QT_MOC_LITERAL(181, 7),  // "receive"
        QT_MOC_LITERAL(189, 3)   // "now"
    },
    "ServerConection",
    "loginResponse",
    "",
    "resp",
    "logData",
    "log",
    "logDataNumbers",
    "logTable",
    "genericResponse",
    "data",
    "onlineUsers",
    "users",
    "IncidentsResponseTable",
    "IncidentsChartData",
    "IncidentsResolved",
    "HostsEnum",
    "receive",
    "now"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ServerConection[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,
       4,    1,   83,    2, 0x06,    3 /* Public */,
       6,    1,   86,    2, 0x06,    5 /* Public */,
       7,    1,   89,    2, 0x06,    7 /* Public */,
       8,    1,   92,    2, 0x06,    9 /* Public */,
      10,    1,   95,    2, 0x06,   11 /* Public */,
      12,    1,   98,    2, 0x06,   13 /* Public */,
      13,    1,  101,    2, 0x06,   15 /* Public */,
      14,    1,  104,    2, 0x06,   17 /* Public */,
      15,    1,  107,    2, 0x06,   19 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,  110,    2, 0x08,   21 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

Q_CONSTINIT const QMetaObject ServerConection::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ServerConection.offsetsAndSizes,
    qt_meta_data_ServerConection,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ServerConection_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ServerConection, std::true_type>,
        // method 'loginResponse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'logData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'logDataNumbers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'logTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'genericResponse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onlineUsers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'IncidentsResponseTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'IncidentsChartData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'IncidentsResolved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'HostsEnum'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'receive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void ServerConection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerConection *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loginResponse((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->logData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->logDataNumbers((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->logTable((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->genericResponse((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onlineUsers((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->IncidentsResponseTable((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->IncidentsChartData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->IncidentsResolved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->HostsEnum((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->receive((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::loginResponse; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::logData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::logDataNumbers; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::logTable; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::genericResponse; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::onlineUsers; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::IncidentsResponseTable; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::IncidentsChartData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::IncidentsResolved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ServerConection::*)(QString );
            if (_t _q_method = &ServerConection::HostsEnum; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *ServerConection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerConection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerConection.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ServerConection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ServerConection::loginResponse(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerConection::logData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerConection::logDataNumbers(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ServerConection::logTable(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ServerConection::genericResponse(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ServerConection::onlineUsers(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ServerConection::IncidentsResponseTable(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ServerConection::IncidentsChartData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ServerConection::IncidentsResolved(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ServerConection::HostsEnum(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
