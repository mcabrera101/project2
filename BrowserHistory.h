#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class BrowserHistory {
public:
	BrowserHistory() {       //default constructor
		numSites = 0;
		navHistory = {};
		navPos = navHistory.begin();
		sitesVisited = {};

	};

	BrowserHistory(const BrowserHistory & other) { //copy constructor
		navHistory = other.navHistory;
		navPos = other.navPos;
		sitesVisited = other.sitesVisited;
	};



	void visitSite(Webpage newSite); // stores site into the containers.
	string back();                   // goes "back" in the operation
	string forward();                // goes "forward"

	void readHistory(string fileName);

	string getUrl();
	size_t getNavSize();
	list<Webpage> getSitesVisited();

private:
	list<Webpage> navHistory;
	list<Webpage>::iterator navPos;
	list<Webpage> sitesVisited;
	int numSites;
};

list<Webpage> BrowserHistory::getSitesVisited() {
	list <Webpage> other;
	other = sitesVisited;
	return other;
}

size_t BrowserHistory::getNavSize() {     //returns navigation size
	return navHistory.size();
}

string BrowserHistory::getUrl() {       //returns url that is being pointed to currently
	if (numSites == 0) { throw std::out_of_range("no sites have been visited"); }
	else {
		return navPos->getUrl();
	}
}

string BrowserHistory::back() {
	if (navPos == navHistory.begin()) { throw std::out_of_range("Iterator at beginning cannot go back."); }
	else {
		--navPos;
	}
	return navPos->getUrl();
}

string BrowserHistory::forward() {
	if (navPos == (--navHistory.end())) { throw std::out_of_range("Iterator at end cannot go forward."); }
	else {
		++navPos;
	}
	return navPos->getUrl();

}

void BrowserHistory::visitSite(Webpage newSite) {
	sitesVisited.push_back(newSite);

if (navPos != --navHistory.end()) {                 // if statement used to make sure page is added at the back
    navHistory.erase(++navPos, navHistory.end());
    --navPos;
  	}

	navHistory.push_back(newSite);
	++navPos;
	++numSites;
}

void BrowserHistory::readHistory(string fileName) {
	string temp;
	int newTime;
	Webpage newSite;
	ifstream inFile(fileName.c_str());

	while (inFile >> temp) {
		if (temp == "new") {
			inFile >> temp >> newTime;
			newSite = Webpage(temp, time_t(newTime));
			visitSite(newSite);
		}
		else if (temp == "back") {
			back();
		}
		else if (temp == "forward") {
			forward();
		}
		else {
			throw logic_error("invalid command");
		}
	}
}
