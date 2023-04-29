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
    QByteArrayData data[19];
    char stringdata0[125];
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
QT_MOC_LITERAL(12, 65, 12), // "xdotoolGetId"
QT_MOC_LITERAL(13, 78, 13), // "x11_kwinGetId"
QT_MOC_LITERAL(14, 92, 9), // "waitForId"
QT_MOC_LITERAL(15, 102, 5), // "getId"
QT_MOC_LITERAL(16, 108, 6), // "toggle"
QT_MOC_LITERAL(17, 115, 4), // "show"
QT_MOC_LITERAL(18, 120, 4) // "hide"

    },
    "Embedder\0launch\0\0program\0embed\0Class\0"
    "setSize\0h\0w\0setPosition\0x\0y\0xdotoolGetId\0"
    "x11_kwinGetId\0waitForId\0getId\0toggle\0"
    "show\0hide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Embedder[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x02 /* Public */,
       4,    2,   72,    2, 0x02 /* Public */,
       6,    2,   77,    2, 0x02 /* Public */,
       9,    2,   82,    2, 0x02 /* Public */,
      12,    1,   87,    2, 0x02 /* Public */,
      13,    1,   90,    2, 0x02 /* Public */,
      14,    1,   93,    2, 0x02 /* Public */,
      15,    1,   96,    2, 0x02 /* Public */,
      16,    0,   99,    2, 0x02 /* Public */,
      17,    0,  100,    2, 0x02 /* Public */,
      18,    0,  101,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    3,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Int, QMetaType::QString,    5,
    QMetaType::Int, QMetaType::QString,    5,
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
        case 1: { bool _r = _t->embed((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->setSize((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->setPosition((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: { int _r = _t->xdotoolGetId((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->x11_kwinGetId((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->waitForId((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->getId((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->toggle(); break;
        case 9: _t->show(); break;
        case 10: _t->hide(); break;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
