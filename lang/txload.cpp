/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/*
 * Tool to find differences between translations (can be used to help
 * merging them into one). See usage string, below, for details.
 *
 * The tool can be used when there are multiple translation files
 * for a single language (e.g. Spanish) which need to be reconciled.
 * Then running `txload file0.ts file1.ts ...` will produce a
 * human-readable overview of what is translated and where the
 * differences in translation are.
 */

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
// #include <QList>

#include <QDomDocument>

static const char usage[] = "Usage: txload <origin> [<alternate> ...]\n"
                            "\n"
                            "Reads a .ts source file <origin> and zero or more .ts <alternate>\n"
                            "files, and does a comparison between the translations. Source (English)\n"
                            "strings that are untranslated are flagged in each of the translation\n"
                            "files, while differences in the translations are themselves also shown.\n"
                            "\n"
                            "Outputs to stdout a human-readable list of differences between the\n"
                            "translations.\n";

bool
load_file( const char* filename, QDomDocument& doc )
{
    QFile file( filename );
    QString err;
    int err_line, err_column;
    if ( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Could not open" << filename;
        return false;
    }
    QByteArray ba( file.read( 1024 * 1024 ) );
    qDebug() << "Read" << ba.length() << "bytes from" << filename;

    if ( !doc.setContent( ba, &err, &err_line, &err_column ) )
    {
        qDebug() << "Could not read" << filename << ':' << err_line << ':' << err_column << ' ' << err;
        file.close();
        return false;
    }
    file.close();

    return true;
}

QDomElement
find_context( QDomDocument& doc, const QString& name )
{
    QDomElement top = doc.documentElement();
    QDomNode n = top.firstChild();
    while ( !n.isNull() )
    {
        if ( n.isElement() )
        {
            QDomElement e = n.toElement();
            if ( ( e.tagName() == "context" ) && ( e.firstChildElement( "name" ).text() == name ) )
            {
                return e;
            }
        }
        n = n.nextSibling();
    }

    return QDomElement();
}

QDomElement
find_message( QDomElement& context, const QString& source )
{
    QDomNode n = context.firstChild();
    while ( !n.isNull() )
    {
        if ( n.isElement() )
        {
            QDomElement e = n.toElement();
            if ( e.tagName() == "message" )
            {
                QString msource = e.firstChildElement( "source" ).text();
                if ( msource == source )
                {
                    return e;
                }
            }
        }
        n = n.nextSibling();
    }
    return QDomElement();
}

bool
merge_into( QDomElement& origin, QDomElement& alternate )
{
    QDomNode n = alternate.firstChild();
    while ( !n.isNull() )
    {
        if ( n.isElement() )
        {
            QDomElement alternateMessage = n.toElement();
            if ( alternateMessage.tagName() == "message" )
            {
                QString alternateSourceText = alternateMessage.firstChildElement( "source" ).text();
                QString alternateTranslationText = alternateMessage.firstChildElement( "translation" ).text();
                QDomElement originMessage = find_message( origin, alternateSourceText );
                if ( originMessage.isNull() )
                {
                    qDebug() << "No origin translation for" << alternateSourceText;
                    return false;
                }

                QString originSourceText = originMessage.firstChildElement( "source" ).text();
                QString originTranslationText = originMessage.firstChildElement( "translation" ).text();

                if ( alternateSourceText != originSourceText )
                {
                    qDebug() << "Mismatch for messages\n" << alternateSourceText << '\n' << originSourceText;
                    return false;
                }
                if ( !alternateTranslationText.isEmpty() && ( alternateTranslationText != originTranslationText ) )
                {
                    qDebug() << "\n\n\nSource:" << alternateSourceText << "\nTL1:" << originTranslationText
                             << "\nTL2:" << alternateTranslationText;
                }
            }
        }
        n = n.nextSibling();
    }

    return true;
}


bool
merge_into( QDomDocument& originDocument, QDomElement& context )
{
    QDomElement name = context.firstChildElement( "name" );
    if ( name.isNull() )
    {
        return false;
    }

    QString contextname = name.text();
    QDomElement originContext = find_context( originDocument, contextname );
    if ( originContext.isNull() )
    {
        qDebug() << "Origin document has no context" << contextname;
        return false;
    }

    return merge_into( originContext, context );
}

bool
merge_into( QDomDocument& originDocument, QDomDocument& alternateDocument )
{
    QDomElement top = alternateDocument.documentElement();
    QDomNode n = top.firstChild();
    while ( !n.isNull() )
    {
        if ( n.isElement() )
        {
            QDomElement e = n.toElement();
            if ( e.tagName() == "context" )
                if ( !merge_into( originDocument, e ) )
                {
                    return false;
                }
        }
        n = n.nextSibling();
    }

    return true;
}

int
main( int argc, char** argv )
{
    QCoreApplication a( argc, argv );

    if ( argc < 2 )
    {
        qWarning() << usage;
        return 1;
    }

    QDomDocument originDocument( "origin" );
    if ( !load_file( argv[ 1 ], originDocument ) )
    {
        return 1;
    }

    for ( int i = 2; i < argc; ++i )
    {
        QDomDocument alternateDocument( "alternate" );
        if ( !load_file( argv[ i ], alternateDocument ) )
        {
            return 1;
        }
        if ( !merge_into( originDocument, alternateDocument ) )
        {
            return 1;
        }
    }

    QString outfilename( argv[ 1 ] );
    outfilename.append( ".new" );
    QFile outfile( outfilename );
    if ( !outfile.open( QIODevice::WriteOnly ) )
    {
        qDebug() << "Could not open" << outfilename;
        return 1;
    }

    outfile.write( originDocument.toString( 4 ).toUtf8() );
    outfile.close();

    return 0;
}
