// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include <memory>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::App;
using namespace std;
using namespace cinder;

MyApp::MyApp() { }

void MyApp::setup() {
    ImGui::initialize();
}

void MyApp::update() {
    if (ImGui::Button("Search Player")) {

    }
}

void MyApp::draw() {
    ImGui::Text("Please enter a current of former NBA player to begin the search");

    static char name[14] = "stephen curry";
    ImGui::InputText("Player Name", name, IM_ARRAYSIZE(name));
    ImGui::SameLine(0, -1);
    ImGui::Button("Search Player");
}

void MyApp::keyDown(KeyEvent event) {
}

}  // namespace myapp
