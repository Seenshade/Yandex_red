#include "stats.h"

HttpRequest ParseRequest(string_view line){
  HttpRequest req;
  size_t last_pos_space = 0;
  while (line.at(last_pos_space) == ' '){
    last_pos_space++;
  }
  line.remove_prefix(last_pos_space);
  auto first_sep = line.find(' ');
  req.method = line.substr(0, first_sep);
  line.remove_prefix(first_sep+1);
  auto second_sep = line.find(' ');
  req.uri = line.substr(0, second_sep);
  line.remove_prefix(second_sep+1);
  req.protocol = line.substr(0, line.npos);
  return req;
};

Stats::Stats()
: data_methods {"GET", "POST", "PUT", "DELETE", "UNKNOWN"},
  data_uri {"/", "/order", "/product", "/basket", "/help", "unknown"}
{
  for(const auto& item : data_methods){
    methods[string_view(item)];
  }
  for(const auto& item : data_uri){
    uris[string_view(item)];
  }
}

void Stats::AddMethod(string_view method) {
  if (method == "GET"){
    methods[data_methods.at(static_cast<size_t>(methods_enum::GET))]++;
  } else if (method == "POST"){
    methods[data_methods.at(static_cast<size_t>(methods_enum::POST))]++;
  } else if (method == "PUT"){
    methods[data_methods.at(static_cast<size_t>(methods_enum::PUT))]++;
  } else if (method == "DELETE"){
    methods[data_methods.at(static_cast<size_t>(methods_enum::DELETE))]++;
  } else {
    methods[data_methods.at(static_cast<size_t>(methods_enum::UNKNOWN))]++;
  }
}

void Stats::AddUri(string_view uri) {
  if (uri == "/"){
    uris[data_uri.at(static_cast<size_t>(uri_enum::main))]++;
  } else if (uri == "/order"){
    uris[data_uri.at(static_cast<size_t>(uri_enum::order))]++;
  } else if (uri == "/product"){
    uris[data_uri.at(static_cast<size_t>(uri_enum::product))]++;
  } else if (uri == "/basket"){
    uris[data_uri.at(static_cast<size_t>(uri_enum::basket))]++;
  } else if (uri == "/help"){
    uris[data_uri.at(static_cast<size_t>(uri_enum::help))]++;
  } else {
    uris[data_uri.at(static_cast<size_t>(uri_enum::unknown))]++;
  }
}

const map<string_view, int> & Stats::GetMethodStats() const {
  return methods;
}

const map<string_view, int> & Stats::GetUriStats() const {
  return uris;
}