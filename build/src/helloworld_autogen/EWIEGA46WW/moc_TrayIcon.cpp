/****************************************************************************
** Meta object code from reading C++ file 'TrayIcon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/TrayIcon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrayIcon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrayIcon_t {
    QByteArrayData data[16];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrayIcon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrayIcon_t qt_meta_stringdata_TrayIcon = {
    {
QT_MOC_LITERAL(0, 0, 8), // "TrayIcon"
QT_MOC_LITERAL(1, 9, 6), // "action"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "QAction*"
QT_MOC_LITERAL(4, 26, 12), // "clearActions"
QT_MOC_LITERAL(5, 39, 4), // "show"
QT_MOC_LITERAL(6, 44, 4), // "hide"
QT_MOC_LITERAL(7, 49, 10), // "setVisible"
QT_MOC_LITERAL(8, 60, 7), // "visible"
QT_MOC_LITERAL(9, 68, 7), // "setIcon"
QT_MOC_LITERAL(10, 76, 4), // "icon"
QT_MOC_LITERAL(11, 81, 9), // "isVisible"
QT_MOC_LITERAL(12, 91, 10), // "setToolTip"
QT_MOC_LITERAL(13, 102, 7), // "tooltip"
QT_MOC_LITERAL(14, 110, 7), // "toolTip"
QT_MOC_LITERAL(15, 118, 7) // "actions"

    },
    "TrayIcon\0action\0\0QAction*\0clearActions\0"
    "show\0hide\0setVisible\0visible\0setIcon\0"
    "icon\0isVisible\0setToolTip\0tooltip\0"
    "toolTip\0actions"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrayIcon[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       1,   82, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    0,   67,    2, 0x02 /* Public */,
       5,    0,   68,    2, 0x02 /* Public */,
       6,    0,   69,    2, 0x02 /* Public */,
       7,    1,   70,    2, 0x02 /* Public */,
       9,    1,   73,    2, 0x02 /* Public */,
      11,    0,   76,    2, 0x02 /* Public */,
      10,    0,   77,    2, 0x02 /* Public */,
      12,    1,   78,    2, 0x02 /* Public */,
      14,    0,   81,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    1,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Bool,
    QMetaType::QIcon,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::QString,

 // properties: name, type, flags
      15, QMetaType::QStringList, 0x00095103,

       0        // eod
};

void TrayIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrayIcon *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->action((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->clearActions(); break;
        case 2: _t->show(); break;
        case 3: _t->hide(); break;
        case 4: _t->setVisible((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 5: _t->setIcon((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: { bool _r = _t->isVisible();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { QIcon _r = _t->icon();
            if (_a[0]) *reinterpret_cast< QIcon*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->setToolTip((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: { QString _r = _t->toolTip();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrayIcon::*)(QAction * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrayIcon::action)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TrayIcon *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStringList*>(_v) = _t->actions(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TrayIcon *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setActions(*reinterpret_cast< QStringList*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject TrayIcon::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TrayIcon.data,
    qt_meta_data_TrayIcon,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TrayIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrayIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrayIcon.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TrayIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TrayIcon::action(QAction * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
