include(_.cmake)
ae2f_CoreLibFetch(ae2f Inet main)

project(Bare)

configure_file(${PROJECT_SOURCE_DIR}/auto/Max.h ${PROJECT_SOURCE_DIR}/inc/Max.auto.h)
configure_file(${PROJECT_SOURCE_DIR}/auto/Dbg.h ${PROJECT_SOURCE_DIR}/inc/Dbg.auto.h)

file(GLOB incCore-src ${PROJECT_SOURCE_DIR}/inc/*)
file(GLOB incSvr-src ${PROJECT_SOURCE_DIR}/inc/Svr/*)
file(GLOB incCli-src ${PROJECT_SOURCE_DIR}/inc/Cli/*)

file(GLOB libSvr-src ${PROJECT_SOURCE_DIR}/src/Svr/*)
file(GLOB libCli-src ${PROJECT_SOURCE_DIR}/src/Cli/*)

add_library(incCore INTERFACE ${incCore-src})
target_include_directories(incCore  INTERFACE ${PROJECT_SOURCE_DIR}/inc)
target_link_libraries(incCore       INTERFACE Inet)

add_library(incSvr  INTERFACE ${incSvr-src})
add_library(incCli  INTERFACE ${incCli-src})

target_link_libraries(incSvr INTERFACE incCore)
target_link_libraries(incCli INTERFACE incCore)

target_compile_definitions(incSvr INTERFACE -DSERVER=1)
target_compile_definitions(incCli INTERFACE -DSERVER=0)

add_library(libSvr ${ae2f_LIBPREFIX} ${libSvr-src})
add_library(libCli ${ae2f_LIBPREFIX} ${libCli-src})

target_link_libraries(libCli PUBLIC incCli)
target_link_libraries(libSvr PUBLIC incSvr PUBLIC libCli)