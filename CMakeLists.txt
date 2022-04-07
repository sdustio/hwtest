cmake_minimum_required(VERSION 3.5)
project(driver_test VERSION 1.0.0)

### C
set(CMAKE_C_STANDARD 11)
### CXX
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/source-charset:utf-8)
endif()


# find dependencies
find_package(serial REQUIRED)
find_package(sdquadx REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  src/spi.cc
  src/main.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} sdquadx::sdquadx serial::serial)

set_target_properties(${PROJECT_NAME} PROPERTIES
  INSTALL_RPATH_USE_LINK_PATH ON
)
