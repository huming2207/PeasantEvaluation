#include <stdio.h>
#include "weather.h"

int main()
{
    weather_result_t * weather;
    weather = get_weather_result(get_weather_json());
    printf("[INFO] Melbourne CBD, current temp: %d, pressure: %f, humidity: %d, status code: %d\n",
           weather->temp, weather->pressure, weather->humidity, weather->status_code);

    char * utc_time_str = malloc(50);
    char * local_time_str = malloc(50);
    struct tm local_time = *localtime(&weather->current_time);
    struct tm utc_time = *gmtime(&weather->current_time);


    strftime(utc_time_str, 50, "[INFO] UTC Time from API: %T %d/%h/%Y\n", &utc_time);
    strftime(local_time_str, 50, "[INFO] Local Time: %T %d/%h/%Y\n", &local_time);

    printf("%s", utc_time_str);
    printf("%s", local_time_str);

    // Cleanup and return
    free(weather);
    free(utc_time_str);
    free(local_time_str);
    return 0;
}

