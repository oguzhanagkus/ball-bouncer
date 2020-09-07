/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../server-app/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[351];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "on_button2d_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "on_button3d_clicked"
QT_MOC_LITERAL(4, 52, 20), // "on_button23d_clicked"
QT_MOC_LITERAL(5, 73, 25), // "on_balance_button_clicked"
QT_MOC_LITERAL(6, 99, 24), // "on_circle_button_clicked"
QT_MOC_LITERAL(7, 124, 22), // "on_stop_button_clicked"
QT_MOC_LITERAL(8, 147, 12), // "sendDatagram"
QT_MOC_LITERAL(9, 160, 24), // "dataFromImageProcesssing"
QT_MOC_LITERAL(10, 185, 17), // "changeAngleRobot1"
QT_MOC_LITERAL(11, 203, 17), // "changeAngleRobot2"
QT_MOC_LITERAL(12, 221, 17), // "changeAngleRobot3"
QT_MOC_LITERAL(13, 239, 17), // "changeAngleRobot4"
QT_MOC_LITERAL(14, 257, 13), // "giveArmsAngle"
QT_MOC_LITERAL(15, 271, 11), // "degree_arm1"
QT_MOC_LITERAL(16, 283, 11), // "degree_arm2"
QT_MOC_LITERAL(17, 295, 11), // "degree_arm3"
QT_MOC_LITERAL(18, 307, 11), // "degree_arm4"
QT_MOC_LITERAL(19, 319, 22), // "changeBallsCoordinates"
QT_MOC_LITERAL(20, 342, 1), // "x"
QT_MOC_LITERAL(21, 344, 1), // "y"
QT_MOC_LITERAL(22, 346, 1), // "z"
QT_MOC_LITERAL(23, 348, 2) // "go"

    },
    "MainWindow\0on_button2d_clicked\0\0"
    "on_button3d_clicked\0on_button23d_clicked\0"
    "on_balance_button_clicked\0"
    "on_circle_button_clicked\0"
    "on_stop_button_clicked\0sendDatagram\0"
    "dataFromImageProcesssing\0changeAngleRobot1\0"
    "changeAngleRobot2\0changeAngleRobot3\0"
    "changeAngleRobot4\0giveArmsAngle\0"
    "degree_arm1\0degree_arm2\0degree_arm3\0"
    "degree_arm4\0changeBallsCoordinates\0x\0"
    "y\0z\0go"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    4,  101,    2, 0x08 /* Private */,
      19,    3,  110,    2, 0x08 /* Private */,
      23,    0,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   15,   16,   17,   18,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   20,   21,   22,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_button2d_clicked(); break;
        case 1: _t->on_button3d_clicked(); break;
        case 2: _t->on_button23d_clicked(); break;
        case 3: _t->on_balance_button_clicked(); break;
        case 4: _t->on_circle_button_clicked(); break;
        case 5: _t->on_stop_button_clicked(); break;
        case 6: _t->sendDatagram(); break;
        case 7: _t->dataFromImageProcesssing(); break;
        case 8: _t->changeAngleRobot1(); break;
        case 9: _t->changeAngleRobot2(); break;
        case 10: _t->changeAngleRobot3(); break;
        case 11: _t->changeAngleRobot4(); break;
        case 12: _t->giveArmsAngle((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 13: _t->changeBallsCoordinates((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 14: _t->go(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
