#include "LessonDelegate.h"
#include "controller/Controller.h"

#include <QMetaObject>
#include <QLineEdit>
#include <qdebug.h>

void LessonDelegate::setEditorData (QWidget * editor, const QModelIndex & index) const
{
	QString oldName = index.data (Qt::EditRole).toString ();
	QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(editor);
	if (lineEdit != nullptr && !oldName.isEmpty ())
	{
		int dot = oldName.lastIndexOf (Controller::getFileExtention());
		if (dot != -1)
		{
			QString basename = oldName.left (dot);
			lineEdit->setText (basename);
		}
	}
}

void LessonDelegate::setModelData (QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QString oldName = index.data (Qt::EditRole).toString ();
	QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(editor);
	if (lineEdit != nullptr && !oldName.isEmpty ())
	{
		QString newName = lineEdit->text () + Controller::getFileExtention ();
		if (oldName != newName)
		{
			model->setData (index, newName, Qt::EditRole);
			emit lessonNameChanged (oldName, newName);
		}
	}
}
