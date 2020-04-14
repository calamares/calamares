/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2020, Camilo Higuita <milo.h@aol.com> *
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Config.h"

#include "SetKeyboardLayoutJob.h"
#include "keyboardwidget/keyboardpreview.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QApplication>
#include <QProcess>
#include <QTimer>

KeyboardModelsModel::KeyboardModelsModel( QObject* parent )
    : QAbstractListModel( parent )
{
    detectModels();
}

void
KeyboardModelsModel::detectModels()
{
    beginResetModel();
    const auto models = KeyboardGlobal::getKeyboardModels();
    auto index = -1;
    for ( const auto& key : models.keys() )
    {
        index++;
        m_list << QMap< QString, QString > { { "label", key }, { "key", models[ key ] } };
        if ( models[ key ] == "pc105" )
        {
            this->setCurrentIndex( index );
        }
    }
    endResetModel();
}

void
KeyboardModelsModel::refresh()
{
    m_list.clear();
    setCurrentIndex( -1 );
    detectModels();
}

QVariant
KeyboardModelsModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    const auto item = m_list.at( index.row() );
    return role == Qt::DisplayRole ? item[ "label" ] : item[ "key" ];
}

int
KeyboardModelsModel::rowCount( const QModelIndex& ) const
{
    return m_list.count();
}

QHash< int, QByteArray >
KeyboardModelsModel::roleNames() const
{
    return { { Qt::DisplayRole, "label" }, { Qt::UserRole, "key" } };
}

int
KeyboardModelsModel::currentIndex() const
{
    return m_currentIndex;
}

const QMap< QString, QString >
KeyboardModelsModel::item( const int& index ) const
{
    if ( index >= m_list.count() || index < 0 )
    {
        return QMap< QString, QString >();
    }

    return m_list.at( index );
}

const QMap< QString, QString >
KeyboardVariantsModel::item( const int& index ) const
{
    if ( index >= m_list.count() || index < 0 )
    {
        return QMap< QString, QString >();
    }

    return m_list.at( index );
}

void
KeyboardModelsModel::setCurrentIndex( const int& index )
{
    if ( index >= m_list.count() || index < 0 )
    {
        return;
    }

    m_currentIndex = index;
    emit currentIndexChanged( m_currentIndex );
}

KeyboardVariantsModel::KeyboardVariantsModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

int
KeyboardVariantsModel::currentIndex() const
{
    return m_currentIndex;
}

void
KeyboardVariantsModel::setCurrentIndex( const int& index )
{
    if ( index >= m_list.count() || index < 0 )
    {
        return;
    }

    m_currentIndex = index;
    emit currentIndexChanged( m_currentIndex );
}

QVariant
KeyboardVariantsModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    const auto item = m_list.at( index.row() );
    return role == Qt::DisplayRole ? item[ "label" ] : item[ "key" ];
}

int
KeyboardVariantsModel::rowCount( const QModelIndex& ) const
{
    return m_list.count();
}

QHash< int, QByteArray >
KeyboardVariantsModel::roleNames() const
{
    return { { Qt::DisplayRole, "label" }, { Qt::UserRole, "key" } };
}

void
KeyboardVariantsModel::setVariants( QMap< QString, QString > variants )
{
    m_list.clear();
    beginResetModel();
    for ( const auto& key : variants.keys() )
    {
        const auto item = QMap< QString, QString > { { "label", key }, { "key", variants[ key ] } };
        m_list << item;
    }
    endResetModel();
}

/* Returns stringlist with suitable setxkbmap command-line arguments
 * to set the given @p layout and @p variant.
 */
static inline QStringList
xkbmap_args( const QString& layout, const QString& variant )
{
    QStringList r { "-layout", layout };
    if ( !variant.isEmpty() )
    {
        r << "-variant" << variant;
    }
    return r;
}

Config::Config( QObject* parent )
    : QObject( parent )
    , m_keyboardModelsModel( new KeyboardModelsModel( this ) )
    , m_keyboardLayoutsModel( new KeyboardLayoutModel( this ) )
    , m_keyboardVariantsModel( new KeyboardVariantsModel( this ) )
{
    m_setxkbmapTimer.setSingleShot( true );

    // Connect signals and slots
    connect( m_keyboardModelsModel, &KeyboardModelsModel::currentIndexChanged, [&]( int index ) {
        m_selectedModel = m_keyboardModelsModel->item( index ).value( "key", "pc105" );
        //                      Set Xorg keyboard model
        QProcess::execute( "setxkbmap", QStringList { "-model", m_selectedModel } );
        emit prettyStatusChanged();
    } );

    connect( m_keyboardLayoutsModel, &KeyboardLayoutModel::currentIndexChanged, [&]( int index ) {
        m_selectedLayout = m_keyboardLayoutsModel->item( index ).first;
        updateVariants( QPersistentModelIndex( m_keyboardLayoutsModel->index( index ) ) );
        emit prettyStatusChanged();
    } );

    connect( m_keyboardVariantsModel, &KeyboardVariantsModel::currentIndexChanged, [&]( int index ) {
        m_selectedVariant = m_keyboardVariantsModel->item( index )[ "key" ];

        // Set Xorg keyboard layout
        if ( m_setxkbmapTimer.isActive() )
        {
            m_setxkbmapTimer.stop();
            m_setxkbmapTimer.disconnect( this );
        }

        connect( &m_setxkbmapTimer, &QTimer::timeout, this, [=] {
            QProcess::execute( "setxkbmap", xkbmap_args( m_selectedLayout, m_selectedVariant ) );
            cDebug() << "xkbmap selection changed to: " << m_selectedLayout << '-' << m_selectedVariant;
            m_setxkbmapTimer.disconnect( this );
        } );
        m_setxkbmapTimer.start( QApplication::keyboardInputInterval() );
        emit prettyStatusChanged();
    } );
}

KeyboardModelsModel*
Config::keyboardModels() const
{
    return m_keyboardModelsModel;
}

KeyboardLayoutModel*
Config::keyboardLayouts() const
{
    return m_keyboardLayoutsModel;
}

KeyboardVariantsModel*
Config::keyboardVariants() const
{
    return m_keyboardVariantsModel;
}

static QPersistentModelIndex
findLayout( const KeyboardLayoutModel* klm, const QString& currentLayout )
{
    QPersistentModelIndex currentLayoutItem;

    for ( int i = 0; i < klm->rowCount(); ++i )
    {
        QModelIndex idx = klm->index( i );
        if ( idx.isValid() && idx.data( KeyboardLayoutModel::KeyboardLayoutKeyRole ).toString() == currentLayout )
        {
            currentLayoutItem = idx;
        }
    }

    return currentLayoutItem;
}

void
Config::init()
{
    //### Detect current keyboard layout and variant
    QString currentLayout;
    QString currentVariant;
    QProcess process;
    process.start( "setxkbmap", QStringList() << "-print" );

    if ( process.waitForFinished() )
    {
        const QStringList list = QString( process.readAll() ).split( "\n", QString::SkipEmptyParts );

        for ( QString line : list )
        {
            line = line.trimmed();
            if ( !line.startsWith( "xkb_symbols" ) )
            {
                continue;
            }

            line = line.remove( "}" ).remove( "{" ).remove( ";" );
            line = line.mid( line.indexOf( "\"" ) + 1 );

            QStringList split = line.split( "+", QString::SkipEmptyParts );
            if ( split.size() >= 2 )
            {
                currentLayout = split.at( 1 );

                if ( currentLayout.contains( "(" ) )
                {
                    int parenthesisIndex = currentLayout.indexOf( "(" );
                    currentVariant = currentLayout.mid( parenthesisIndex + 1 ).trimmed();
                    currentVariant.chop( 1 );
                    currentLayout = currentLayout.mid( 0, parenthesisIndex ).trimmed();
                }

                break;
            }
        }
    }

    //### Layouts and Variants
    QPersistentModelIndex currentLayoutItem = findLayout( m_keyboardLayoutsModel, currentLayout );
    if ( !currentLayoutItem.isValid() && ( ( currentLayout == "latin" ) || ( currentLayout == "pc" ) ) )
    {
        currentLayout = "us";
        currentLayoutItem = findLayout( m_keyboardLayoutsModel, currentLayout );
    }

    // Set current layout and variant
    if ( currentLayoutItem.isValid() )
    {
        m_keyboardLayoutsModel->setCurrentIndex( currentLayoutItem.row() );
        updateVariants( currentLayoutItem, currentVariant );
    }

    // Default to the first available layout if none was set
    // Do this after unblocking signals so we get the default variant handling.
    if ( !currentLayoutItem.isValid() && m_keyboardLayoutsModel->rowCount() > 0 )
    {
        m_keyboardLayoutsModel->setCurrentIndex( m_keyboardLayoutsModel->index( 0 ).row() );
    }
}

QString
Config::prettyStatus() const
{
    QString status;
    status += tr( "Set keyboard model to %1.<br/>" )
                  .arg( m_keyboardModelsModel->item( m_keyboardModelsModel->currentIndex() )[ "label" ] );

    QString layout = m_keyboardLayoutsModel->item( m_keyboardLayoutsModel->currentIndex() ).second.description;
    QString variant = m_keyboardVariantsModel->currentIndex() >= 0
        ? m_keyboardVariantsModel->item( m_keyboardVariantsModel->currentIndex() )[ "label" ]
        : QString( "<default>" );
    status += tr( "Set keyboard layout to %1/%2." ).arg( layout, variant );

    return status;
}

Calamares::JobList
Config::createJobs( const QString& xOrgConfFileName, const QString& convertedKeymapPath, bool writeEtcDefaultKeyboard )
{
    QList< Calamares::job_ptr > list;

    Calamares::Job* j = new SetKeyboardLayoutJob( m_selectedModel,
                                                  m_selectedLayout,
                                                  m_selectedVariant,
                                                  xOrgConfFileName,
                                                  convertedKeymapPath,
                                                  writeEtcDefaultKeyboard );
    list.append( Calamares::job_ptr( j ) );

    return list;
}

void
Config::guessLayout( const QStringList& langParts )
{
    bool foundCountryPart = false;
    for ( auto countryPart = langParts.rbegin(); !foundCountryPart && countryPart != langParts.rend(); ++countryPart )
    {
        cDebug() << Logger::SubEntry << "looking for locale part" << *countryPart;
        for ( int i = 0; i < m_keyboardLayoutsModel->rowCount(); ++i )
        {
            QModelIndex idx = m_keyboardLayoutsModel->index( i );
            QString name
                = idx.isValid() ? idx.data( KeyboardLayoutModel::KeyboardLayoutKeyRole ).toString() : QString();
            if ( idx.isValid() && ( name.compare( *countryPart, Qt::CaseInsensitive ) == 0 ) )
            {
                cDebug() << Logger::SubEntry << "matched" << name;
                m_keyboardLayoutsModel->setCurrentIndex( i );
                foundCountryPart = true;
                break;
            }
        }
        if ( foundCountryPart )
        {
            ++countryPart;
            if ( countryPart != langParts.rend() )
            {
                cDebug() << "Next level:" << *countryPart;
                for ( int variantnumber = 0; variantnumber < m_keyboardVariantsModel->rowCount(); ++variantnumber )
                {
                    if ( m_keyboardVariantsModel->item( variantnumber )[ "key" ].compare( *countryPart,
                                                                                          Qt::CaseInsensitive ) )
                    {
                        m_keyboardVariantsModel->setCurrentIndex( variantnumber );
                        cDebug() << Logger::SubEntry << "matched variant"
                                 << m_keyboardVariantsModel->item( variantnumber )[ "key" ] << ' '
                                 << m_keyboardVariantsModel->item( variantnumber )[ "key" ];
                    }
                }
            }
        }
    }
}

void
Config::onActivate()
{
    /* Guessing a keyboard layout based on the locale means
     * mapping between language identifiers in <lang>_<country>
     * format to keyboard mappings, which are <country>_<layout>
     * format; in addition, some countries have multiple languages,
     * so fr_BE and nl_BE want different layouts (both Belgian)
     * and sometimes the language-country name doesn't match the
     * keyboard-country name at all (e.g. Ellas vs. Greek).
     *
     * This is a table of language-to-keyboard mappings. The
     * language identifier is the key, while the value is
     * a string that is used instead of the real language
     * identifier in guessing -- so it should be something
     * like <layout>_<country>.
     */
    static constexpr char arabic[] = "ara";
    static const auto specialCaseMap = QMap< std::string, std::string >( {
        /* Most Arab countries map to Arabic keyboard (Default) */
        { "ar_AE", arabic },
        { "ar_BH", arabic },
        { "ar_DZ", arabic },
        { "ar_EG", arabic },
        { "ar_IN", arabic },
        { "ar_IQ", arabic },
        { "ar_JO", arabic },
        { "ar_KW", arabic },
        { "ar_LB", arabic },
        { "ar_LY", arabic },
        /* Not Morocco: use layout ma */
        { "ar_OM", arabic },
        { "ar_QA", arabic },
        { "ar_SA", arabic },
        { "ar_SD", arabic },
        { "ar_SS", arabic },
        /* Not Syria: use layout sy */
        { "ar_TN", arabic },
        { "ar_YE", arabic },
        { "ca_ES", "cat_ES" }, /* Catalan */
        { "as_ES", "ast_ES" }, /* Asturian */
        { "en_CA", "eng_CA" }, /* Canadian English */
        { "el_CY", "gr" }, /* Greek in Cyprus */
        { "el_GR", "gr" }, /* Greek in Greeze */
        { "ig_NG", "igbo_NG" }, /* Igbo in Nigeria */
        { "ha_NG", "hausa_NG" } /* Hausa */
    } );

    // Try to preselect a layout, depending on language and locale
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QString lang = gs->value( "localeConf" ).toMap().value( "LANG" ).toString();

    cDebug() << "Got locale language" << lang;
    if ( !lang.isEmpty() )
    {
        // Chop off .codeset and @modifier
        int index = lang.indexOf( '.' );
        if ( index >= 0 )
        {
            lang.truncate( index );
        }
        index = lang.indexOf( '@' );
        if ( index >= 0 )
        {
            lang.truncate( index );
        }

        lang.replace( '-', '_' );  // Normalize separators
    }
    if ( !lang.isEmpty() )
    {
        std::string lang_s = lang.toStdString();
        if ( specialCaseMap.contains( lang_s ) )
        {
            QString newLang = QString::fromStdString( specialCaseMap.value( lang_s ) );
            cDebug() << Logger::SubEntry << "special case language" << lang << "becomes" << newLang;
            lang = newLang;
        }
    }
    if ( !lang.isEmpty() )
    {
        const auto langParts = lang.split( '_', QString::SkipEmptyParts );

        // Note that this his string is not fit for display purposes!
        // It doesn't come from QLocale::nativeCountryName.
        QString country = QLocale::countryToString( QLocale( lang ).country() );
        cDebug() << Logger::SubEntry << "extracted country" << country << "::" << langParts;

        guessLayout( langParts );
    }
}

void
Config::finalize()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !m_selectedLayout.isEmpty() )
    {
        gs->insert( "keyboardLayout", m_selectedLayout );
        gs->insert( "keyboardVariant", m_selectedVariant );  //empty means default variant
    }

    //FIXME: also store keyboard model for something?
}

void
Config::updateVariants( const QPersistentModelIndex& currentItem, QString currentVariant )
{
    const auto variants = m_keyboardLayoutsModel->item( currentItem.row() ).second.variants;
    m_keyboardVariantsModel->setVariants( variants );

    auto index = -1;
    for ( const auto& key : variants.keys() )
    {
        index++;
        if ( variants[ key ] == currentVariant )
        {
            m_keyboardVariantsModel->setCurrentIndex( index );
            return;
        }
    }
}
