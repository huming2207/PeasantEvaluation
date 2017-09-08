//
// Created by Ming Hu on 6/9/17.
//

#ifndef YAHOO_WEATHER_C_CONFIG_H
#define YAHOO_WEATHER_C_CONFIG_H

#define YWEATHER_MAIN_API_ENDPOINT "https://query.yahooapis.com/v1/public/yql?q=select%20item.condition%2C%20yweather%3Aatmosphere%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22melbourne%2C%20victoria%22)%20and%20u%3D%27c%27&format=json"
//#define YWEATHER_DEBUG_CURL 1


#endif //YAHOO_WEATHER_C_CONFIG_H
