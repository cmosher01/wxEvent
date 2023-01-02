#ifndef FRAME_H
#define FRAME_H

#include <wx/frame.h>
#include <wx/event.h>
#include <wx/string.h>

class EventFrame : public wxFrame {
    void CreateMenuBar();

    void OnUpdateFileOpen(wxUpdateUIEvent &event);
    void OnFileOpen(wxCommandEvent &event);

public:
    EventFrame();
    virtual ~EventFrame();

    bool Create(wxString name);

    void OnCloseWindow(wxCloseEvent &event);
};

#endif
