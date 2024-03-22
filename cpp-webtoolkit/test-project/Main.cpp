#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WCalendar.h>
#include <Wt/WDate.h>
#include <Wt/WTimeEdit.h>
#include <Wt/WLabel.h>
#include <Wt/WTemplate.h>
#include <Wt/WString.h>

class HelloApplication : public Wt::WApplication
{
  public:
    HelloApplication(const Wt::WEnvironment& env);

  private:
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
{
  setTitle("WT Example");
  setTheme(std::make_unique<Wt::WBootstrap5Theme>());
  messageResourceBundle().use(WApplication::appRoot() + "editSide-template");

  auto result = std::make_unique<Wt::WTemplate>(Wt::WString::tr("editSide-template"));

  auto edit = std::make_unique<Wt::WLineEdit>("Username");
  edit->setStyleClass("span2");
  result->bindWidget("name", std::move(edit));

  edit = std::make_unique<Wt::WLineEdit>();
  edit->setStyleClass("span2");
  result->bindWidget("amount1", std::move(edit));

  edit = std::make_unique<Wt::WLineEdit>();
  edit->setStyleClass("span2");
  result->bindWidget("amount2", std::move(edit));

  root()->addWidget(std::move(result));
}

int main(int argc, char** argv)
{
  return Wt::WRun(
    argc,
    argv,
    [](const Wt::WEnvironment& env) { //
      return std::make_unique<HelloApplication>(env);
    }
  );
}

// PATH=$PREFIX/bin:$PATH LD_LIBRARY_PATH=$PREFIX/lib:$LD_LIBRARY_PATH DYLD_LIBRARY_PATH=$PREFIX/lib:$DYLD_LIBRARY_PATH $EXAMPLEPREFIX/@EXAMPLENAME@.wt --docroot $EXAMPLEPREFIX/@DOCROOTSUBFOLDER@ --approot $EXAMPLEPREFIX/@APPROOTSUBFOLDER@ --http-port 8080 --http-address 0.0.0.0 --resources-dir $PREFIX/share/Wt/resources $@
// ./CppWebToolKit --docroot=. --http-address 0.0.0.0 --http-port 5000 --resources-dir /usr/share/Wt/resources
