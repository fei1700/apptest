/****************************************************************************
** Meta object code from reading C++ file 'photoviewer.h'
**
** Created: Wed Mar 4 16:46:47 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "photoviewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'photoviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PhotoViewer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      24,   12,   12,   12, 0x0a,
      35,   12,   12,   12, 0x0a,
      50,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PhotoViewer[] = {
    "PhotoViewer\0\0showList()\0showFlow()\0"
    "showFileInfo()\0showImage()\0"
};

const QMetaObject PhotoViewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PhotoViewer,
      qt_meta_data_PhotoViewer, 0 }
};

const QMetaObject *PhotoViewer::metaObject() const
{
    return &staticMetaObject;
}

void *PhotoViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PhotoViewer))
        return static_cast<void*>(const_cast< PhotoViewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int PhotoViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showList(); break;
        case 1: showFlow(); break;
        case 2: showFileInfo(); break;
        case 3: showImage(); break;
        }
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_ImageWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      24,   12,   12,   12, 0x0a,
      35,   12,   12,   12, 0x0a,
      47,   12,   12,   12, 0x0a,
      59,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImageWidget[] = {
    "ImageWidget\0\0showNext()\0showPrev()\0"
    "showFScrn()\0slideshow()\0toolhide()\0"
};

const QMetaObject ImageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageWidget,
      qt_meta_data_ImageWidget, 0 }
};

const QMetaObject *ImageWidget::metaObject() const
{
    return &staticMetaObject;
}

void *ImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageWidget))
        return static_cast<void*>(const_cast< ImageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showNext(); break;
        case 1: showPrev(); break;
        case 2: showFScrn(); break;
        case 3: slideshow(); break;
        case 4: toolhide(); break;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_TreeshowWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_TreeshowWidget[] = {
    "TreeshowWidget\0"
};

const QMetaObject TreeshowWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TreeshowWidget,
      qt_meta_data_TreeshowWidget, 0 }
};

const QMetaObject *TreeshowWidget::metaObject() const
{
    return &staticMetaObject;
}

void *TreeshowWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeshowWidget))
        return static_cast<void*>(const_cast< TreeshowWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TreeshowWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
