cmake_minimum_required(VERSION 3.8)
project(yahoo_weather_c)

set(CMAKE_C_STANDARD 11)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_C_FLAGS "-pedantic -Wall -Wno-unused-function")
else()
    set(CMAKE_C_FLAGS "-pedantic -Wall -lcurl -Wno-unused-function")
endif()

set(SOURCE_FILES main.c weather.c weather.h config.h Parson/parson.c Parson/parson.h)
add_executable(yahoo_weather_c ${SOURCE_FILES})
target_link_libraries(yahoo_weather_c curl)