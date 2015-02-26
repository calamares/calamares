/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *
 *   Originally from https://github.com/snowwlex/QtWaitingSpinner
 *   Copyright 2012, Alex Turkin
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

#ifndef QTWAITINGSPINNER_H
#define QTWAITINGSPINNER_H

#include "UiDllMacro.h"

#include <QtCore/QTimer>

#include <QWidget>
#include <QColor>

class UIDLLEXPORT QtWaitingSpinner : public QWidget {
	Q_OBJECT

public:
	explicit QtWaitingSpinner(int linesNumber = 12, int length = 7, int width = 5, int radius = 10, QWidget* parent = 0);

public Q_SLOTS:
	void start();
	void finish();

public:
	void setLinesNumber(int linesNumber);
	void setLength(int length);
	void setWidth(int width);
	void setRadius(int radius);
	void setRoundness(qreal roundness);
	void setColor(QColor color);
	void setSpeed(qreal speed);
	void setTrail(int trail);
	void setOpacity(int minOpacity);

private Q_SLOTS:
	void rotate();
	void updateSize();
	void updateTimer();

protected:
	void paintEvent(QPaintEvent* ev);

private:
	static int countTimeout(int lines, qreal speed);
	static int lineDistance(int from, int to, int lines);
	static QColor countTrailColor(int distance, int lines, int trail, int minOpacity, QColor color);

private:
	int myLinesNumber;
	int myLength;
	int myWidth;
	int myRadius;
	qreal myRoundness; //0..100
	QColor myColor;
	qreal mySpeed; // in rounds per second
	int myTrail;
	int myOpacity;

private:
	QTimer* myTimer;
	int myCurrentCounter;
};

#endif // QTWAITINGSPINNER_H
