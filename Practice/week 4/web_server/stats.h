#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

enum class methods_enum{
  GET,
  POST,
  PUT,
  DELETE,
  UNKNOWN
};

enum class uri_enum{
  main,
  order,
  product,
  basket,
  help,
  unknown
};

class Stats {
public:
  Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;

private:
  map<string_view, int> methods;
  map<string_view, int> uris;
  const array<string, 5> data_methods;
  const array<string, 6> data_uri;
};

HttpRequest ParseRequest(string_view line);