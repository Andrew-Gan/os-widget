#ifndef __PANEL_H__
#define __PANEL_H__

#include <string>
#include <gtkmm.h>
#include "os_info.h"

class MainPanel : public Gtk::Window {
public:
    MainPanel();
    virtual ~MainPanel();
private:
    bool updateInfo();
    void but_win_event(), but_lin_event();
    Gtk::Box box, box_win, box_lin;
    Gtk::Image img_win, img_lin;
    Gtk::TextView view_win, view_lin, view_disk_win, view_disk_lin;
    Glib::RefPtr<Gtk::TextBuffer> textbuff_win = Gtk::TextBuffer::create();
    Glib::RefPtr<Gtk::TextBuffer> textbuff_lin = Gtk::TextBuffer::create();
    Glib::RefPtr<Gtk::TextBuffer> textbuff_disk_win = Gtk::TextBuffer::create();
    Glib::RefPtr<Gtk::TextBuffer> textbuff_disk_lin = Gtk::TextBuffer::create();
    Gtk::ProgressBar bar_win, bar_lin;
    Gtk::VSeparator sep;;
    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    Gtk::Frame frame_disk_win, frame_disk_lin;
    Gtk::Button but_win, but_lin;
};

#endif