#include "widget/main_window.hpp"

#include <QApplication>


int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    MainWindow widget;
    widget.show();

    return app.exec();
}
