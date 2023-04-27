/****************************************************************************
** Meta object code from reading C++ file 'Embedder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/Embedder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Embedder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Embedder_t {
    QByteArrayData data[17];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Embedder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Embedder_t qt_meta_stringdata_Embedder = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Embedder"
QT_MOC_LITERAL(1, 9, 6), // "launch"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 7), // "program"
QT_MOC_LITERAL(4, 25, 5), // "embed"
QT_MOC_LITERAL(5, 31, 5), // "Class"
QT_MOC_LITERAL(6, 37, 7), // "setSize"
QT_MOC_LITERAL(7, 45, 1), // "h"
QT_MOC_LITERAL(8, 47, 1), // "w"
QT_MOC_LITERAL(9, 49, 11), // "setPosition"
QT_MOC_LITERAL(10, 61, 1), // "x"
QT_MOC_LITERAL(11, 63, 1), // "y"
QT_MOC_LITERAL(12, 65, 12), // "getRealWinID"
QT_MOC_LITERAL(13, 78, 12), // "xdotoolGetId"
QT_MOC_LITERAL(14, 91, 6), // "toggle"
QT_MOC_LITERAL(15, 98, 4), // "show"
QT_MOC_LITERAL(16, 103, 4) // "hide"

    },
    "Embedder\0launch\0\0program\0embed\0Class\0"
    "setSize\0h\0w\0setPosition\0x\0y\0getRealWinID\0"
    "xdotoolGetId\0toggle\0show\0hide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Embedder[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x02 /* Public */,
       4,    1,   62,    2, 0x02 /* Public */,
       6,    2,   65,    2, 0x02 /* Public */,
       9,    2,   70,    2, 0x02 /* Public */,
      12,    1,   75,    2, 0x02 /* Public */,
      13,    1,   78,    2, 0x02 /* Public */,
      14,    0,   81,    2, 0x02 /* Public */,
      15,    0,   82,    2, 0x02 /* Public */,
      16,    0,   83,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Int, QMetaType::QString,    5,
    QMetaType::Int, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Embedder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Embedder *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { int _r = _t->launch((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->embed((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->setSize((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->setPosition((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: { int _r = _t->getRealWinID((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->xdotoolGetId((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->toggle(); break;
        case 7: _t->show(); break;
        case 8: _t->hide(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Embedder::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Embedder.data,
    qt_meta_data_Embedder,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Embedder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Embedder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Embedder.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Embedder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
