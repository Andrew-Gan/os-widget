#include "panel.h"
#include <iostream>

using namespace std;

MainPanel::MainPanel() : box(Gtk::ORIENTATION_HORIZONTAL), box_win(Gtk::ORIENTATION_VERTICAL), box_lin(Gtk::ORIENTATION_VERTICAL) {
    // configure main panel
    set_title("OS Activity Widget");
    set_border_width(5);
    set_default_size(500, 200);
    set_resizable(false);

    // init box_
    box.pack_start(box_win, Gtk::PACK_EXPAND_PADDING);
    box.pack_start(sep, Gtk::PACK_EXPAND_PADDING);
    box.pack_start(box_lin, Gtk::PACK_EXPAND_PADDING);
    box_win.set_size_request(180, -1);
    box_win.pack_start(img_win, Gtk::PACK_EXPAND_PADDING);
    box_win.pack_start(view_win, Gtk::PACK_EXPAND_PADDING);
    box_win.pack_start(frame_disk_win, Gtk::PACK_EXPAND_PADDING);
    box_win.pack_start(bar_win, Gtk::PACK_EXPAND_PADDING);
    box_win.pack_start(but_win, Gtk::PACK_EXPAND_PADDING);
    box_lin.set_size_request(180, -1);
    box_lin.pack_start(img_lin, Gtk::PACK_EXPAND_PADDING);
    box_lin.pack_start(view_lin, Gtk::PACK_EXPAND_PADDING);
    box_lin.pack_start(frame_disk_lin, Gtk::PACK_EXPAND_PADDING);
    box_lin.pack_start(bar_lin, Gtk::PACK_EXPAND_PADDING);
    box_lin.pack_start(but_lin, Gtk::PACK_EXPAND_PADDING);
    box.set_border_width(10);

    // init separator
    sep.set_size_request(5, 200);

    // init images
    img_win.set("img/win10.png");
    img_win.set_margin_bottom(10);
    img_lin.set("img/ubuntu.png");
    img_lin.set_margin_bottom(10);

    // init textview
    view_win.set_editable(false);
    view_lin.set_editable(false);
    view_disk_win.set_editable(false);
    view_disk_win.set_left_margin(5);
    view_disk_lin.set_editable(false);
    view_disk_lin.set_left_margin(5);
    
    // init bar
    bar_win.set_halign(Gtk::ALIGN_CENTER);
    bar_win.set_valign(Gtk::ALIGN_CENTER);
    bar_win.property_show_text() = true;
    bar_win.set_margin_bottom(10);
    bar_lin.set_halign(Gtk::ALIGN_CENTER);
    bar_lin.set_valign(Gtk::ALIGN_CENTER);
    bar_lin.property_show_text() = true;
    bar_lin.set_margin_bottom(10);

    add(box);

    // init frame
    frame_disk_win.add(view_disk_win);
    frame_disk_win.set_label("Disk");
    frame_disk_win.set_margin_bottom(10);
    frame_disk_lin.add(view_disk_lin);
    frame_disk_lin.set_label("Disk");
    frame_disk_lin.set_margin_bottom(10);

    // init button
    but_win.set_label("Open Windows Dir");
    but_win.signal_clicked().connect(sigc::mem_fun(*this, &MainPanel::but_win_event));
    but_lin.set_label("Open Linux Dir");
    but_lin.signal_clicked().connect(sigc::mem_fun(*this, &MainPanel::but_lin_event));

    // initialize information
    struct utsname utsname_info;
    uname(&utsname_info);
    info_lin.init(utsname_info.sysname, utsname_info.release);
    info_win.init("Windows 10", "Version 1909");
    textbuff_win->set_text(info_win.return_info(1).str());
    view_win.set_buffer(textbuff_win);
    textbuff_lin->set_text(info_lin.return_info(1).str());
    view_lin.set_buffer(textbuff_lin);
    updateInfo();

    // include CSS
    cssProvider->load_from_path("theme.css");
    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    // create slot
    int timeout = 5000; // apx. 5s
    sigc::slot<bool>my_slot = sigc::mem_fun(*this, &MainPanel::updateInfo);

    // connect slot
    Glib::signal_timeout().connect(my_slot, timeout);
    show_all_children();
}

MainPanel::~MainPanel() {}

bool MainPanel::updateInfo() {
    // retrieve disk space info
    info_lin.update("/");
    info_win.update("/media/andrew-gan/Acer");

    // update frame textview
    textbuff_disk_win->set_text(info_win.return_info(0).str());
    view_disk_win.set_buffer(textbuff_disk_win);
    textbuff_disk_lin->set_text(info_lin.return_info(0).str());
    view_disk_lin.set_buffer(textbuff_disk_lin);

    // update prog bar and text
    ostringstream oss;
    bar_win.set_fraction(1 - float(info_win.get_info(2)) / info_win.get_info(3));
    oss << fixed << setprecision(1) << bar_win.get_fraction() * 100;
    bar_win.set_text(oss.str() + " % used");
    oss.str(string());
    bar_lin.set_fraction(1 - float(info_lin.get_info(2)) / info_lin.get_info(3));
    oss << fixed << setprecision(1) << bar_lin.get_fraction() * 100;
    bar_lin.set_text(oss.str() + " % used");

    // return true for continued iteration
    return true;
}

void MainPanel::but_lin_event() {
    system("nautilus /");
}

void MainPanel::but_win_event() {
    system("nautilus /media/andrew-gan/Acer");
}