//
// Created by Anik on 5/6/2020.
//

#include "InteractiveTextBox.h"
using namespace std;
using namespace ci;
using namespace ci::app;

InteractiveTextBox::InteractiveTextBox( const Rectf& rect ):InteractiveObject( rect ) {
    mActive = false;
    mText = "Write some text";
    mTextBox.setText( mText );
    mTextBox.setFont( Font( "Arial", 24 ) );
    mTextBox.setPremultiplied( true );
    mTextBox.setSize( Vec2i( rect.getWidth(), rect.getHeight() ) );
    mTextBox.setBackgroundColor( Color::white() );
    mTextBox.setColor( Color::black() );
    mFirstText = true;
}

void InteractiveTextBox::draw(){
    if( mActive ){
        mTextBox.setBackgroundColor( Color( 0.7f, 0.7f, 1.0f ) );
    } else {
        mTextBox.setBackgroundColor( Color::white() );
    }
    gl::color( Color::white() );
    gl::Texture texture = mTextBox.render();
    gl::draw( texture, rect );
}

void InteractiveTextBox::pressed(){
    mActive = true;
}
void InteractiveTextBox::releasedOutside(){
    mActive = false;
}

void InteractiveTextBox::keyDown( KeyEvent& event ){
    if( mActive == false ) return;
    if( mFirstText ){
        mText = "";
        mFirstText = false;
    }
    if( event.getCode() == KeyEvent::KEY_BACKSPACE ){
        if( mText.size() > 0 ){
            mText = mText.substr( 0, mText.size()-1 );
        }
    } else {
        const char character = event.getChar();
        mText += string( &character, 1 );
    }
    mTextBox.setText( mText );
}