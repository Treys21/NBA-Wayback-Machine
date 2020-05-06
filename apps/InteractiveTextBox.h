//
// Created by Anik on 5/6/2020.
//

#ifndef FINALPROJECT_INTERACTIVETEXTBOX_H
#define FINALPROJECT_INTERACTIVETEXTBOX_H

#pragma once
#include "InteractiveObject.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/KeyEvent.h"
//#include "cinder/app/AppBasic.h"

class InteractiveTextBox: public InteractiveObject{
public:
    InteractiveTextBox( const ci::Rectf& rect );
    virtual void draw();
    virtual void pressed();
    virtual void releasedOutside();
    void keyDown( ci::app::KeyEvent& event );
protected:
    ci::TextBox mTextBox;
    std::string mText;
    bool mActive;
    bool mFirstText;
};

#endif //FINALPROJECT_INTERACTIVETEXTBOX_H

