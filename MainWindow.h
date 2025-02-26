#include <gtkmm.h>

class MainWindow : public Gtk::Window
{
  public:
    MainWindow();
    virtual ~MainWindow();
    void SetUpBasicMargins(Gtk::Widget* objectToModify);

  protected:
    //Child widgets:
    Gtk::Grid main_Grid;
    Gtk::ScrolledWindow leftScrollWindow;
    Gtk::Box boxInLeftScroll {Gtk::Orientation::VERTICAL, 10};
    Gtk::Box middleWindow;
    Gtk::ScrolledWindow rightScrollWindow;
    Gtk::Box boxInRightScroll {Gtk::Orientation::VERTICAL, 10};

  private:
    // Signal handlers:
    void handleAddWidgetGesture(int n_press, double x, double y);
    Glib::RefPtr<Gtk::GestureClick> clickGestureDetector;// listen for mouse clicks
    // child methods
    void removeWidgetByName(const Glib::ustring& id);
    void addDeleteButtonToWidget(Gtk::Widget* newWidget);
};