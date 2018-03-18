#pragma once

#include <QLabel>

class CompressibleLabel : public QLabel
{
public:
	CompressibleLabel (QWidget *parent);
	void setFullText (const QString &text);

protected:
	void compressText ();
	virtual void resizeEvent (QResizeEvent *event);
	QString fullText = "";
};