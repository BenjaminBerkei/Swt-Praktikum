/****************************************************************************
** Meta object code from reading C++ file 'gamewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BattleIsle/gamewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameWidget_t {
    QByteArrayData data[13];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameWidget_t qt_meta_stringdata_GameWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameWidget"
QT_MOC_LITERAL(1, 11, 34), // "SIGNAL_gameWidChangeIndexFrom..."
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 24), // "SIGNAL_MenueButtonPushed"
QT_MOC_LITERAL(4, 72, 27), // "SIGNAL_changeStateOfButtons"
QT_MOC_LITERAL(5, 100, 28), // "SLOT_qbuttonSaveGame_clicked"
QT_MOC_LITERAL(6, 129, 28), // "SLOT_qbuttonLoadGame_clicked"
QT_MOC_LITERAL(7, 158, 27), // "SLOT_qbuttonEndGame_clicked"
QT_MOC_LITERAL(8, 186, 26), // "SLOT_qbuttonResume_clicked"
QT_MOC_LITERAL(9, 213, 21), // "SLOT_gameWidCenterHex"
QT_MOC_LITERAL(10, 235, 18), // "HexagonMatchfield*"
QT_MOC_LITERAL(11, 254, 3), // "hex"
QT_MOC_LITERAL(12, 258, 22) // "SLOT_gameWidDestroyMap"

    },
    "GameWidget\0SIGNAL_gameWidChangeIndexFromStack\0"
    "\0SIGNAL_MenueButtonPushed\0"
    "SIGNAL_changeStateOfButtons\0"
    "SLOT_qbuttonSaveGame_clicked\0"
    "SLOT_qbuttonLoadGame_clicked\0"
    "SLOT_qbuttonEndGame_clicked\0"
    "SLOT_qbuttonResume_clicked\0"
    "SLOT_gameWidCenterHex\0HexagonMatchfield*\0"
    "hex\0SLOT_gameWidDestroyMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,
       4,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   66,    2, 0x08 /* Private */,
       6,    0,   67,    2, 0x08 /* Private */,
       7,    0,   68,    2, 0x08 /* Private */,
       8,    0,   69,    2, 0x08 /* Private */,
       9,    1,   70,    2, 0x08 /* Private */,
      12,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void GameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameWidget *_t = static_cast<GameWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIGNAL_gameWidChangeIndexFromStack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SIGNAL_MenueButtonPushed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SIGNAL_changeStateOfButtons(); break;
        case 3: _t->SLOT_qbuttonSaveGame_clicked(); break;
        case 4: _t->SLOT_qbuttonLoadGame_clicked(); break;
        case 5: _t->SLOT_qbuttonEndGame_clicked(); break;
        case 6: _t->SLOT_qbuttonResume_clicked(); break;
        case 7: _t->SLOT_gameWidCenterHex((*reinterpret_cast< HexagonMatchfield*(*)>(_a[1]))); break;
        case 8: _t->SLOT_gameWidDestroyMap(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< HexagonMatchfield* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GameWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameWidget::SIGNAL_gameWidChangeIndexFromStack)) {
                *result = 0;
            }
        }
        {
            typedef void (GameWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameWidget::SIGNAL_MenueButtonPushed)) {
                *result = 1;
            }
        }
        {
            typedef void (GameWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameWidget::SIGNAL_changeStateOfButtons)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject GameWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GameWidget.data,
      qt_meta_data_GameWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GameWidget.stringdata0))
        return static_cast<void*>(const_cast< GameWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GameWidget::SIGNAL_gameWidChangeIndexFromStack(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameWidget::SIGNAL_MenueButtonPushed(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameWidget::SIGNAL_changeStateOfButtons()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
struct qt_meta_stringdata_HexagonDisplayInfo_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HexagonDisplayInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HexagonDisplayInfo_t qt_meta_stringdata_HexagonDisplayInfo = {
    {
QT_MOC_LITERAL(0, 0, 18) // "HexagonDisplayInfo"

    },
    "HexagonDisplayInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HexagonDisplayInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void HexagonDisplayInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject HexagonDisplayInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HexagonDisplayInfo.data,
      qt_meta_data_HexagonDisplayInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HexagonDisplayInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HexagonDisplayInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HexagonDisplayInfo.stringdata0))
        return static_cast<void*>(const_cast< HexagonDisplayInfo*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< HexagonDisplayInfo*>(this));
    return QObject::qt_metacast(_clname);
}

int HexagonDisplayInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_UnitDisplayInfo_t {
    QByteArrayData data[5];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UnitDisplayInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UnitDisplayInfo_t qt_meta_stringdata_UnitDisplayInfo = {
    {
QT_MOC_LITERAL(0, 0, 15), // "UnitDisplayInfo"
QT_MOC_LITERAL(1, 16, 17), // "unitDispl_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "Unit*"
QT_MOC_LITERAL(4, 41, 4) // "unit"

    },
    "UnitDisplayInfo\0unitDispl_clicked\0\0"
    "Unit*\0unit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UnitDisplayInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void UnitDisplayInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UnitDisplayInfo *_t = static_cast<UnitDisplayInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->unitDispl_clicked((*reinterpret_cast< Unit*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UnitDisplayInfo::*_t)(Unit * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UnitDisplayInfo::unitDispl_clicked)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject UnitDisplayInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UnitDisplayInfo.data,
      qt_meta_data_UnitDisplayInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UnitDisplayInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UnitDisplayInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UnitDisplayInfo.stringdata0))
        return static_cast<void*>(const_cast< UnitDisplayInfo*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< UnitDisplayInfo*>(this));
    return QObject::qt_metacast(_clname);
}

int UnitDisplayInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void UnitDisplayInfo::unitDispl_clicked(Unit * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_MapPixel_t {
    QByteArrayData data[3];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapPixel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapPixel_t qt_meta_stringdata_MapPixel = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MapPixel"
QT_MOC_LITERAL(1, 9, 22), // "SIGNAL_mapPixelClicked"
QT_MOC_LITERAL(2, 32, 0) // ""

    },
    "MapPixel\0SIGNAL_mapPixelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapPixel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void MapPixel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapPixel *_t = static_cast<MapPixel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIGNAL_mapPixelClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MapPixel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapPixel::SIGNAL_mapPixelClicked)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MapPixel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MapPixel.data,
      qt_meta_data_MapPixel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MapPixel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapPixel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MapPixel.stringdata0))
        return static_cast<void*>(const_cast< MapPixel*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< MapPixel*>(this));
    return QObject::qt_metacast(_clname);
}

int MapPixel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MapPixel::SIGNAL_mapPixelClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
