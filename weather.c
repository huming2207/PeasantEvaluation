//
// Created by Ming Hu on 4/9/17.
//

#include "weather.h"

char * get_weather_json()
{
    // Curl string declaration
    curl_string str_buffer;
    str_buffer.memory = malloc(1);
    str_buffer.size = 0;

    // Curl declaration
    CURL * curl;
    CURLcode curl_response_code;

    // Curl init
    curl = curl_easy_init();

    // Detect if it successfully initialized
    if(curl == NULL)
    {
        printf("[ERROR] libcurl init failed!\n");
        exit(1);
    }

#ifdef YWEATHER_DEBUG_CURL

    // Set debug mode
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

#endif

    // Set Curl parameters
    // Set URL
    curl_easy_setopt(curl, CURLOPT_URL, YWEATHER_MAIN_API_ENDPOINT);

    // Set write function pointer (see libcurl's example)
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_response_to_string);

    // Write to string
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_buffer);

    // Perform request
    curl_response_code = curl_easy_perform(curl);

    if(curl_response_code != CURLE_OK)
    {
        fprintf(stderr, "[ERROR] CURL Perform failed, result is: %s", curl_easy_strerror(curl_response_code));

        // Clean up curl instance
        curl_easy_cleanup(curl);
        free(str_buffer.memory);
        curl_global_cleanup();

        return NULL;
    }
    else
    {
        printf("[INFO] API data fetch successful\n");

        // Declare a new string and copy it from curl string buffer
        char * return_str = malloc(str_buffer.size);
        strcpy(return_str, str_buffer.memory);

        // Clean up curl instance
        curl_easy_cleanup(curl);
        free(str_buffer.memory);
        curl_global_cleanup();

        return return_str;
    }

}

weather_result_t * get_weather_result(char * weather_str)
{
    // Declare weather result
    weather_result_t * weather_result = malloc(sizeof(weather_result_t));
    struct tm * utc_time_struct = malloc(sizeof(struct tm));

    // Parse JSON
    JSON_Value * weather_value = json_parse_string(weather_str);
    JSON_Object * weather_root = json_value_get_object(weather_value);

    weather_result->humidity = (uint8_t)strtol(
            json_object_dotget_string(weather_root, "query.results.channel.atmosphere.humidity") , NULL, 10);

    weather_result->status_code = (uint16_t)strtol(
            json_object_dotget_string(weather_root, "query.results.channel.item.condition.code") , NULL, 10);

    weather_result->temp = (uint8_t)strtol(
            json_object_dotget_string(weather_root, "query.results.channel.item.condition.temp") , NULL, 10);

    weather_result->pressure = strtof(
            json_object_dotget_string(weather_root, "query.results.channel.atmosphere.pressure"), NULL);

    // Parse time to string first then covert to time struct
    strptime(json_object_dotget_string(weather_root, "query.created"), "%FT%T%z", utc_time_struct);

    // Force set to UTC first in order to let it understand it's a damn UTC time source...
    char * tz_env = getenv("TZ");
    setenv("TZ", "UTC", 1);
    weather_result->current_time = mktime(utc_time_struct);
    tz_env == NULL ? unsetenv("TZ") : setenv("TZ", tz_env, 1);

    // Clean up and return
    free(utc_time_struct);
    json_value_free(weather_value);
    return weather_result;

}

static size_t save_response_to_string(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    curl_string *mem = (curl_string*)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL)
    {
        /* out of memory! */
        fprintf(stderr, "[ERROR] Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

