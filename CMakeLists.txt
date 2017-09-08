cmake_minimum_required(VERSION 3.8)
project(yahoo_weather_c)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lcurl")

set(SOURCE_FILES main.c weather.c weather.h config.h Parson/parson.c Parson/parson.h)
add_executable(yahoo_weather_c ${SOURCE_FILES})
target_link_libraries(yahoo_weather_c curl)