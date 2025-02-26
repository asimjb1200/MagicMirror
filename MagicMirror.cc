#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow()
{
 /* Set some window properties */
  set_title("Frame Example");
  set_size_request(800, 800);
  // Force dark theme
  auto provider = Gtk::CssProvider::create();
  provider->load_from_data("window { background-color: #2E2E2E; color: #FFFFFF; }");

  auto screen = Gdk::Display::get_default();
  auto style_context = get_style_context();
  style_context->add_provider_for_display(screen, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  /* Sets the margin around the frame. */
  //main_Grid.set_margin(10);

  /* Set the frames label */
  main_Grid.set_name("Gtk::Frame Widget");

  /* create the box that will go into the left scroll window */

  auto button = Gtk::make_managed<Gtk::Button>("Left Pane Header");
  auto button2 = Gtk::make_managed<Gtk::Button>("Left Pane Notice");
  boxInLeftScroll.append(*button);
  boxInLeftScroll.append(*button2);
  boxInLeftScroll.set_vexpand();
  leftScrollWindow.set_child(boxInLeftScroll);
  leftScrollWindow.set_hexpand(true);
  leftScrollWindow.set_vexpand(true);

  /* create the box that will go into the right scroll window */
  auto rightbutton = Gtk::make_managed<Gtk::Button>("Right Pane Header");
  auto rightbutton2 = Gtk::make_managed<Gtk::Button>("Right Pane Notice");
  boxInRightScroll.append(*rightbutton);
  boxInRightScroll.append(*rightbutton2);
  rightScrollWindow.set_child(boxInRightScroll);
  rightScrollWindow.set_hexpand(true);
  //rightScrollWindow.set_vexpand(true);

  /* create the box that will go into the middle window */
  Gtk::Frame* nameGreetingFrame = Gtk::make_managed<Gtk::Frame>();
  nameGreetingFrame->set_label("Hello Asim, how are you today?");
  nameGreetingFrame->set_label_align(Gtk::Align::CENTER);
  nameGreetingFrame->set_size_request(100, 20);

  SetUpBasicMargins(nameGreetingFrame);

  auto addWidgetButton = Gtk::make_managed<Gtk::Button>("\u2795 Add Item");
  SetUpBasicMargins(addWidgetButton);

  clickGestureDetector = Gtk::GestureClick::create();
  clickGestureDetector->set_button(GDK_BUTTON_PRIMARY);
  clickGestureDetector->signal_pressed().connect(sigc::mem_fun(*this, &MainWindow::handleAddWidgetGesture));
  addWidgetButton->add_controller(clickGestureDetector);

  Gtk::Box* middleWindowBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
  middleWindowBox->append(*nameGreetingFrame);
  middleWindowBox->append(*addWidgetButton);

  middleWindow.append(*middleWindowBox);
  middleWindow.set_hexpand(true);
  middleWindow.set_vexpand(true);

  // Attach Widgets to Grid
  main_Grid.set_expand(true);
  main_Grid.attach(leftScrollWindow,  0, 0, 2, 1);  // Left: large
  main_Grid.attach(middleWindow,   2, 0, 4, 1);  // Middle: small
  main_Grid.attach(rightScrollWindow, 6, 0, 2, 1);  // Right: large
  
  set_child(main_Grid);
}

void MainWindow::SetUpBasicMargins(Gtk::Widget* objectToModify)
{
  objectToModify->set_margin_start(10);
  objectToModify->set_margin_end(10);
  objectToModify->set_margin_top(5);
  objectToModify->set_margin_bottom(5);
  objectToModify->set_hexpand();
}

void MainWindow::handleAddWidgetGesture(int n_press, double x, double y)
{
  std::cout << "Mouse pressed in first button: " << ", " << n_press << ", " << x << ", " << y << std::endl;
  auto newWidget = Gtk::make_managed<Gtk::Label>("New Item " + std::to_string(boxInLeftScroll.get_children().size() + 1));
  newWidget->set_size_request(50, 50);
  newWidget->set_hexpand();

  // Set a unique name
  std::string widget_id = "item_" + std::to_string(boxInLeftScroll.get_children().size() + 1);
  newWidget->set_name(widget_id);

  // add delete controller to the new widget
  addDeleteButtonToWidget(newWidget);

  // Add the widget to the box
  boxInLeftScroll.append(*newWidget);

  // Reset the gesture so it’s ready for the next click
  clickGestureDetector->reset();

  std::cout << "Added widget with ID: " << widget_id << std::endl;
}

void MainWindow::addDeleteButtonToWidget(Gtk::Widget* newWidget) {
  Glib::RefPtr<Gtk::GestureClick> clickGesture = Gtk::GestureClick::create();
  clickGesture->set_button(GDK_BUTTON_PRIMARY);
  auto widgetName = newWidget->get_name();
  clickGesture->signal_pressed().connect([this, widgetName](int n_press, double x, double y) {
    this->removeWidgetByName(widgetName);
  });
  newWidget->add_controller(clickGesture);
}

void MainWindow::removeWidgetByName(const Glib::ustring& id) {
    for (auto* child : boxInLeftScroll.get_children()) {
      if (child->get_name() == id) {
        boxInLeftScroll.remove(*child);
        std::cout << "Removed widget with ID: " << id << std::endl;
        return;  // Exit after removing
      }
    }
    std::cout << "Widget with ID: " << id << " not found!" << std::endl;
}


MainWindow::~MainWindow()
{
}

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  //Shows the window and returns when it is closed.
  return app->make_window_and_run<MainWindow>(argc, argv);
}