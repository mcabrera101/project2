#pragma once

#include <string>
using namespace std;

class Webpage {
public:
    Webpage(){
      url = "";
      time = 0;}
    Webpage(const string& webpageUrl, const time_t& timeVisited){
      this->url = webpageUrl;
      this->time = timeVisited;
    }

    void setUrl(string &url) {this->url = url;}
    string getUrl() const {return url;}

    void setTime(time_t time){this->time = time;}
    time_t getTime() const {return time;}


private:
    string url;
    time_t time;
};
