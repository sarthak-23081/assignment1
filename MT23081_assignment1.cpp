#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

double calculateActualValue(double amount, int year, double interest_rates[])
{
    int current_year = 2022;
    int prev_year = 1960;
    int index_year = year - prev_year;

    double actual_value = amount;
    double net_rate;
    for (int i = index_year; i <= (current_year - prev_year); i++)
    {
        net_rate = interest_rates[i];
        actual_value *= (1 + (net_rate / 100));
    }

    return actual_value;
}

double calculateMoneyValue(double amount, int year, double inflation_rates[], double interest_rates[])
{
    int current_year = 2022;
    int prev_year = 1960;
    int index_year = year - prev_year;

    double money_value = amount;
    double net_rate;

    for (int i = index_year; i <= (current_year - prev_year); i++)
    {
        net_rate = interest_rates[i] - inflation_rates[i];
        money_value *= (1 + (net_rate / 100));
    }
    return money_value;
}

int main()
{
    const int MAX_VALUES = 63;

    ifstream inputFile("india_data.csv");

    if (!inputFile.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    double intrestRate[MAX_VALUES];
    double inflationRate[MAX_VALUES];
    int intrestRateCount = 0;
    int inflationCount = 0;
    double amount;
    int year;
    double actual_value;
    double money_value;
    string line;

    getline(inputFile, line);

    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string token;

        if (!getline(ss, token, ','))
            continue;
        if (!getline(ss, token, ','))
            continue;

        if (!getline(ss, token, ','))
        {
            cerr << "Invalid data format in CSV file." << endl;
            continue;
        }
        double rate = std::stod(token);
        if (intrestRateCount < MAX_VALUES)
        {
            intrestRate[intrestRateCount] = rate;
            intrestRateCount++;
        }

        if (!getline(ss, token, ','))
        {
            cerr << "Invalid data format in CSV file." << endl;
            continue;
        }
        double inflationValue = stod(token);
        if (inflationCount < MAX_VALUES)
        {
            inflationRate[inflationCount] = inflationValue;
            inflationCount++;
        }
    }

    inputFile.close();

    cout << "amount invested(₹): ";
    if (!(cin >> amount))
    {
        cerr << "Error: Invalid input for amount." << endl;
        return 1;
    }

    cout << "year of investment (1960 - 2022): ";
    if (!(cin >> year) || year < 1960 || year > 2022)
    {
        cerr << "Error: Invalid input for year." << endl;
        return 1;
    }

    actual_value = calculateActualValue(amount, year, intrestRate);
    money_value = calculateMoneyValue(amount, year, inflationRate, intrestRate);

    cout << fixed << setprecision(2);
    cout << "actual money received in 2022: " << actual_value << endl;
    cout << "value of money in 2022: " << money_value << endl;

    return 0;
}
