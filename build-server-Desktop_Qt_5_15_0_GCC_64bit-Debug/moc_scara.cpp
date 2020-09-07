/****************************************************************************
** Meta object code from reading C++ file 'scara.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../server-app/scara.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scara.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Scara_t {
    QByteArrayData data[33];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Scara_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Scara_t qt_meta_stringdata_Scara = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Scara"
QT_MOC_LITERAL(1, 6, 2), // "go"
QT_MOC_LITERAL(2, 9, 0), // ""
QT_MOC_LITERAL(3, 10, 2), // "dt"
QT_MOC_LITERAL(4, 13, 11), // "displayPath"
QT_MOC_LITERAL(5, 25, 7), // "display"
QT_MOC_LITERAL(6, 33, 6), // "getTh1"
QT_MOC_LITERAL(7, 40, 6), // "getTh2"
QT_MOC_LITERAL(8, 47, 6), // "getTh3"
QT_MOC_LITERAL(9, 54, 4), // "getX"
QT_MOC_LITERAL(10, 59, 4), // "getY"
QT_MOC_LITERAL(11, 64, 4), // "getZ"
QT_MOC_LITERAL(12, 69, 6), // "setTh1"
QT_MOC_LITERAL(13, 76, 3), // "th1"
QT_MOC_LITERAL(14, 80, 6), // "setTh2"
QT_MOC_LITERAL(15, 87, 3), // "th2"
QT_MOC_LITERAL(16, 91, 6), // "setTh3"
QT_MOC_LITERAL(17, 98, 3), // "th3"
QT_MOC_LITERAL(18, 102, 4), // "setZ"
QT_MOC_LITERAL(19, 107, 1), // "z"
QT_MOC_LITERAL(20, 109, 7), // "setMode"
QT_MOC_LITERAL(21, 117, 12), // "SteeringMode"
QT_MOC_LITERAL(22, 130, 4), // "mode"
QT_MOC_LITERAL(23, 135, 9), // "setTarget"
QT_MOC_LITERAL(24, 145, 2), // "tx"
QT_MOC_LITERAL(25, 148, 2), // "ty"
QT_MOC_LITERAL(26, 151, 2), // "tz"
QT_MOC_LITERAL(27, 154, 5), // "kinPr"
QT_MOC_LITERAL(28, 160, 7), // "kinOdwr"
QT_MOC_LITERAL(29, 168, 9), // "calcSpeed"
QT_MOC_LITERAL(30, 178, 2), // "vx"
QT_MOC_LITERAL(31, 181, 2), // "vy"
QT_MOC_LITERAL(32, 184, 2) // "vz"

    },
    "Scara\0go\0\0dt\0displayPath\0display\0"
    "getTh1\0getTh2\0getTh3\0getX\0getY\0getZ\0"
    "setTh1\0th1\0setTh2\0th2\0setTh3\0th3\0setZ\0"
    "z\0setMode\0SteeringMode\0mode\0setTarget\0"
    "tx\0ty\0tz\0kinPr\0kinOdwr\0calcSpeed\0vx\0"
    "vy\0vz"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scara[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x0a /* Public */,
       4,    0,  107,    2, 0x0a /* Public */,
       5,    0,  108,    2, 0x0a /* Public */,
       6,    0,  109,    2, 0x0a /* Public */,
       7,    0,  110,    2, 0x0a /* Public */,
       8,    0,  111,    2, 0x0a /* Public */,
       9,    0,  112,    2, 0x0a /* Public */,
      10,    0,  113,    2, 0x0a /* Public */,
      11,    0,  114,    2, 0x0a /* Public */,
      12,    1,  115,    2, 0x0a /* Public */,
      14,    1,  118,    2, 0x0a /* Public */,
      16,    1,  121,    2, 0x0a /* Public */,
      18,    1,  124,    2, 0x0a /* Public */,
      20,    1,  127,    2, 0x0a /* Public */,
      23,    3,  130,    2, 0x0a /* Public */,
      27,    0,  137,    2, 0x08 /* Private */,
      28,    0,  138,    2, 0x08 /* Private */,
      29,    3,  139,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   17,
    QMetaType::Void, QMetaType::Double,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   24,   25,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Double, QMetaType::Double, QMetaType::Double,   30,   31,   32,

       0        // eod
};

void Scara::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Scara *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->go((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->displayPath(); break;
        case 2: _t->display(); break;
        case 3: { double _r = _t->getTh1();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 4: { double _r = _t->getTh2();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 5: { double _r = _t->getTh3();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 6: { double _r = _t->getX();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 7: { double _r = _t->getY();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 8: { double _r = _t->getZ();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setTh1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setTh2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setTh3((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setMode((*reinterpret_cast< SteeringMode(*)>(_a[1]))); break;
        case 14: _t->setTarget((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 15: _t->kinPr(); break;
        case 16: _t->kinOdwr(); break;
        case 17: { bool _r = _t->calcSpeed((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Scara::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Scara.data,
    qt_meta_data_Scara,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Scara::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scara::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Scara.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Scara::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
