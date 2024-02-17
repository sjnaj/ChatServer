
# message("${PROJECT_SOURCE_DIR}")
set(SRC_LIST ./testmuduo.cpp)

add_executable(testmuduo ${SRC_LIST})
target_link_libraries(testmuduo muduo_net muduo_base pthread)


