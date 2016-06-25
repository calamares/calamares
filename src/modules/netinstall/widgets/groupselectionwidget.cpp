#include "groupselectionwidget.h"

#include <QtDebug>

GroupSelectionWidget::GroupSelectionWidget( QString name, QString description, QStringList packages, QWidget* parent ) :
    QWidget( parent ),
    m_isToggled( false )
{
    ui.setupUi( this );

    connect( ui.group, SIGNAL( toggled( bool ) ), this, SLOT( toggleGroup( bool ) ) );

    ui.group->setText( name );
    ui.description->setText( description );
    const int columns = 4;
    const int rows = ( packages.size() - 1 ) / columns + 1;
    ui.packageview->setRowCount( rows );
    ui.packageview->setColumnCount( columns );

    ui.packageview->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    int r = 0, c = 0;
    for ( int i = 0; i < packages.size(); ++i )
    {
        ui.packageview->setItem( r++,c, new QTableWidgetItem( packages.at( i ) ) );
        if ( r == ui.packageview->rowCount() )
        {
            ++c;
            r = 0;
        }
    }

    int rowsShown = 6;
    rowsShown = rows < rowsShown ? rows : 6;
    ui.packageview->setFixedHeight( rowsShown * ui.packageview->rowHeight( 0 ) );
    ui.packageview->hide();
}

void GroupSelectionWidget::toggleGroup( bool isToggled )
{
    m_isToggled = isToggled;
    emit toggled( isToggled );
}

bool GroupSelectionWidget::isToggled() const
{
    return m_isToggled;
}
