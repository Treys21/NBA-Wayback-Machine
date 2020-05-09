// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/database.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <imgui.h>
#include <cmath>
#include <csv2/reader.hpp>

using namespace std;

namespace mylibrary {

    /**
     * Uses ifstream to read csv file line by line into a 2d string vector
     */
    void ParseCsv::load_data() {
        ifstream file;
        file.open(cinder::app::getAssetPath(filename));

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

    /**
     * Search data vector to find all seasons a player has played
     * @param name of user inputed player
     * @return list of indices of their seasons
     */
    vector<int> ParseCsv::find_player(string name) {
        vector<int> years;

        for (size_t i = 1; i < data.size(); i++) {
            if (data.at(i).at(1).compare(name) == 0) {
                years.push_back(i);
            }
        }

        return years;
    }


    /**
     * Use helper methods to compare selected to season to every other player in dataset at same position
     * @param season selected by user
     * @param name of player selected by user
     * @return indices of similar seasons
     */
    vector<int> ParseCsv::find_similarities(string season, string name) {
        int row_number = 0;
        for (size_t i = 0; i < data.size(); i++) {
            if (data.at(i).at(name_index).compare(name) == 0 && data.at(i).at(name_index + 1).compare(season) == 0) {
                row_number = i;
                break;
            }
        }

        vector<string> player = data.at(row_number);

        vector<double> stat_line = get_stats(player);

        vector<int> comps;

        for (size_t i = 1; i < data.size(); i++) {

            if (data.at(row_number).at(position_index).compare(data.at(i).at(position_index)) != 0) {
                continue;
            }


            boolean similarities = is_similar(stat_line, get_stats(data.at(i)));
            if (similarities && data.at(i).at(name_index).compare(name) != 0) {
                comps.push_back(i);
            }
        }

        return comps;
    }

    /**
     *
     * @param player
     * @return
     */
    vector<double> ParseCsv::get_stats(vector<string> player) {
        int stat_index = 8; // starting index of stats
        vector<double> stat_line;
        for (size_t i = stat_index; i < stat_end; i++) {
            if (player.at(i).length() == 0) {
                stat_line.push_back(0);
            } else {
                stat_line.push_back(stod(player.at(i)));
            }
        }
        return stat_line;
    }

    /**
     * Compare statlines of players to find out if they are similar or not
     * @param first_player relevant stats to compare
     * @param second_player revalent stats to compare
     * @return false if statline are not similar, true if they are
     */
    bool ParseCsv::is_similar(vector<double> first_player, vector<double> second_player) {

        if (second_player.at(1) < minutes_min) {
            return 0;
        }

        for (size_t i = 1; i < first_player.size(); i++) {
            double percent_diff =  (abs(second_player.at(i) - first_player.at(i)) / (first_player.at(i) + 0.01));
            percent_diff = percent_diff * percent_conversion;

            if (percent_diff > percent) {
                return false;
            }
        }
        return true;
    }

    /**
     * Generate a string for the players season statline with relevant info for user to see
     * @param row of the players season in dataset
     * @return statline to display
     */
    string ParseCsv::print_stats(int row) {
        vector<string> stats = data.at(row);
        string statline;
        for (int i = 1; i < useless_col; i++) {
            statline += " " + stats.at(i);
        }

        for (int i = stat_start; i < stat_end; i++) {
            statline += "     " + stats.at(i);
        }
        return statline;
    }

    /**
     * Return title header for displaying statlines of players
     * @return
     */
    string ParseCsv::getHeader() {
        return "Player Year Age Position Team Team Rating Points/36 True Shooting Assists/36 Rebounds/36 Blocks/36";
    }

}  // namespace mylibrary
