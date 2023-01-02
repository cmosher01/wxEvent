#ifndef APP_H
#define APP_H

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/event.h>

class EventFrame;

class EventApp : public wxApp {
    EventFrame *f1;

public:
    EventApp();
    virtual ~EventApp();

    virtual bool OnInit() override;
    virtual int OnExit() override;

    void OnCloseFrame(wxFrame *frame);
    void OnFileExit(wxCommandEvent &event);
};

wxDECLARE_APP(EventApp);

#endif
