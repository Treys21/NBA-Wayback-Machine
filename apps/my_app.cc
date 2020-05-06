// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>

#include <memory>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::App;
using namespace std;
using namespace cinder;

shared_ptr<InteractiveTextBox> textBox;


MyApp::MyApp() { }

void MyApp::setup() {
    cinder::Rectf rect( 0, 0, 300.0f, 300.0f );
    textBox = std::make_shared<InteractiveTextBox>( rect );
}

void MyApp::update() { }

void MyApp::draw() {
    gl::enableAlphaBlending();
    gl::clear( Color( 0, 0, 0 ) );
    textBox->draw();
}

void MyApp::keyDown(KeyEvent event) {
    textBox->keyDown( event );
}

void MyApp::mouseDown( cinder::app::MouseEvent event ){
    textBox->mouseDown( event );
}
void MyApp::mouseUp( cinder::app::MouseEvent event ){
    textBox->mouseUp( event );
}

void MyApp::mouseDrag( cinder::app::MouseEvent event ){
    textBox->mouseDrag( event );
}
void MyApp::mouseMove( cinder::app::MouseEvent event ){
    textBox->mouseMove( event );
}

}  // namespace myapp
