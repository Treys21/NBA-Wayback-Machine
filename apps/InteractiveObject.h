//
// Created by Anik on 5/6/2020.
//

#ifndef FINALPROJECT_INTERACTIVEOBJECT_H
#define FINALPROJECT_INTERACTIVEOBJECT_H

#endif //FINALPROJECT_INTERACTIVEOBJECT_H

#pragma once
#include "cinder/Rect.h"
#include "cinder/Color.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

namespace myapp {
    class InteractiveObject{
    public:
        InteractiveObject( const ci::Rectf& rect );
        virtual ~InteractiveObject();
        virtual void draw();
        virtual void pressed();
        virtual void pressedOutside();
        virtual void released();
        virtual void releasedOutside();
        virtual void rolledOver();
        virtual void rolledOut();
        virtual void dragged();
        void mouseDown( ci::app::MouseEvent& event );
        void mouseUp( ci::app::MouseEvent& event );
        void mouseDrag( ci::app::MouseEvent& event );
        void mouseMove( ci::app::MouseEvent& event );
        ci::Rectf rect;
        ci::Color pressedColor, idleColor, overColor, strokeColor;
    protected:
        bool mPressed, mOver;
    };
}
