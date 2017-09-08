//
// Created by Ming Hu on 4/9/17.
//

#ifndef YAHOO_WEATHER_C_UTIL_H
#define YAHOO_WEATHER_C_UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include "Parson/parson.h"
#include "config.h"

typedef struct weather_struct
{
    int8_t temp;
    uint16_t status_code;
    uint8_t humidity;
    float pressure;
    time_t current_time;
} weather_result_t;

typedef struct _curl_str
{
    char *memory;
    size_t size;
} curl_string;

typedef struct _curl_result
{
    char * string;
    uint16_t response_time;
} curl_result;

char * get_weather_json();

static size_t save_response_to_string(void *contents, size_t size, size_t nmemb, void *userp);

weather_result_t * get_weather_result(char * weather_str);

#endif //YAHOO_WEATHER_C_UTIL_H
