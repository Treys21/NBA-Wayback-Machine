// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <vector>
#include <fstream>
#include "CinderImGui.h"
#include "csv2/reader.hpp"

using namespace std;

namespace mylibrary {

    class ParseCsv {
    public:
        void load_data();
        vector<int> find_player(string name);
        vector<int> find_similarities(string season, string name);
        string print_stats(int row);
        bool is_similar(vector<double> first_player, vector<double> second_player);
        vector<vector<string>> data;
        string getHeader();

    private:
        vector<double> get_stats(vector<string> player);
        const int useless_col = 7;
        const int stat_start = 12;
        const int stat_end = 17;
        const int position_index = 4;
        const int name_index = 1;
        const int minutes_min = 1000;
        const int percent_conversion = 100;
        const double percent = 20; // desired margin of error for stats
        const double rounding_factor = 0.01; // to prevent division by 0
        const string filename = "nba-data-historical.csv";
    };
}
  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
