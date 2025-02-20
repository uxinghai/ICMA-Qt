cmake_minimum_required(VERSION 3.16)

project(ICMA VERSION 0.1 LANGUAGES CXX)

# 启用 Qt 的自动处理功能
set(CMAKE_AUTOMOC ON) # 自动处理 MOC 文件
set(CMAKE_AUTOUIC ON) # 自动处理 UIC 文件
set(CMAKE_AUTORCC ON) # 自动处理资源文件（如 .qrc）

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置应用程序图标
if (WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/logo128.ico")
endif ()

# 尝试查找 Qt6 或 Qt5
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets
        Multimedia MultimediaWidgets Sql Concurrent Network)
# 提取实际找到的 Qt 版本
set(QT_VERSION_MAJOR ${QT_VERSION_MAJOR})
# 根据找到的 Qt 版本配置组件
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets
        Multimedia MultimediaWidgets Sql Concurrent Network)


# 配置 OpenCV
set(OpenCV_DIR "D:/A-Develop/ToolLibrary/OpenCV/opencv-build/install")
find_package(OpenCV REQUIRED)

#                                            *********
#                                             *******
#                                              *****
#                                               ***
#                                                *
#                                            收集所有文件
set(PROJECT_SOURCES
        main.cpp
        icmaStart.h
        # widgets下所有文件
        src/Widgets/mainWindow/MainWindow.cpp
        src/Widgets/mainWindow/MainWindow.h
        src/Widgets/photoShop/PS.cpp
        src/Widgets/photoShop/PS.h
        src/Widgets/photoShop/faceTest/FaceTest.cpp
        src/Widgets/photoShop/faceTest/FaceTest.h
        src/Widgets/fileTransfer/FileTransfer.cpp
        src/Widgets/fileTransfer/FileTransfer.h
        src/Widgets/fileTransfer/FileTransTool.h
        src/Widgets/fileTransfer/client/AClient.h
        src/Widgets/fileTransfer/client/AClient.cpp
        src/Widgets/fileTransfer/server/AServer.h
        src/Widgets/fileTransfer/server/AServer.cpp
        src/Widgets/mainWindow/FileManage/FileManage.cpp
        src/Widgets/mainWindow/FileManage/FileManage.h
        src/Widgets/photoShop/ShareSrc.h
        src/Utils/BoostClass/MyGraphicsView.h
        src/Widgets/photoShop/faceTest/ToGetToken.h
        src/Widgets/photoShop/PSTools/Rota.h
        src/Widgets/photoShop/PSTools/Filter.h
        src/Widgets/photoShop/ImgCropper/Cropper.cpp
        src/Widgets/photoShop/ImgCropper/Cropper.h
        src/Widgets/photoShop/ImgCropper/CropperDialog/CustomCropperDialog.cpp
        src/Widgets/photoShop/ImgCropper/CropperDialog/CustomCropperDialog.h
        src/Widgets/photoShop/ImgCropper/CropperDialog/SimpleCropperDialog.h
        src/Widgets/photoShop/ImgCropper/Tool/ImageCropperLabel.cpp
        src/Widgets/photoShop/ImgCropper/Tool/ImageCropperLabel.h
        src/Widgets/photoShop/PSTools/Resize.h
        src/Widgets/photoShop/PSTools/Adjust.h
        src/Widgets/photoShop/PSTools/Crop.h
        # utils下所有文件
        src/Utils/Tools/closeWindowMsgBox.h
        src/Utils/Tools/MovableFramelessWindow.h
        src/Utils/Tools/NetworkTool.h
        src/Utils/threadWorkers/ThreadImageToBase64.h
        src/Network/GetICMABrief.h
        src/Utils/Tools/SystemTrayIcon.h
        src/Utils/Tools/LoadingGif.h
        src/Utils/Tools/TipLabel.h
        src/Utils/Tools/MyAutoStack.h
        src/Utils/Tools/ImageToBase64.h
        src/Utils/Tools/MyInformationBox.h
        src/Utils/BoostClass/NoWheelSlider.h
        src/Utils/Tools/LogOut.h
        # network下所有文件
        src/manager/JsonManager.h
        src/Network/GetBaiduToken.h
        src/manager/NetworkManager.h
        src/manager/NetworkManager.cpp
        # initial下所有文件
        src/initial/AppInit.h
        src/initial/AppInit.cpp
        src/initial/SplashScreen.h
        # dataBase下所有文件
        src/manager/SqlManager.h
        src/Utils/ThreadWorkers/File/FilesDBWorker.h
        src/manager/Config/iniManager.h
        src/Utils/ThreadWorkers/File/FilesDBWorker.cpp
        src/DataBase/SqlQuery/Directory.h
        src/DataBase/SqlQuery/Files.h
        src/DataBase/SqlQuery/SqlQueryHelper.h
        src/Network/AIDoFaceDetect.h
        # UI
        UI/MainWindow.ui
        UI/PS.ui
        UI/FileTransfer.ui
        UI/AClient.ui
        UI/AServer.ui
        UI/FaceTest.ui
        UI/SimpleCrop.ui
        UI/CustomCrop.ui
        src/Widgets/fileTransfer/ShareSrc.h
        src/Widgets/fileDeduplicate/FileDeduplicate.h
        src/Widgets/fileDeduplicate/FileDeduplicate.cpp
        src/Utils/Tools/DataUnitCalc.h
        src/Utils/Tools/MyQueryModel.h
        src/Utils/BoostClass/MyTableView.h
        src/Utils/Tools/IconTextDelegate.h
)

#                                            *********
#                                             *******
#                                              *****
#                                               ***
#                                                *
#                                       依据 QT 版本， 使用不同方式
if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ICMA
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            Resource.qrc
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET ICMA APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(ICMA SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(ICMA
                ${PROJECT_SOURCES}
        )
    endif ()
endif ()


target_link_libraries(ICMA PRIVATE ${OpenCV_LIBS} # 添加openCv lib库
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Multimedia
        Qt${QT_VERSION_MAJOR}::MultimediaWidgets
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::Concurrent
)


target_include_directories(ICMA PRIVATE ${OpenCV_INCLUDE_DIRS} # 添加openCv include路径
        ${CMAKE_BINARY_DIR} # 添加自动生成文件的路径
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ICMA)
endif ()
set_target_properties(ICMA PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ICMA
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ICMA)
endif ()
