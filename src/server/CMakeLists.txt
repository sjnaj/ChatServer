find_package(folly REQUIRED)
find_package(gflags REQUIRED)
find_package(glog REQUIRED)

aux_source_directory(. SRC_LIST)
add_executable(chatserver ${SRC_LIST})
message("${SRC_LIST}")
target_link_libraries(chatserver Folly::folly  muduo_net muduo_base mysqlclient pthread)