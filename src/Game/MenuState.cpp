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
#include "MenuState.h"
#include "GameState.h"


MenuState::MenuState(Context* ctx)
    : AppState(ctx)
{
}

void MenuState::Start()
{
    logger.Write(LOG_DEBUG, "MenuState::Start");

    _menuWindow = gui.GetRoot()->CreateChild<Window>();
    _menuWindow->SetAlignment(HA_CENTER, VA_CENTER);
    _menuWindow->SetSize(150, 100);
    _menuWindow->SetStyleAuto();
    _menuWindow->SetVisible(true);

    // Start button
    {
        auto start = _menuWindow->CreateChild<Button>();
        start->SetAlignment(HA_CENTER, VA_CENTER);
        start->SetPosition(0, -20);
        start->SetMinHeight(24);
        start->SetMinWidth(100);
        start->SetStyleAuto();
        auto startText = start->CreateChild<Text>();
        startText->SetAlignment(HA_CENTER, VA_CENTER);
        startText->SetText("To Game");
        startText->SetStyleAuto();

        SubscribeToEvent(start, E_CLICK, [&](StringHash, VariantMap&) {
            SuspendInto<GameState>();
        });
    }

    // Exit button
    {
        auto exit = _menuWindow->CreateChild<Button>();
        exit->SetAlignment(HA_CENTER, VA_CENTER);
        exit->SetPosition(0, 20);
        exit->SetMinHeight(24);
        exit->SetMinWidth(100);
        exit->SetStyleAuto();
        auto exitText = exit->CreateChild<Text>();
        exitText->SetAlignment(HA_CENTER, VA_CENTER);
        exitText->SetText("Exit");
        exitText->SetStyleAuto();

        SubscribeToEvent(exit, E_CLICK, [&](StringHash, VariantMap&) {
            Exit();
        });
    }

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(MenuState, OnUpdate));
}

void MenuState::Suspend()
{
    logger.Write(LOG_DEBUG, "MenuState::Suspend");
    _menuWindow->SetVisible(false);
}

void MenuState::Resume()
{
    logger.Write(LOG_DEBUG, "MenuState::Resume");
    _menuWindow->SetVisible(true);
}

void MenuState::Stop()
{
    logger.Write(LOG_DEBUG, "MenuState::Stop");
    _menuWindow->Remove();
    _menuWindow = 0;
}

void MenuState::OnUpdate(StringHash event, VariantMap& args)
{
    if (inputsys.GetKeyPress(KEY_ESCAPE))
    {
        Leave();
    }
}
