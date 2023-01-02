#include "frame.h"
#include "app.h"
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <iostream>

EventFrame::EventFrame() {
    std::cerr << "EventFrame::EventFrame" << std::endl;
}

EventFrame::~EventFrame() {
    std::cerr << "EventFrame::~EventFrame" << std::endl;
}

bool EventFrame::Create(wxString name) {
    std::cerr << "EventFrame::Create " << name << ": " << this << std::endl;

    if (!wxFrame::Create(nullptr, wxID_ANY, name)) {
        return false;
    }

    Bind(wxEVT_CLOSE_WINDOW, &EventFrame::OnCloseWindow, this);
    CreateMenuBar();

    return true;
}

void EventFrame::CreateMenuBar() {
    wxMenuBar *menuBar = new wxMenuBar;



    wxMenu *menuFile = new wxMenu;

    menuFile->Append(wxID_OPEN);
    Bind(wxEVT_MENU, &EventFrame::OnFileOpen, this, wxID_OPEN);
    Bind(wxEVT_UPDATE_UI, &EventFrame::OnUpdateFileOpen, this, wxID_OPEN);

    menuFile->AppendSeparator();

    menuFile->Append(wxID_EXIT);
    Bind(wxEVT_MENU, &EventApp::OnFileExit, &wxGetApp(), wxID_EXIT);

    menuBar->Append(menuFile, "&File");



    SetMenuBar(menuBar);
}

void EventFrame::OnCloseWindow(wxCloseEvent &event) {
    std::cerr << "EventFrame::OnCloseWindow " << this->GetTitle() << std::endl;
    wxGetApp().OnCloseFrame(this);
}

void EventFrame::OnUpdateFileOpen(wxUpdateUIEvent &event) {
    std::cerr << "EventFrame::OnUpdateFileOpen " << this->GetTitle() << std::endl;
    event.Enable(false);
}

void EventFrame::OnFileOpen(wxCommandEvent &event) {
    std::cerr << "EventFrame::OnFileOpen " << this->GetTitle() << std::endl;
}
