//
// Created by Anik on 5/6/2020.
//

#include "InteractiveObject.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace myapp {
    InteractiveObject::InteractiveObject( const Rectf& rect ){
        this->rect = rect;
        pressedColor = Color( 1.0f, 0.0f, 0.0f );
        idleColor = Color( 0.7f, 0.7f, 0.7f );
        overColor = Color( 1.0f, 1.0f, 1.0f );
        strokeColor = Color( 0.0f, 0.0f, 0.0f );
        mPressed = false;
        mOver = false;
    }

    InteractiveObject::~InteractiveObject(){
    }

    void InteractiveObject::draw(){
        if( mPressed ){
            gl::color( pressedColor );
        } else if( mOver ){
            gl::color( overColor );
        } else {
            gl::color( idleColor );
        }
        gl::drawSolidRect( rect );
        gl::color( strokeColor );
        gl::drawStrokedRect( rect );
    }

    void InteractiveObject::pressed(){
        console() << "pressed" << endl;
    }
    void InteractiveObject::pressedOutside(){
        console() << "pressed outside" << endl;
    }
    void InteractiveObject::released(){
        console() << "released" << endl;
    }
    void InteractiveObject::releasedOutside(){
        console() << "released outside" << endl;
    }
    void InteractiveObject::rolledOver(){
        console() << "rolled over" << endl;
    }
    void InteractiveObject::rolledOut(){
        console() << "rolled out" << endl;
    }
    void InteractiveObject::dragged(){
        console() << "dragged" << endl;
    }

    void InteractiveObject::mouseDown( MouseEvent& event ){
        if( rect.contains( event.getPos() ) ){
            mPressed = true;
            mOver = false;
            pressed();
        } else{
            pressedOutside();
        }
    }
    void InteractiveObject::mouseUp( MouseEvent& event ){
        if( rect.contains( event.getPos() ) ){
            if( mPressed ){
                mPressed = false;
                mOver = true;
                released();
            }
        } else {
            mPressed = false;
            mOver = false;
            releasedOutside();
        }
    }

    void InteractiveObject::mouseDrag( MouseEvent& event ){
        if( mPressed && rect.contains( event.getPos() ) ){
            mPressed = true;
            mOver = false;
            dragged();
        }
    }
    void InteractiveObject::mouseMove( MouseEvent& event ) {
        if (rect.contains(event.getPos())) {
            if (mOver == false) {
                mPressed = false;
                mOver = true;
                rolledOver();
            }
        } else {
            if (mOver) {
                mPressed = false;
                mOver = false;
                rolledOut();
            }
        }
    }
}