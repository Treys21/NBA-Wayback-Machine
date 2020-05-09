// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <mylibrary/database.h>

using namespace std;

mylibrary::Database csv;

TEST_CASE("Find Similarities", "[Database]") {
    csv.load_data();
    REQUIRE(csv.find_similarities("2016", "klay thompson").size() > 0);
    REQUIRE(csv.find_similarities("2016", "KeViN DuRaNt").size() > 0);
    REQUIRE(csv.find_similarities("2016", "ANDREW WIGGINS").size() > 0);
    REQUIRE(csv.find_similarities("1980", "klay thompson").size() == 0);
    REQUIRE(csv.find_similarities("2010", "larry bird").size() == 0);
}

TEST_CASE("Load nba data", "[Load Data]") {
    ifstream file;
    file.open(cinder::app::getAssetPath("nba-data-historical.csv"));
    string row;
    getline(file, row);
    REQUIRE(row.length() != 0);
    csv.load_data();
}

TEST_CASE("Find Player", "[Database]") {
    csv.load_data();
    REQUIRE(csv.find_player("Stephen Curry").size() > 0);
    REQUIRE(csv.find_player("James Harden").size() > 0);
    REQUIRE(csv.find_player("Kareem Abdul-Jabbar").size() > 0);
    REQUIRE(csv.find_player("Tom Brady").size() == 0);
    REQUIRE(csv.find_player("").size() == 0);
    REQUIRE(csv.find_player("stephen curry").size() > 0);
}

TEST_CASE("Fetching Stats", "[Database]") {
    csv.load_data();
    REQUIRE(csv.get_stats(csv.data.at(5)).size() > 0);
    REQUIRE(csv.get_stats(csv.data.at(500)).size() > 0);
    REQUIRE(csv.get_stats(csv.data.at(1)).size() > 0);
    REQUIRE(csv.get_stats(csv.data.at(5000)).size() > 0);
}

TEST_CASE("Similarity Check", "[Database]") {
    csv.load_data();
    vector<double> player = csv.get_stats(csv.data.at(1));
    vector<double> other_player = csv.get_stats(csv.data.at(20000));

    REQUIRE(csv.is_similar(player, player));
    REQUIRE(csv.is_similar(player, other_player) == false);
}

TEST_CASE("Printing Stats", "[Database]") {
    csv.load_data();

    REQUIRE(csv.print_stats(1).compare("") != 0);
    REQUIRE(csv.print_stats(5).compare("") != 0);
    REQUIRE(csv.print_stats(500).compare("") != 0);
    REQUIRE(csv.print_stats(20000).compare("") != 0);
}

TEST_CASE("Generate Header", "[Database]") {
    REQUIRE(csv.get_header().compare("") != 0);
}