/****************************************************************************
** Meta object code from reading C++ file 'musicplayer.h'
**
** Created: Wed Mar 4 16:46:41 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "musicplayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MusicPlayer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      26,   12,   12,   12, 0x0a,
      40,   12,   12,   12, 0x0a,
      51,   12,   12,   12, 0x0a,
      62,   12,   12,   12, 0x0a,
      75,   12,   12,   12, 0x0a,
      92,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MusicPlayer[] = {
    "MusicPlayer\0\0playToggle()\0setProgress()\0"
    "playNext()\0playPrev()\0playRotate()\0"
    "setposition(int)\0ossSetVolume(int)\0"
};

const QMetaObject MusicPlayer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicPlayer,
      qt_meta_data_MusicPlayer, 0 }
};

const QMetaObject *MusicPlayer::metaObject() const
{
    return &staticMetaObject;
}

void *MusicPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlayer))
        return static_cast<void*>(const_cast< MusicPlayer*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playToggle(); break;
        case 1: setProgress(); break;
        case 2: playNext(); break;
        case 3: playPrev(); break;
        case 4: playRotate(); break;
        case 5: setposition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: ossSetVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
