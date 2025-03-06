cmake_minimum_required(VERSION 3.10)

# Set the project name
project(absubmoduleUser)

# so modules/a/A.cpp is required here to access A.cpp, otherwise it doesn't see it.
# this is what the library.json file fixes.
add_executable(absubmoduleUser main.cpp) #modules/a/A.cpp)
