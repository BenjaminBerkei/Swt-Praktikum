/****************************************************************************
** Meta object code from reading C++ file 'startmenuewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BattleIsle/startmenuewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'startmenuewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StartMenueWidget_t {
    QByteArrayData data[6];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StartMenueWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StartMenueWidget_t qt_meta_stringdata_StartMenueWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "StartMenueWidget"
QT_MOC_LITERAL(1, 17, 30), // "SIGNAL_smwChangeIndexFromStack"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 28), // "on_qbutton_startGame_clicked"
QT_MOC_LITERAL(4, 78, 27), // "on_qbutton_loadGame_clicked"
QT_MOC_LITERAL(5, 106, 26) // "on_qbutton_options_clicked"

    },
    "StartMenueWidget\0SIGNAL_smwChangeIndexFromStack\0"
    "\0on_qbutton_startGame_clicked\0"
    "on_qbutton_loadGame_clicked\0"
    "on_qbutton_options_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StartMenueWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   37,    2, 0x08 /* Private */,
       4,    0,   38,    2, 0x08 /* Private */,
       5,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StartMenueWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StartMenueWidget *_t = static_cast<StartMenueWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIGNAL_smwChangeIndexFromStack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_qbutton_startGame_clicked(); break;
        case 2: _t->on_qbutton_loadGame_clicked(); break;
        case 3: _t->on_qbutton_options_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StartMenueWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StartMenueWidget::SIGNAL_smwChangeIndexFromStack)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject StartMenueWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StartMenueWidget.data,
      qt_meta_data_StartMenueWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StartMenueWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StartMenueWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StartMenueWidget.stringdata0))
        return static_cast<void*>(const_cast< StartMenueWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int StartMenueWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void StartMenueWidget::SIGNAL_smwChangeIndexFromStack(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
