//jose arellano


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class StateClimate {
private:
    int fips;
    int year;
    double temp;
    double tempc;
public:
    // Constructor
    StateClimate(int f, int y, double t, double tc);

    // Getters
    int getFips() const;
    int getYear() const;
    double getTemp() const;
    double getTempC() const;

    // Setters
    void setFips(int f);
    void setYear(int y);
    void setTemp(double t);
    void setTempC(double tc);

    // Display function
    void display() const;
};

StateClimate::StateClimate(int f, int y, double t, double tc) : fips(f), year(y), temp(t), tempc(tc) {}

// Getters
int StateClimate::getFips() const { return fips; }
int StateClimate::getYear() const { return year; }
double StateClimate::getTemp() const { return temp; }
double StateClimate::getTempC() const { return tempc; }

// Setters
void StateClimate::setFips(int f) { fips = f; }
void StateClimate::setYear(int y) { year = y; }
void StateClimate::setTemp(double t) { temp = t; }
void StateClimate::setTempC(double tc) { tempc = tc; }

// Display function
void StateClimate::display() const {
    cout << "FIPS: " << fips << ", Year: " << year
         << ", Temp (F): " << temp << ", Temp (C): " << tempc << std::endl;
}

// Comparison function for sorting and searching
bool compareByFips(const StateClimate &a, const StateClimate &b) {
    return a.getFips() < b.getFips();
}

// Recursive binary search function
int binarySearch(const vector<StateClimate> &data, int targetFips, int left, int right) {
    if (left > right) {
        return -1; // Not found
    }

    int mid = left + (right - left) / 2;
    if (data[mid].getFips() == targetFips) {
        return mid;
    } else if (data[mid].getFips() > targetFips) {
        return binarySearch(data, targetFips, left, mid - 1);
    } else {
        return binarySearch(data, targetFips, mid + 1, right);
    }
}

int main() {
    vector<StateClimate> climateData;
    ifstream file("climdiv_state_year.csv");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip header line
    while (getline(file, line)) {
        stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;
        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();

    // sort data by FIPS code
    sort(climateData.begin(), climateData.end(), compareByFips);

    // Display data
    //for (const auto &entry : climateData) {
       // entry.display();
   // }

    // Allow user to search multiple times
    while (true) {
        int targetFips;
        cout << "Enter FIPS code to search (or -1 to exit): ";
        cin >> targetFips;

        if (targetFips == -1) {
            break;
        }

        int index = binarySearch(climateData, targetFips, 0, climateData.size() - 1);
        if (index != -1) {
            cout << "Record found for FIPS " << targetFips << ":" << endl;
            climateData[index].display();
        } else {
            cout << "Record not found for FIPS " << targetFips << endl;
        }
    }

    return 0;
}
