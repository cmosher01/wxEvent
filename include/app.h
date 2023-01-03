#ifndef APP_H
#define APP_H

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/event.h>

class EventFrame;

class EventApp : public wxApp {
    EventFrame *frame;

    void CreateFrame();
    void DeleteFrame();

    virtual bool OnInit() override;
    virtual int OnExit() override;

public:
    EventApp();
    virtual ~EventApp();

    void OnFileExit(const wxCommandEvent &event);
    void OnEndSession(const wxCloseEvent &event);

    void CloseFrame(wxFrame *frame);
};

wxDECLARE_APP(EventApp);

#endif
