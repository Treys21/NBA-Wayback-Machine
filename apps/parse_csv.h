//
// Created by Anik on 5/6/2020.
//

#ifndef FINALPROJECT_PARSE_CSV_H
#define FINALPROJECT_PARSE_CSV_H

#include <cinder/app/App.h>
#include <csv.h>
#include <vector>
#include "CinderImGui.h"

using namespace csv2;
using namespace std;

namespace myapp {

    class ParseCsv {
    private:
        vector<int> find_player(std::string name);
        vector<double> find_similarities(int row);
        std::string print_stats(int row);
    };

}

#endif //FINALPROJECT_PARSE_CSV_H
