#include "CompressibleLabel.h"

#include <QPainter>
#include <QTextLayout>
#include <QDebug>

CompressibleLabel::CompressibleLabel (QWidget *parent) : QLabel (parent) 
{
	setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Fixed); 
}

void CompressibleLabel::setFullText (const QString & text)
{
	fullText = text;
	compressText ();
}

void CompressibleLabel::compressText ()
{
	QFontMetrics metrics (this->font ());
	QString elidedText = metrics.elidedText (fullText, Qt::TextElideMode::ElideMiddle, this->width ());
	this->setText (elidedText);
}

void CompressibleLabel::resizeEvent (QResizeEvent * event)
{
	compressText ();
	QLabel::resizeEvent (event);	
}
