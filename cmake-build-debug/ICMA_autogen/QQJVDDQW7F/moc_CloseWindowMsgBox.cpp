/****************************************************************************
** Meta object code from reading C++ file 'CloseWindowMsgBox.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Utils/Tools/CloseWindowMsgBox.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CloseWindowMsgBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS = QtMocHelpers::stringData(
    "CloseWindowMsgBox",
    "okButtonClicked",
    "",
    "cancelButtonClicked",
    "trayRadioClicked",
    "directCloseRadioClicked",
    "checkBoxClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[18];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[17];
    char stringdata5[24];
    char stringdata6[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS_t qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS = {
    {
        QT_MOC_LITERAL(0, 17),  // "CloseWindowMsgBox"
        QT_MOC_LITERAL(18, 15),  // "okButtonClicked"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 19),  // "cancelButtonClicked"
        QT_MOC_LITERAL(55, 16),  // "trayRadioClicked"
        QT_MOC_LITERAL(72, 23),  // "directCloseRadioClicked"
        QT_MOC_LITERAL(96, 15)   // "checkBoxClicked"
    },
    "CloseWindowMsgBox",
    "okButtonClicked",
    "",
    "cancelButtonClicked",
    "trayRadioClicked",
    "directCloseRadioClicked",
    "checkBoxClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCloseWindowMsgBoxENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,
       3,    0,   45,    2, 0x06,    2 /* Public */,
       4,    0,   46,    2, 0x06,    3 /* Public */,
       5,    0,   47,    2, 0x06,    4 /* Public */,
       6,    1,   48,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject CloseWindowMsgBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCloseWindowMsgBoxENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CloseWindowMsgBox, std::true_type>,
        // method 'okButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cancelButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'trayRadioClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'directCloseRadioClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkBoxClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void CloseWindowMsgBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CloseWindowMsgBox *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->okButtonClicked(); break;
        case 1: _t->cancelButtonClicked(); break;
        case 2: _t->trayRadioClicked(); break;
        case 3: _t->directCloseRadioClicked(); break;
        case 4: _t->checkBoxClicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CloseWindowMsgBox::*)();
            if (_t _q_method = &CloseWindowMsgBox::okButtonClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CloseWindowMsgBox::*)();
            if (_t _q_method = &CloseWindowMsgBox::cancelButtonClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CloseWindowMsgBox::*)();
            if (_t _q_method = &CloseWindowMsgBox::trayRadioClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CloseWindowMsgBox::*)();
            if (_t _q_method = &CloseWindowMsgBox::directCloseRadioClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CloseWindowMsgBox::*)(bool );
            if (_t _q_method = &CloseWindowMsgBox::checkBoxClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *CloseWindowMsgBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CloseWindowMsgBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCloseWindowMsgBoxENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CloseWindowMsgBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CloseWindowMsgBox::okButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CloseWindowMsgBox::cancelButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CloseWindowMsgBox::trayRadioClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CloseWindowMsgBox::directCloseRadioClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CloseWindowMsgBox::checkBoxClicked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
