// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "wayback_machine.h"
#include <cinder/app/App.h>
#include <vector>
#include <memory>

using namespace std;

namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::App;
using namespace std;
using namespace cinder;

MyApp::MyApp(): csv{} {}


/**
 * Load data and intialize Gui
 */
void MyApp::setup() {
    csv.load_data();
    ImGui::initialize();
}

/**
 * Updates player statlines based on user input
 */
void MyApp::update() {
    ImGui::Text(csv.get_header().c_str());

    for (size_t i = 0; i < years.size(); i++) {
        string line = csv.print_stats(years.at(i));
        ImGui::BulletText(line.c_str());
    }

    for (size_t i = 0; i < comparisons.size(); i++) {
        string line = csv.print_stats(comparisons.at(i));
        ImGui::BulletText(line.c_str());
    }
}

/**
 * Implement text fields for user input and according trigger subsequent actions either player or comparison search
 */
void MyApp::draw() {
    static char user_input[40] = "Hit enter to search";
    ImGui::Text("Please enter a current or former NBA player to begin the search"); // first user input
    if (ImGui::InputText("Enter player name", user_input, IM_ARRAYSIZE(user_input),
            ImGuiInputTextFlags_EnterReturnsTrue)) {
        name = user_input;
        years.clear();
        comparisons.clear();
        years = csv.find_player(user_input);
    }

    static char input[40] = "Hit search to enter";
    ImGui::Text("Now enter the year you would like to run comparisons to."); // second user input
    if (ImGui::InputText("Enter desired season", input, IM_ARRAYSIZE(input),
            ImGuiInputTextFlags_EnterReturnsTrue)) {
        comparisons.clear();
        //years.clear();
        comparisons = csv.find_similarities(input, name);
    }
}

void MyApp::keyDown(KeyEvent event) {
}

}  // namespace myapp
