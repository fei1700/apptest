/****************************************************************************
** Meta object code from reading C++ file 'pictureflow.h'
**
** Created: Wed Mar 4 16:46:53 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pictureflow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pictureflow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PictureFlow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       4,   50, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x05,
      38,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   13,   12,   12, 0x0a,
      75,   12,   12,   12, 0x0a,
      83,   12,   12,   12, 0x0a,
      92,   12,   12,   12, 0x0a,
     107,   12,   12,   12, 0x0a,
     118,   13,   12,   12, 0x0a,

 // properties: name, type, flags
     137,  133, 0x02095103,
     148,  133, 0x02095103,
     167,  161, 0x15095103,
     177,  133, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_PictureFlow[] = {
    "PictureFlow\0\0index\0itemActivated(int)\0"
    "inputReceived()\0setCurrentSlide(int)\0"
    "clear()\0render()\0showPrevious()\0"
    "showNext()\0showSlide(int)\0int\0slideCount\0"
    "currentSlide\0QSize\0slideSize\0zoomFactor\0"
};

const QMetaObject PictureFlow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PictureFlow,
      qt_meta_data_PictureFlow, 0 }
};

const QMetaObject *PictureFlow::metaObject() const
{
    return &staticMetaObject;
}

void *PictureFlow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PictureFlow))
        return static_cast<void*>(const_cast< PictureFlow*>(this));
    return QWidget::qt_metacast(_clname);
}

int PictureFlow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: inputReceived(); break;
        case 2: setCurrentSlide((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: clear(); break;
        case 4: render(); break;
        case 5: showPrevious(); break;
        case 6: showNext(); break;
        case 7: showSlide((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = slideCount(); break;
        case 1: *reinterpret_cast< int*>(_v) = currentSlide(); break;
        case 2: *reinterpret_cast< QSize*>(_v) = slideSize(); break;
        case 3: *reinterpret_cast< int*>(_v) = zoomFactor(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSlideCount(*reinterpret_cast< int*>(_v)); break;
        case 1: setCurrentSlide(*reinterpret_cast< int*>(_v)); break;
        case 2: setSlideSize(*reinterpret_cast< QSize*>(_v)); break;
        case 3: setZoomFactor(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PictureFlow::itemActivated(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PictureFlow::inputReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
