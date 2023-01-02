#include "app.h"
#include "frame.h"
#include <iostream>

wxIMPLEMENT_APP(EventApp);

EventApp::EventApp() : f1{nullptr} {
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

    this->f1 = new EventFrame;
    this->f1->Create("A");
    this->f1->Show();

    return true;
}

int EventApp::OnExit() {
    std::cerr << "EventApp::OnExit" << std::endl;

    return wxApp::OnExit();
}

void EventApp::OnCloseFrame(wxFrame *frame) {
    std::cerr << "EventApp::OnCloseFrame: " << frame << std::endl;    
    if (frame == this->f1) {
        std::cerr << "deleting frame..." << std::endl;    
        this->f1->Destroy();
        this->f1 = nullptr;
    }
}

void EventApp::OnFileExit(wxCommandEvent &event) {
    std::cerr << "EventApp::OnFileExit" << std::endl;
    if (this->f1) {
        wxCloseEvent e{wxEVT_CLOSE_WINDOW, this->f1->GetId()};
        this->f1->OnCloseWindow(e);
    }
}
