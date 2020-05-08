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
        vector<double> get_stats(vector<string> player);
        double compare_stats(vector<double> first_player, vector<double> second_player, double percent);
        vector<vector<string>> data;
    };
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
