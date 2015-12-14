#include <curl/curl.h>

int main() {
    CURL *curl = curl_easy_init();
    if (curl) {
      CURLcode res;
      curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080");
      res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
    }
    return 1;
}