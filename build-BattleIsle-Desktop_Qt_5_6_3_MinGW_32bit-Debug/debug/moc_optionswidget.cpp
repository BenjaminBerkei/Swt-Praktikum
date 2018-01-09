/****************************************************************************
** Meta object code from reading C++ file 'optionswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BattleIsle/optionswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OptionsWidget_t {
    QByteArrayData data[5];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OptionsWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OptionsWidget_t qt_meta_stringdata_OptionsWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "OptionsWidget"
QT_MOC_LITERAL(1, 14, 30), // "SIGNAL_optChangeIndexFromStack"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 24), // "on_qbutton_apply_clicked"
QT_MOC_LITERAL(4, 71, 25) // "on_qbutton_cancel_clicked"

    },
    "OptionsWidget\0SIGNAL_optChangeIndexFromStack\0"
    "\0on_qbutton_apply_clicked\0"
    "on_qbutton_cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OptionsWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   32,    2, 0x08 /* Private */,
       4,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OptionsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OptionsWidget *_t = static_cast<OptionsWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIGNAL_optChangeIndexFromStack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_qbutton_apply_clicked(); break;
        case 2: _t->on_qbutton_cancel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OptionsWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OptionsWidget::SIGNAL_optChangeIndexFromStack)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject OptionsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OptionsWidget.data,
      qt_meta_data_OptionsWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OptionsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OptionsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OptionsWidget.stringdata0))
        return static_cast<void*>(const_cast< OptionsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int OptionsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void OptionsWidget::SIGNAL_optChangeIndexFromStack(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
