project(cvrptw)

add_executable(cvrptw instance.cpp main.cpp)

install(TARGETS cvrptw RUNTIME DESTINATION bin)
