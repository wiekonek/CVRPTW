project(cvrptw)

add_executable(cvrptw functions.cpp instance.cpp main.cpp)

install(TARGETS cvrptw RUNTIME DESTINATION bin)
