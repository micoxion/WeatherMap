#include "pch.h"
#include<iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace std;
using namespace utility; // Common utilities like string conversions
using namespace web; // Common features like URIs.
using namespace web::http; // Common HTTP functionality
using namespace web::http::client; // HTTP client features
using namespace concurrency::streams;
using std::string;
void main() {
	http_client client(U("http://api.openweathermap.org"));
	uri_builder builder(U("/data/2.5/forecast"));
	builder.append_query(U("zip"), U("72143"));
	builder.append_query(U("appid"), U("f6a2662f931aa3d354df68e6b4864c37"));
	builder.append_query(U("units"), U("imperial"));
	builder.append_query(U("mode"), U("json"));
	http_response response = client.request(methods::GET, builder.to_string()).get();
	web::json::value forecastJson = response.extract_json(true).get();
	web::json::value forecastListJson = forecastJson.at(U("list"));
	if (forecastListJson.is_array()) {
		for (int i = 0; i < forecastListJson.size(); i++)
		{
			web::json::value forecastDayJson = forecastListJson[i];
			web::json::value mainJson = forecastDayJson.at(U("main"));
			web::json::value tempJson = mainJson.at(U("temp"));
			cout << tempJson.as_double() << endl;
			web::json::value weatherJson = forecastDayJson.at(U("weather"))[0];
			web::json::value mainWeatherJson = weatherJson.at(U("main"));
			cout << conversions::to_utf8string(mainWeatherJson.as_string()) << endl;
		}
	}
}
