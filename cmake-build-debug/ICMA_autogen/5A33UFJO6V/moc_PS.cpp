/****************************************************************************
** Meta object code from reading C++ file 'PS.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Widgets/photoShop/PS.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PS.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSPSENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSPSENDCLASS = QtMocHelpers::stringData(
    "PS",
    "doImageOpen",
    "",
    "showImgToUi",
    "std::pair<cv::Mat,MatInfo>",
    "showPixmap",
    "doUndo",
    "doReset",
    "doSizeChange",
    "doShowFaceTest",
    "doImageSave",
    "isSaveAs",
    "doToolBoxChanged",
    "index",
    "doCropChange",
    "row",
    "doResizeChange"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPSENDCLASS_t {
    uint offsetsAndSizes[34];
    char stringdata0[3];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[27];
    char stringdata5[11];
    char stringdata6[7];
    char stringdata7[8];
    char stringdata8[13];
    char stringdata9[15];
    char stringdata10[12];
    char stringdata11[9];
    char stringdata12[17];
    char stringdata13[6];
    char stringdata14[13];
    char stringdata15[4];
    char stringdata16[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPSENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPSENDCLASS_t qt_meta_stringdata_CLASSPSENDCLASS = {
    {
        QT_MOC_LITERAL(0, 2),  // "PS"
        QT_MOC_LITERAL(3, 11),  // "doImageOpen"
        QT_MOC_LITERAL(15, 0),  // ""
        QT_MOC_LITERAL(16, 11),  // "showImgToUi"
        QT_MOC_LITERAL(28, 26),  // "std::pair<cv::Mat,MatInfo>"
        QT_MOC_LITERAL(55, 10),  // "showPixmap"
        QT_MOC_LITERAL(66, 6),  // "doUndo"
        QT_MOC_LITERAL(73, 7),  // "doReset"
        QT_MOC_LITERAL(81, 12),  // "doSizeChange"
        QT_MOC_LITERAL(94, 14),  // "doShowFaceTest"
        QT_MOC_LITERAL(109, 11),  // "doImageSave"
        QT_MOC_LITERAL(121, 8),  // "isSaveAs"
        QT_MOC_LITERAL(130, 16),  // "doToolBoxChanged"
        QT_MOC_LITERAL(147, 5),  // "index"
        QT_MOC_LITERAL(153, 12),  // "doCropChange"
        QT_MOC_LITERAL(166, 3),  // "row"
        QT_MOC_LITERAL(170, 14)   // "doResizeChange"
    },
    "PS",
    "doImageOpen",
    "",
    "showImgToUi",
    "std::pair<cv::Mat,MatInfo>",
    "showPixmap",
    "doUndo",
    "doReset",
    "doSizeChange",
    "doShowFaceTest",
    "doImageSave",
    "isSaveAs",
    "doToolBoxChanged",
    "index",
    "doCropChange",
    "row",
    "doResizeChange"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPSENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    1,   75,    2, 0x08,    2 /* Private */,
       6,    0,   78,    2, 0x08,    4 /* Private */,
       7,    0,   79,    2, 0x08,    5 /* Private */,
       8,    0,   80,    2, 0x08,    6 /* Private */,
       9,    0,   81,    2, 0x08,    7 /* Private */,
      10,    1,   82,    2, 0x08,    8 /* Private */,
      12,    1,   85,    2, 0x08,   10 /* Private */,
      14,    1,   88,    2, 0x08,   12 /* Private */,
      16,    1,   91,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject PS::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSPSENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPSENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPSENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PS, std::true_type>,
        // method 'doImageOpen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showImgToUi'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPair<cv::Mat,MatInfo> &, std::false_type>,
        // method 'doUndo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doReset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doSizeChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doShowFaceTest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doImageSave'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'doToolBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'doCropChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'doResizeChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void PS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PS *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->doImageOpen(); break;
        case 1: _t->showImgToUi((*reinterpret_cast< std::add_pointer_t<std::pair<cv::Mat,MatInfo>>>(_a[1]))); break;
        case 2: _t->doUndo(); break;
        case 3: _t->doReset(); break;
        case 4: _t->doSizeChange(); break;
        case 5: _t->doShowFaceTest(); break;
        case 6: _t->doImageSave((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->doToolBoxChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->doCropChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->doResizeChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PS::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPSENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
