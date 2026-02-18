cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(SOURCES
    main.c
    DSnapshotMaker/DSnapshotMaker.c
    EntityLoader/EntLoader.c
    EntityUpdate/EntityUpdate.c
    SnapshotSender/SnapshotSender.c
    UserCmdReceiver/UserCmdReceiver.c
    MapLoader/MapLoader.c
    tools/dataArr.c
    tools/HashArray.c
)

add_executable(engine ${SOURCES})

target_include_directories(engine PRIVATE
    ${PROJECT_SOURCE_DIR}/DSnapshotMaker
    ${PROJECT_SOURCE_DIR}/EntityLoader
    ${PROJECT_SOURCE_DIR}/EntityUpdate
    ${PROJECT_SOURCE_DIR}/SnapshotSender
    ${PROJECT_SOURCE_DIR}/UserCmdReceiver
    ${PROJECT_SOURCE_DIR}/MapLoader
    ${PROJECT_SOURCE_DIR}/tools
)
