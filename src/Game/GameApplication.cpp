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
#include "GameApplication.h"
#include "AppState.h"
#include "MenuState.h"
#include "GameState.h"


URHO3D_DEFINE_APPLICATION_MAIN(GameApplication);

GameApplication* GameApplication::_instance = 0;
SharedPtr<AppState> AppState::_current;

GameApplication::GameApplication(Context* context)
    : Urho3D::Application(context)
{
    assert(_instance == 0);
    _instance = this;
}

void GameApplication::Setup()
{
    engineParameters_["WindowTitle"] = GetTypeName();
    engineParameters_["Headless"] = false;
    engineParameters_["ResourcePaths"] = "CoreData;Data;GameData";
    engineParameters_["ResourcePrefixPaths"] = filesys.GetProgramDir();
    engineParameters_["FullScreen"] = false;
    engineParameters_["WindowWidth"] = 1027;
    engineParameters_["WindowHeight"] = 768;
#if DEBUG
    logger.SetLevel(LOG_DEBUG);
#endif
}

void GameApplication::Start()
{
    auto style = cache.GetResource<XMLFile>("UI/DefaultStyle.xml");
    inputsys.SetMouseVisible(true);
    gui.GetRoot()->SetDefaultStyle(style);
    gui.GetRoot()->SetStyleAuto();

#if DEBUG
    engine_->CreateDebugHud()->SetDefaultStyle(style);
#endif

    auto console = engine_->CreateConsole();
    console->SetDefaultStyle(style);
    console->GetBackground()->SetOpacity(0.8f);
    console->SetNumRows(32);
    console->SetNumBufferedRows(2 * console->GetNumRows());

    context_->RegisterFactory<MenuState>();
    context_->RegisterFactory<GameState>();

    AppState::EnterInto(context_->CreateObject<MenuState>());
}

void GameApplication::Stop()
{
    AppState::Exit();
}
