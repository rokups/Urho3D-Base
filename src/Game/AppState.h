//
// Copyright (c) 2016 Rokas Kupstys
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#pragma once

#include "Common.h"
#include "GameApplication.h"


class AppState
    : public Urho3D::Object
{
    URHO3D_OBJECT(AppState, Urho3D::Object);
protected:
    SharedPtr<AppState> _suspended;
    bool _eventsSuspended = false;
    static SharedPtr<AppState> _current;
    friend class GameApplication;

public:
    AppState(Context* ctx) : Urho3D::Object(ctx) { }

    virtual ~AppState() { }

    static AppState* Current() { return _current; }

    /// Called when state is entered
    virtual void Start() { };

    /// Called when state is suspended
    virtual void Suspend() { };

    /// Called when state is resumed
    virtual void Resume() { };

    /// Called when state is left
    virtual void Stop() { };

    virtual void OnEvent(Object* sender, StringHash eventType, VariantMap& eventData)
    {
        if (!GetEventsSuspended())
        {
            float delta = eventData[Update::P_TIMESTEP].GetFloat();
            Urho3D::Object::OnEvent(sender, eventType, eventData);
        }
    }

    /// Leaves current state, destroys it and enters into next one
    template<typename T>
    void EnterInto()
    {
        this->Stop();
        auto next = context_->CreateObject<T>();
        _current = StaticCast<AppState, T>(next);
        next->Start();
    }

    /// Enters first state, can be called just once on application startup
    template<typename T>
    static void EnterInto(SharedPtr<T> state)
    {
        assert(_current.Get() == nullptr);
        _current = StaticCast<AppState, T>(state);
        _current->Start();
    }

    /// Leaves curernt state, suspends it and enters into next one
    template<typename T>
    void SuspendInto()
    {
        this->Suspend();
        this->_eventsSuspended = true;
        SharedPtr<T> next = nullptr;
        if (_suspended)
            next = StaticCast<T>(_suspended);
        else
            next = context_->CreateObject<T>();
        next->_suspended = this;
        next->_eventsSuspended = false;
        _current = StaticCast<AppState, T>(next);
        if (_suspended)
        {
            _suspended = nullptr;
            next->Resume();
        }
        else
            next->Start();
    }

    /// Leaves current state, resumes previous one if there is one, otherwise exits application
    void Leave()
    {
        this->Stop();
        if (_suspended)
        {
            auto previous = _suspended;  // Save pointer on the stack. Next statement causes current object to destruct
                                         // and _suspended becomes invalid.
            _current = previous;
            _current->_eventsSuspended = false;
            _current->Resume();
        }
        else
        {
            _current = nullptr;
            GameApplication::get().Exit();
        }
    }

    /// Exits from application by executing chain of Leave() events until no previous state is left.
    static void Exit()
    {
        while (_current)
            _current->Leave();
    }

    bool SuspendedStateExists()
    {
        return _suspended.Get() != 0;
    }

    virtual bool GetEventsSuspended()
    {
        return _eventsSuspended;
    }
};

