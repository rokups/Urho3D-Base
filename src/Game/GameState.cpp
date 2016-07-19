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
#include "GameState.h"
#include "MenuState.h"


GameState::GameState(Context* ctx)
    : AppState(ctx)
{
}

void GameState::Start()
{
    logger.Write(LOG_DEBUG, "GameState::Start");

    consolesys.SetCommandInterpreter(GetTypeName());
    _text = gui.GetRoot()->CreateChild<Text>();
    _text->SetText("Hello Urho3D-Base");
    _text->SetAlignment(HA_CENTER, VA_CENTER);
    _text->SetStyleAuto();

    SubscribeToEvent(E_UPDATE, std::bind(&GameState::OnUpdate, this, _1, _2));
    SubscribeToEvent(E_CONSOLECOMMAND, std::bind(&GameState::OnConsoleCommand, this, _1, _2));
}

void GameState::Suspend()
{
    logger.Write(LOG_DEBUG, "GameState::Suspend");
    _text->SetVisible(false);
}

void GameState::Resume()
{
    logger.Write(LOG_DEBUG, "GameState::Resume");
    _text->SetVisible(true);
}

void GameState::Stop()
{
    logger.Write(LOG_DEBUG, "GameState::Stop");
    _text->Remove();
    _text = 0;
}

void GameState::OnUpdate(StringHash event, VariantMap& args)
{
    if (inputsys.GetKeyPress('`'))
    {
        consolesys.Toggle();
    }
    else if (inputsys.GetKeyPress(KEY_ESCAPE))
    {
        if (consolesys.IsVisible())
            consolesys.Toggle();
        else
            SuspendInto<MenuState>();
    }
}

void GameState::OnConsoleCommand(StringHash event, VariantMap& args)
{
    if (args[ConsoleCommand::P_ID].GetString() == GetTypeName())
        logger.Write(LOG_DEBUG, "Console command: " + args[ConsoleCommand::P_COMMAND].GetString());
}


