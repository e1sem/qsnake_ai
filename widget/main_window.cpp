#include "main_window.hpp"

#include <QGraphicsView>
#include <QGraphicsScene>

/************************************************************************/

MainWindow::MainWindow( QWidget* parent )
    :   QMainWindow( parent )
{
    setWindowTitle( "Snake" );
    setFixedSize( 490, 490 );

    initGraphicView();
}

/************************************************************************/

void MainWindow::initGraphicView()
{
    m_graphicScene = new QGraphicsScene( this );
    m_graphicScene->setSceneRect( 0, 0, 450, 450 );

    m_graphicView = new QGraphicsView( m_graphicScene, this );
    m_graphicView->setGeometry( 20, 20, 450, 450 );
    m_graphicView->setFrameStyle( 0 );

    QBrush brush;
    brush.setStyle( Qt::SolidPattern );
    brush.setColor( Qt::lightGray );

    m_graphicView->setBackgroundBrush( brush );
}

/************************************************************************/
