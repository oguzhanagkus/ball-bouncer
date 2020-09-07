/****************************************************************************
** Meta object code from reading C++ file 'plate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../server-app/plate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_plate_t {
    QByteArrayData data[25];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_plate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_plate_t qt_meta_stringdata_plate = {
    {
QT_MOC_LITERAL(0, 0, 5), // "plate"
QT_MOC_LITERAL(1, 6, 11), // "displayPath"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "display"
QT_MOC_LITERAL(4, 27, 6), // "getTh1"
QT_MOC_LITERAL(5, 34, 6), // "getTh2"
QT_MOC_LITERAL(6, 41, 6), // "getTh3"
QT_MOC_LITERAL(7, 48, 4), // "getX"
QT_MOC_LITERAL(8, 53, 4), // "getY"
QT_MOC_LITERAL(9, 58, 4), // "getZ"
QT_MOC_LITERAL(10, 63, 6), // "setTh1"
QT_MOC_LITERAL(11, 70, 3), // "th1"
QT_MOC_LITERAL(12, 74, 6), // "setTh2"
QT_MOC_LITERAL(13, 81, 3), // "th2"
QT_MOC_LITERAL(14, 85, 6), // "setTh3"
QT_MOC_LITERAL(15, 92, 3), // "th3"
QT_MOC_LITERAL(16, 96, 4), // "setZ"
QT_MOC_LITERAL(17, 101, 1), // "z"
QT_MOC_LITERAL(18, 103, 9), // "setTarget"
QT_MOC_LITERAL(19, 113, 2), // "tx"
QT_MOC_LITERAL(20, 116, 2), // "ty"
QT_MOC_LITERAL(21, 119, 2), // "tz"
QT_MOC_LITERAL(22, 122, 14), // "changeLocation"
QT_MOC_LITERAL(23, 137, 1), // "x"
QT_MOC_LITERAL(24, 139, 1) // "y"

    },
    "plate\0displayPath\0\0display\0getTh1\0"
    "getTh2\0getTh3\0getX\0getY\0getZ\0setTh1\0"
    "th1\0setTh2\0th2\0setTh3\0th3\0setZ\0z\0"
    "setTarget\0tx\0ty\0tz\0changeLocation\0x\0"
    "y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    0,   91,    2, 0x0a /* Public */,
      10,    1,   92,    2, 0x0a /* Public */,
      12,    1,   95,    2, 0x0a /* Public */,
      14,    1,   98,    2, 0x0a /* Public */,
      16,    1,  101,    2, 0x0a /* Public */,
      18,    3,  104,    2, 0x0a /* Public */,
      22,    3,  111,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   17,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   19,   20,   21,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   23,   24,   17,

       0        // eod
};

void plate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<plate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayPath(); break;
        case 1: _t->display(); break;
        case 2: { double _r = _t->getTh1();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 3: { double _r = _t->getTh2();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 4: { double _r = _t->getTh3();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 5: { double _r = _t->getX();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 6: { double _r = _t->getY();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 7: { double _r = _t->getZ();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->setTh1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->setTh2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setTh3((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setTarget((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 13: _t->changeLocation((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject plate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_plate.data,
    qt_meta_data_plate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *plate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_plate.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int plate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
