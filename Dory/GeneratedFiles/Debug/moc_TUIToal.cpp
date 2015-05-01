/****************************************************************************
** Meta object code from reading C++ file 'TUIToal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TUIToal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TUIToal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TUIToal_t {
    QByteArrayData data[12];
    char stringdata[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TUIToal_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TUIToal_t qt_meta_stringdata_TUIToal = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 8),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 11),
QT_MOC_LITERAL(4, 30, 9),
QT_MOC_LITERAL(5, 40, 4),
QT_MOC_LITERAL(6, 45, 17),
QT_MOC_LITERAL(7, 63, 5),
QT_MOC_LITERAL(8, 69, 15),
QT_MOC_LITERAL(9, 85, 4),
QT_MOC_LITERAL(10, 90, 7),
QT_MOC_LITERAL(11, 98, 9)
    },
    "TUIToal\0UpdateDB\0\0slotAddData\0TInfoData\0"
    "data\0slotSelectChanged\0index\0"
    "slotDateChanged\0date\0slotDel\0slotClear\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TUIToal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x08,
       6,    1,   48,    2, 0x08,
       8,    1,   51,    2, 0x08,
      10,    0,   54,    2, 0x08,
      11,    0,   55,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QDate,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TUIToal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TUIToal *_t = static_cast<TUIToal *>(_o);
        switch (_id) {
        case 0: _t->UpdateDB(); break;
        case 1: _t->slotAddData((*reinterpret_cast< TInfoData(*)>(_a[1]))); break;
        case 2: _t->slotSelectChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 4: _t->slotDel(); break;
        case 5: _t->slotClear(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TUIToal::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TUIToal::UpdateDB)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TUIToal::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TUIToal.data,
      qt_meta_data_TUIToal,  qt_static_metacall, 0, 0}
};


const QMetaObject *TUIToal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TUIToal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TUIToal.stringdata))
        return static_cast<void*>(const_cast< TUIToal*>(this));
    return QWidget::qt_metacast(_clname);
}

int TUIToal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TUIToal::UpdateDB()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
