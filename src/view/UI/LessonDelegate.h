#pragma once

#include <QStyledItemDelegate>

class LessonDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	LessonDelegate (QObject* parent) : QStyledItemDelegate (parent) {}
	virtual void setEditorData (QWidget *editor, const QModelIndex &index) const override;
	virtual void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

signals:
	void lessonNameChanged (QString& oldName, QString& newName) const;
};