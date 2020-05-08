// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
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
static char user_input[40] = "hit search to enter";

void MyApp::setup() {
    csv.load_data();
    ImGui::initialize();
}

void MyApp::update() {
    for (int i = 0; i < years.size(); i++) {
        string line = csv.print_stats(years.at(i));
        ImGui::BulletText(line.c_str());
    }

    for (int i = 0; i < comparisons.size(); i++) {
        string line = csv.print_stats(comparisons.at(i));
        ImGui::BulletText(line.c_str());
    }
}

void MyApp::draw() {
    ImGui::Text("Please enter a current or former NBA player to begin the search");
    if (ImGui::InputText("Enter player name", user_input, IM_ARRAYSIZE(user_input), ImGuiInputTextFlags_EnterReturnsTrue)) {
        name = user_input;
        years.clear();
        years = csv.find_player(user_input);
    }

    static char input[40] = "hit search to enter";
    ImGui::Text("Now enter the year you would like to run comparisons to.");
    if (ImGui::InputText("Enter desired season", input, IM_ARRAYSIZE(input), ImGuiInputTextFlags_EnterReturnsTrue)) {
        comparisons.clear();
        comparisons = csv.find_similarities(input, name);
    }
}

void MyApp::keyDown(KeyEvent event) {
}

}  // namespace myapp
