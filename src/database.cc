// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/database.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <imgui.h>
#include <cmath>
#include <algorithm>
#include <csv2/reader.hpp>

using namespace std;

namespace mylibrary {

    /**
     * Uses ifstream to read csv file line by line into a 2d string vector
     */
    void Database::load_data() {
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
    vector<int> Database::find_player(string name) {
        vector<int> years;

        transform(name.begin(), name.end(), name.begin(), ::tolower);

        for (size_t i = 1; i < data.size(); i++) {
            string player = data.at(i).at(name_index);
            transform(player.begin(), player.end(), player.begin(), ::tolower);
            if (player.compare(name) == 0) {
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
    vector<int> Database::find_similarities(string season, string name) {
        int row_number = 0;
        vector<int> comps;

        transform(name.begin(), name.end(), name.begin(), ::tolower);

        for (size_t i = 0; i < data.size(); i++) {
            string player = data.at(i).at(name_index);
            transform(player.begin(), player.end(), player.begin(), ::tolower);

            if (player.compare(name) == 0 && data.at(i).at(name_index + 1).compare(season) == 0) {
                row_number = i;
                break;
            }
        }

        if (row_number == 0) {
            return comps;
        }

        vector<double> stat_line = get_stats(data.at(row_number));

        for (size_t i = 1; i < data.size(); i++) {
            string bball_player = data.at(i).at(name_index);
            transform(bball_player.begin(), bball_player.end(), bball_player.begin(), ::tolower);

            if (data.at(row_number).at(position_index).compare(data.at(i).at(position_index)) != 0 ||
                bball_player.compare(name) == 0) {
                continue;
            }

            boolean similarities = is_similar(stat_line, get_stats(data.at(i)));

            if (similarities) {
                comps.push_back(i);
            }
        }

        return comps;
    }

    /**
     * Gets stats to compare from the data of player season from the string vector
     * @param player other player
     * @return list of stats to compare
     */
    vector<double> Database::get_stats(vector<string> player) {
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
    bool Database::is_similar(vector<double> first_player, vector<double> second_player) {

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
    string Database::print_stats(int row) {
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
    string Database::get_header() {
        return "Player Year Age Position Team Team Rating Points/36 True Shooting Assists/36 Rebounds/36 Blocks/36";
    }

}  // namespace mylibrary
