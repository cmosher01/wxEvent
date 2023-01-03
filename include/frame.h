#ifndef FRAME_H
#define FRAME_H

#include <wx/frame.h>
#include <wx/event.h>
#include <wx/string.h>

class EventFrame : public wxFrame {
    void CreateMenuBar();

    void OnUpdateFileOpen(wxUpdateUIEvent &event);
    void OnFileOpen(const wxCommandEvent &event);

public:
    EventFrame();
    virtual ~EventFrame();

    bool Create(const wxString name);

    void OnCloseWindow(const wxCloseEvent &event);
};

#endif
