#include "app.h"
#include "frame.h"
#include <iostream>



wxIMPLEMENT_APP(EventApp);



EventApp::EventApp() : frame{nullptr} {
    std::cerr << "EventApp::EventApp" << std::endl;
}

EventApp::~EventApp() {
    std::cerr << "EventApp::~EventApp" << std::endl;
}



bool EventApp::OnInit() {
    std::cerr << "EventApp::OnInit" << std::endl;

    if (!wxApp::OnInit()) {
        return false;
    }

    Bind(wxEVT_END_SESSION, &EventApp::OnEndSession, this);

    CreateFrame();

    return true;
}

int EventApp::OnExit() {
    std::cerr << "EventApp::OnExit" << std::endl;

    return wxApp::OnExit();
}



void EventApp::CreateFrame() {
    std::cerr << "Creating frame..." << std::endl;

    this->frame = new EventFrame;
    this->frame->Create(GetAppDisplayName());
    this->frame->Show();
}

void EventApp::DeleteFrame() {
    std::cerr << "Deleting frame..." << std::endl;

    this->frame->Destroy();
    this->frame = nullptr;
}



void EventApp::OnFileExit(const wxCommandEvent &event) {
    std::cerr << "EventApp::OnFileExit" << std::endl;

    if (this->frame) {
        OnEndSession(wxCloseEvent{wxEVT_CLOSE_WINDOW, this->frame->GetId()});
    }
}

void EventApp::OnEndSession(const wxCloseEvent &event) {
    if (this->frame) {
        this->frame->OnCloseWindow(event);
    }
}



void EventApp::CloseFrame(wxFrame *frame) {
    std::cerr << "EventApp::CloseFrame: " << frame << std::endl;

    if (frame == this->frame) {
        DeleteFrame();
    }
}
