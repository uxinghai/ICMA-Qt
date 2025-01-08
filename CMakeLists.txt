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
        # widgets下所有文件
        src/Widgets/mainWindow/MainWindow.cpp
        src/Widgets/mainWindow/MainWindow.h
        UI/MainWindow.ui
        src/Widgets/photoShop/PS.cpp
        src/Widgets/photoShop/PS.h
        UI/PS.ui
        src/Widgets/faceTest/FaceTest.cpp
        src/Widgets/faceTest/FaceTest.h
        UI/FaceTest.ui
        src/Widgets/fileTransfer/FileTransfer.cpp
        src/Widgets/fileTransfer/FileTransfer.h
        src/Widgets/fileTransfer/FileTransTool.h
        UI/FileTransfer.ui
        # utils下所有文件
        src/manager/Config/JsonManager.h
        src/utils/log/LogOut.h
        src/utils/threadWorkers/GetTokenWorker.h
        src/utils/threadWorkers/GetTokenWorker.cpp
        src/utils/threadWorkers/ToBase64Worker.h
        src/utils/threadWorkers/ToBase64Worker.cpp
        # network下所有文件
        src/Widgets/fileTransfer/client/AClient.h
        src/Widgets/fileTransfer/client/AClient.cpp
        UI/AClient.ui
        src/Widgets/fileTransfer/server/AServer.h
        src/Widgets/fileTransfer/server/AServer.cpp
        UI/AServer.ui
        src/manager/NetworkManager.h
        src/manager/NetworkManager.cpp
        # initial下所有文件
        src/initial/AppInit.h
        src/initial/AppInit.cpp
        src/initial/SplashScreen.h
        # dataBase下所有文件
        src/manager/SqlManager.h
        src/dataBase/worker/FilesDBWorker.h
        # Controls
        src/controls/graphics/MyGraphicsView.h
        src/controls/graphics/MyGraphicsItem.h
        src/manager/Config/iniManager.h
        src/Utils/Tools/closeWindowMsgBox.h
        src/Utils/Tools/MovableFramelessWindow.h
        src/Controls/Network/NetworkTool.h
        src/Controls/Network/GetICMABrief.h
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
            UI/FaceTest.ui
            UI/FileTransfer.ui
            UI/PS.ui
            UI/MainWindow.ui
            UI/FileTransfer.ui
            Resource.qrc # 添加资源文件
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
