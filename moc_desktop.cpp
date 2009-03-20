/****************************************************************************
** Meta object code from reading C++ file 'desktop.h'
**
** Created: Wed Mar 4 16:46:35 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "desktop.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'desktop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Desktop[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      21,    8,    8,    8, 0x08,
      33,    8,    8,    8, 0x08,
      45,    8,    8,    8, 0x08,
      59,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Desktop[] = {
    "Desktop\0\0gotoPhoto()\0gotoMusic()\0"
    "gotoVideo()\0gotoSetting()\0createMusic()\0"
};

const QMetaObject Desktop::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_Desktop,
      qt_meta_data_Desktop, 0 }
};

const QMetaObject *Desktop::metaObject() const
{
    return &staticMetaObject;
}

void *Desktop::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Desktop))
        return static_cast<void*>(const_cast< Desktop*>(this));
    return QFrame::qt_metacast(_clname);
}

int Desktop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: gotoPhoto(); break;
        case 1: gotoMusic(); break;
        case 2: gotoVideo(); break;
        case 3: gotoSetting(); break;
        case 4: createMusic(); break;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_MyLaunch[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyLaunch[] = {
    "MyLaunch\0\0launchDesktop()\0"
};

const QMetaObject MyLaunch::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyLaunch,
      qt_meta_data_MyLaunch, 0 }
};

const QMetaObject *MyLaunch::metaObject() const
{
    return &staticMetaObject;
}

void *MyLaunch::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyLaunch))
        return static_cast<void*>(const_cast< MyLaunch*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyLaunch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: launchDesktop(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
