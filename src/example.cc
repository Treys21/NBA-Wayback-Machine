// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/example.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <imgui.h>
#include <cmath>
#include <csv2/reader.hpp>

using namespace std;
using namespace csv2;

namespace mylibrary {

    void ParseCsv::load_data() {

        ifstream file("C:\\Users\\Anik Patel\\Desktop\\cinder_0.9.2_vc2015\\my-projects\\final-project-Treys21\\resources\\nba-data-historical.csv");

        string word, row;
        while (getline(file, row)) {
            vector<string> line;
            stringstream stream(row);
            while (getline(stream, word, ',')) {
                line.push_back(word);
            }
            data.push_back(line);
        }
        file.close();
    }

    vector<int> ParseCsv::find_player(string name) {
        vector<int> years;
        int index = 1; //index of player name

        for (size_t i = 1; i < data.size(); i++) {
            if (data.at(i).at(index).compare(name) == 0) {
                years.push_back(i);
            }
        }

        return years;
    }


    vector<int> ParseCsv::find_similarities(string season, string name) {
        int row_number = 0;
        int name_index = 1;
        for (size_t i = 0; i < data.size(); i++) {
            if (data.at(i).at(name_index).compare(name) == 0 && data.at(i).at(name_index + 1).compare(season) == 0) {
                row_number = i;
                break;
            }
        }

        vector<string> player = data.at(row_number);
        const int player_count = 20;
        vector<double> stat_line = get_stats(player);

        vector<int> comps;
        vector<double> percentage;



        double percent = 10; // desired margin of error for stats

        cout << data.size() <<  endl;
        for (int i = 1; i < 1000; i++) {
            double similarities = compare_stats(stat_line, get_stats(data.at(i)), percent);
            if (similarities > 60 && data.at(i).at(name_index).compare(name) != 0) {
                percentage.push_back(similarities);
                comps.push_back(i);
                cout << i << endl;
            }
        }


        return comps;
    }

    vector<double> ParseCsv::get_stats(vector<string> player) {
        int stat_index = 8; // starting index of stats
        vector<double> stat_line;
        for (size_t i = stat_index; i < 17; i++) {
            if (player.at(i).length() == 0) {
                stat_line.push_back(0);
            } else {
                stat_line.push_back(stod(player.at(i)));
            }
        }
        return stat_line;
    }

    double ParseCsv::compare_stats(vector<double> first_player, vector<double> second_player, double percent) {
        double similar_counter = 0;
        for (size_t i = 1; i < first_player.size(); i++) {
            double percent_diff = 100 * (abs(second_player.at(i) - first_player.at(i)) / (first_player.at(i) + 0.01));

            if (percent_diff <= percent) {
                similar_counter++;
            }
        }
        return (similar_counter / first_player.size()) * 100;
    }

    string ParseCsv::print_stats(int row) {
        vector<string> stats = data.at(row);
        string statline = stats.at(1) + " " + stats.at(2) + " " + stats.at(4) + " " + stats.at(5);

        for (int i = 12; i < 17; i++) {
            statline = statline + "     " + stats.at(i);
        }
        return statline;
    }

}  // namespace mylibrary
