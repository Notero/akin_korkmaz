cmake_minimum_required(VERSION 3.16)

project(xrpl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Quick WebSockets Sql)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appxrpl
    src/app/main.cpp
    src/app/Backend.cpp
    src/app/Backend.h
    src/storage/walletconfig.cpp
    src/storage/walletconfig.h
    src/networking/RippledCommands.cpp
    src/networking/RippledCommands.h
    src/networking/QWebSocketClient.cpp
    src/networking/QWebSocketClient.h
    src/networking/XrplJsonParser.h
    src/networking/XrplJsonParser.cpp
    src/arbitrage/ArbitrageTypes.h
    src/networking/XrplWebSocketClient.h
    src/networking/XrplWebSocketClient.cpp
    src/storage/DbRepository.h
    src/storage/DbRepository.cpp
    src/arbitrage/ArbitrageEngine.h
    src/arbitrage/ArbitrageEngine.cpp
    src/arbitrage/TraderBot.h
    src/arbitrage/TraderBot.cpp
    src/arbitrage/mathematics.cpp
    src/arbitrage/mathematics.h
    src/networking/websocketclient.cpp
    src/networking/websocketclient.h
)

qt_add_qml_module(appxrpl
    URI xrpl
    QML_FILES
        qml/Main.qml
        qml/MainView.qml
        qml/Wallet.qml
)

set_target_properties(appxrpl PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appxrpl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arbitrage
    ${CMAKE_CURRENT_SOURCE_DIR}/src/networking
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storage
)

target_link_libraries(appxrpl
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::WebSockets
    Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appxrpl
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
