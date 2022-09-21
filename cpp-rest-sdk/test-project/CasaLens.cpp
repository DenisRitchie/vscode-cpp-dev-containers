#include "CasaLens.hpp"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

const utility::string_t CasaLensCredentials::events_url = U("http://api.eventful.com/json/events/search?...&location=");
const utility::string_t CasaLensCredentials::movies_url = U("http://data.tmsapi.com/v1/movies/showings?");
const utility::string_t CasaLensCredentials::images_url = U("https://api.datamarket.azure.com/Bing/Search/Image?$format=json");
const utility::string_t CasaLensCredentials::bmaps_url = U("http://dev.virtualearth.net/REST/v1/Locations");
const utility::string_t CasaLensCredentials::gmaps_url = U("http://maps.googleapis.com/maps/api/geocode/json");
const utility::string_t CasaLensCredentials::weather_url = U("http://api.openweathermap.org/data/2.1/find/name?q=");

// FILL IN THE API KEYS FOR THE DIFFERENT SERVICES HERE.
// Refer Readme.txt for details on how to obtain the key for the services.
const utility::string_t CasaLensCredentials::events_keyname = U("app_key");
const utility::string_t CasaLensCredentials::events_key;
const utility::string_t CasaLensCredentials::movies_keyname = U("api_key");
const utility::string_t CasaLensCredentials::movies_key;
const utility::string_t CasaLensCredentials::images_keyname = U("username");
const utility::string_t CasaLensCredentials::images_key;
const utility::string_t CasaLensCredentials::bmaps_keyname = U("key");
const utility::string_t CasaLensCredentials::bmaps_key;

const utility::string_t CasaLens::events_json_key = U("events");
const utility::string_t CasaLens::movies_json_key = U("movies");
const utility::string_t CasaLens::weather_json_key = U("weather");
const utility::string_t CasaLens::images_json_key = U("images");
const utility::string_t CasaLens::error_json_key = U("error");

void HttpRequestLog(http_request &message)
{
  fprintf(stdout, "Method: %s, Url: %s, Path: %s\n",
          message.method().c_str(),
          message.relative_uri().to_string().c_str(),
          message.relative_uri().path().c_str());
}

CasaLens::CasaLens(utility::string_t url) : m_listener(url)
{
  m_listener.support(methods::GET, std::bind(&CasaLens::handle_get, this, std::placeholders::_1));
  m_listener.support(methods::POST, std::bind(&CasaLens::handle_post, this, std::placeholders::_1));

  m_htmlcontentmap[U("/")] = std::make_tuple(U("assets/AppCode.html"), U("text/html"));
  m_htmlcontentmap[U("/js/default.js")] = std::make_tuple(U("assets/js/default.js"), U("application/javascript"));
  m_htmlcontentmap[U("/css/default.css")] = std::make_tuple(U("assets/css/default.css"), U("text/css"));
  m_htmlcontentmap[U("/images/logo.png")] = std::make_tuple(U("assets/images/logo.png"), U("application/octet-stream"));
  m_htmlcontentmap[U("/images/bing-logo.jpg")] = std::make_tuple(U("assets/images/bing-logo.jpg"), U("application/octet-stream"));
  m_htmlcontentmap[U("/images/wall.jpg")] = std::make_tuple(U("assets/images/wall.jpg"), U("application/octet-stream"));
}

void CasaLens::handle_error(pplx::task<void> &t)
{
  try
  {
    t.get();
  }
  catch (...)
  {
    // Ignore the error, Log it if a logger is available
  }
}

pplx::task<void> CasaLens::open()
{
  return m_listener.open().then([](pplx::task<void> t)
                                { handle_error(t); });
}

pplx::task<void> CasaLens::close()
{
  return m_listener.close().then([](pplx::task<void> t)
                                 { handle_error(t); });
}

// Handler to process HTTP::GET requests.
// Replies to the request with data.
void CasaLens::handle_get(http_request message)
{
  auto path = message.relative_uri().path();
  auto content_data = m_htmlcontentmap.find(path);

  HttpRequestLog(message);

  if (content_data == m_htmlcontentmap.end())
  {
    message.reply(status_codes::NotFound, U("Path not found")).then([](pplx::task<void> t)
                                                                    { handle_error(t); });
    return;
  }

  auto file_name = std::get<0>(content_data->second);
  auto content_type = std::get<1>(content_data->second);

  concurrency::streams::fstream::open_istream(file_name, std::ios::in)
      .then([=](concurrency::streams::istream is)
            { message.reply(status_codes::OK, is, content_type).then([](pplx::task<void> t)
                                                                     { handle_error(t); }); })
      .then([=](pplx::task<void> t)
            {
            try
            {
                t.get();
            }
            catch (...)
            {
                // opening the file (open_istream) failed.
                // Reply with an error.
                message.reply(status_codes::InternalError).then([](pplx::task<void> t) { handle_error(t); });
            } });
}

// Respond to HTTP::POST messages
// Post data will contain the postal code or location string.
// Aggregate location data from different services and reply to the POST request.
void CasaLens::handle_post(http_request message)
{
  auto path = message.relative_uri().path();

  HttpRequestLog(message);

  if (0 == path.compare(U("/")))
  {
    message.extract_string()
        .then([&](const utility::string_t &location)
              { get_data(message, location); })
        .then([](pplx::task<void> t)
              { handle_error(t); });
  }
  else
  {
    message.reply(status_codes::NotFound, U("Path not found")).then([](pplx::task<void> t)
                                                                    { handle_error(t); });
  }
}
