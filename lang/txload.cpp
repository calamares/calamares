/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

/*
 * Tool to find differences between translations (can be used to help
 * merging them into one). See usage string, below, for details.
 */

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QList>

#include <QDomDocument>

static const char usage[] = "Usage: txload <master> [<subsidiary> ...]\n"
    "\n"
    "Reads a .ts source file <master> and zero or more .ts <subsidiary>\n"
    "files, and does a comparison between the translations. Source (English)\n"
    "strings that are untranslated are flagged in each of the translation\n"
    "files, while differences in the translations are themselves also shown.\n"
    "\n"
    "Outputs to stdout a human-readable list of differences between the\n"
    "translations.\n";

bool load_file(const char* filename, QDomDocument& doc)
{
    QFile file(filename);
    QString err;
    int err_line, err_column;
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open" << filename;
        return false;
    }
    QByteArray ba( file.read(1024 * 1024) );
    qDebug() << "Read" << ba.length() << "bytes from" << filename;

    if (!doc.setContent(ba, &err, &err_line, &err_column)) {
        qDebug() << "Could not read" << filename << ':' << err_line << ':' << err_column << ' ' << err;
        file.close();
        return false;
    }
    file.close();

    return true;
}

QDomElement find_context(QDomDocument& doc, const QString& name)
{
    QDomElement top = doc.documentElement();
    QDomNode n = top.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if ( ( e.tagName() == "context" ) && ( e.firstChildElement( "name" ).text() == name ) )
                return e;
        }
        n = n.nextSibling();
    }

    return QDomElement();
}

QDomElement find_message(QDomElement& context, const QString& source)
{
    QDomNode n = context.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if ( e.tagName() == "message" )
            {
                QString msource = e.firstChildElement( "source" ).text();
                if ( msource == source )
                    return e;
            }
        }
        n = n.nextSibling();
    }
    return QDomElement();
}

bool merge_into(QDomElement& master, QDomElement& sub)
{
    QDomNode n = sub.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if ( e.tagName() == "message" )
            {
                QString source = e.firstChildElement( "source" ).text();
                QString translation = e.firstChildElement( "translation" ).text();
                QDomElement masterTranslation = find_message( master, source );
                if ( masterTranslation.isNull() )
                {
                    qDebug() << "No master translation for" << source;
                    return false;
                }

                QString msource = masterTranslation.firstChildElement( "source" ).text();
                QString mtranslation = masterTranslation.firstChildElement( "translation" ).text();

                if ( source != msource )
                {
                    qDebug() << "Mismatch for messages\n" << source << '\n' << msource;
                    return false;
                }
                if ( !translation.isEmpty() && ( translation != mtranslation ) )
                {
                    qDebug() << "\n\n\nSource:" << source << "\nTL1:" << mtranslation << "\nTL2:" << translation;
                }
            }
        }
        n = n.nextSibling();
    }

    return true;
}



bool merge_into(QDomDocument& master, QDomElement& context)
{
    QDomElement name = context.firstChildElement( "name" );
    if ( name.isNull() )
        return false;

    QString contextname = name.text();
    QDomElement masterContext = find_context( master, contextname );
    if ( masterContext.isNull() )
    {
        qDebug() << "Master document has no context" << contextname;
        return false;
    }

    return merge_into( masterContext, context );
}

bool merge_into(QDomDocument& master, QDomDocument& sub)
{
    QDomElement top = sub.documentElement();
    QDomNode n = top.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if ( e.tagName() == "context" )
                if ( !merge_into( master, e ) )
                    return false;
        }
        n = n.nextSibling();
    }

    return true;
}

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    if (argc < 2)
    {
        qWarning() << usage;
        return 1;
    }

    QDomDocument doc("master");
    if ( !load_file(argv[1], doc) )
        return 1;

    for (int i = 2; i < argc; ++i)
    {
        QDomDocument subdoc("sub");
        if ( !load_file(argv[i], subdoc) )
            return 1;
        if ( !merge_into( doc, subdoc ) )
            return 1;
    }

    QString outfilename( argv[1] );
    outfilename.append( ".new" );
    QFile outfile(outfilename);
    if (!outfile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open" << outfilename;
        return 1;
    }

    outfile.write( doc.toString(4).toUtf8() );
    outfile.close();

    return 0;
}
