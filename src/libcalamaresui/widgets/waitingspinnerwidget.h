/*
 *   SPDX-FileCopyrightText: 2012-2014 Alexander Turkin
 *   SPDX-FileCopyrightText: 2014 William Hallatt
 *   SPDX-FileCopyrightText: 2015 Jacob Dawid
 *   SPDX-FileCopyrightText: 2018 huxingyi
 *   SPDX-License-Identifier: MIT
 */

/* Original Work Copyright (c) 2012-2014 Alexander Turkin
   Modified 2014 by William Hallatt
   Modified 2015 by Jacob Dawid

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

// Qt includes
#include <QColor>
#include <QTimer>
#include <QWidget>

class WaitingSpinnerWidget : public QWidget
{
    Q_OBJECT
public:
    /** @brief Constructor for "standard" widget behaviour
     *
     * Use this constructor if you wish to, e.g. embed your widget in another.
     */
    WaitingSpinnerWidget( QWidget* parent = nullptr,
                          bool centerOnParent = true,
                          bool disableParentWhenSpinning = true );

    /** @brief Constructor
     *
     * Use this constructor to automatically create a modal
     * ("blocking") spinner on top of the calling widget/window.  If a valid
     * parent widget is provided, "centreOnParent" will ensure that
     * QtWaitingSpinner automatically centres itself on it, if not,
     * @p centerOnParent is ignored.
     */
    WaitingSpinnerWidget( Qt::WindowModality modality,
                          QWidget* parent = nullptr,
                          bool centerOnParent = true,
                          bool disableParentWhenSpinning = true );

    WaitingSpinnerWidget( const WaitingSpinnerWidget& ) = delete;
    WaitingSpinnerWidget& operator=( const WaitingSpinnerWidget& ) = delete;

    void setColor( QColor color );
    void setTextColor( QColor color );
    void setRoundness( qreal roundness );
    void setMinimumTrailOpacity( qreal minimumTrailOpacity );
    void setTrailFadePercentage( qreal trail );
    void setRevolutionsPerSecond( qreal revolutionsPerSecond );
    void setNumberOfLines( int lines );
    void setLineLength( int length );
    void setLineWidth( int width );
    void setInnerRadius( int radius );

    /** @brief Sets the text displayed in or below the spinner
     *
     * If the text is empty, no text is displayed. The text is displayed
     * in or below the spinner depending on the value of alignment().
     * With AlignBottom, the text is displayed below the spinner,
     * centered horizontally relative to the spinner; any other alignment
     * will put the text in the middle of the spinner itself.
     *
     * TODO: this does not support rich text. Rich text could be done
     *       through a QStaticText, or an HTML document. However, then
     *       we need to do more alignment calculations ourselves.
     */
    void setText( const QString& text );
    /** @brief Sets the alignment of text for the spinner
     *
     * The only meaningful values are AlignBottom and AlignVCenter,
     * for text below the spinner and text in the middle.
     */
    void setAlignment( Qt::AlignmentFlag align );
    /// Convenience to set text-in-the-middle (@c true) or text-at-bottom (@c false)
    void setCenteredText( bool centered )
    {
        setAlignment( centered ? Qt::AlignmentFlag::AlignVCenter : Qt::AlignmentFlag::AlignBottom );
    }

    QColor color() const;
    QColor textColor() const;
    QString text() const;
    Qt::AlignmentFlag alignment() const { return _alignment; }
    qreal roundness() const;
    qreal minimumTrailOpacity() const;
    qreal trailFadePercentage() const;
    qreal revolutionsPersSecond() const;
    int numberOfLines() const;
    int lineLength() const;
    int lineWidth() const;
    int innerRadius() const;

    bool isSpinning() const;

public Q_SLOTS:
    void start();
    void stop();

private Q_SLOTS:
    void rotate();

protected:
    void paintEvent( QPaintEvent* paintEvent ) override;

private:
    void updateSize();
    void updateTimer();
    void updatePosition();

private:
    // PI, leading to a full fade in one whole revolution
    static constexpr const auto radian = 3.14159265358979323846;

    // Spinner-wheel related settings
    QColor _color = Qt::black;
    qreal _roundness = 100.0;  // 0..100
    qreal _minimumTrailOpacity = radian;
    qreal _trailFadePercentage = 80.0;
    qreal _revolutionsPerSecond = radian / 2;
    int _numberOfLines = 20;
    int _lineLength = 10;
    int _lineWidth = 2;
    int _innerRadius = 10;
    QSize _imageSize;

    // Text-related settings
    Qt::AlignmentFlag _alignment = Qt::AlignmentFlag::AlignBottom;
    QString _text;
    QColor _textColor = Qt::black;

    // Environment settings
    bool _centerOnParent = true;
    bool _disableParentWhenSpinning = true;

    // Internal bits
    QTimer* _timer = nullptr;
    int _currentCounter = 0;
    bool _isSpinning = false;
};
