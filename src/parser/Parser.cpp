#include "Parser.h"

#include <QDebug>

std::tuple<Lesson, Parser::IOStatus> Parser::parseFile (const QFileInfo& fileInfo)
{
	QFile file (fileInfo.filePath ());
	Lesson lesson;

	if (file.open (QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in (&file);
		in.setCodec ("UTF-8");
		in >> lesson;
		file.close ();
	}
	else return { lesson, CANNOT_OPEN_FILE };

	return { lesson, SUCCESS };
}

Parser::IOStatus Parser::writeFile (Lesson & lesson, const QFileInfo& fileInfo)
{
	QFile file (fileInfo.filePath ());
	
	if (file.open (QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QTextStream out(&file);
		out.setCodec ("UTF-8");
		out.setGenerateByteOrderMark (true);
		out << lesson;
		file.close ();
	}
	else return CANNOT_OPEN_FILE;

	return SUCCESS;
}

QFileInfoList Parser::listLessonsInFolder (const QDir& dir)
{
	return dir.entryInfoList ({ QString ("*") + QString (DEFAULT_LESSON_FILE_EXTENSION) });;
}

QString Parser::MoveFileToTrash (const QFileInfo & fileInfo)
{
	return MoveToTrashImpl (fileInfo);
}

#ifdef Q_OS_WIN32

#include "windows.h"

QString Parser::MoveToTrashImpl (const QFileInfo & fileinfo) {
	if (!fileinfo.exists ())
		return "File doesnt exists, cant move to trash";
	WCHAR from[MAX_PATH];
	memset (from, 0, sizeof (from));
	int l = fileinfo.absoluteFilePath ().toWCharArray (from);
	Q_ASSERT (0 <= l && l < MAX_PATH);
	from[l] = '\0';
	SHFILEOPSTRUCTW fileop;
	memset (&fileop, 0, sizeof (fileop));
	fileop.wFunc = FO_DELETE;
	fileop.pFrom = from;
	fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
	int rv = SHFileOperationW (&fileop);
	if (0 != rv) {
		qDebug () << rv << QString::number (rv).toInt (0, 8);
		return "move to trash failed";
	}
	fileinfo.absoluteFilePath ();
	return "";
}
#endif

#ifdef Q_OS_LINUX
bool TrashInitialized = false;
QString TrashPath;
QString TrashPathInfo;
QString TrashPathFiles;

QString Parser::MoveToTrashImpl (const QFileInfo & fileinfo) {
	if (!TrashInitialized) {
		QStringList paths;
		const char* xdg_data_home = getenv ("XDG_DATA_HOME");
		if (xdg_data_home) {
			qDebug () << "XDG_DATA_HOME not yet tested";
			QString xdgTrash (xdg_data_home);
			paths.append (xdgTrash + "/Trash");
		}
		QString home = QStandardPaths::writableLocation (QStandardPaths::HomeLocation);
		paths.append (home + "/.local/share/Trash");
		paths.append (home + "/.trash");
		foreach (QString path, paths) {
			if (TrashPath.isEmpty ()) {
				QDir dir (path);
				if (dir.exists ()) {
					TrashPath = path;
				}
			}
		}
		if (TrashPath.isEmpty ())
			return "Cant detect trash folder";
		TrashPathInfo = TrashPath + "/info";
		TrashPathFiles = TrashPath + "/files";
		if (!QDir (TrashPathInfo).exists () || !QDir (TrashPathFiles).exists ())
			return "Trash doesnt looks like FreeDesktop.org Trash specification";
		TrashInitialized = true;
	}
	QFileInfo original = fileinfo;
	if (!original.exists ())
		return "File doesnt exists, cant move to trash";
	QString info;
	info += "[Trash Info]\nPath=";
	info += original.absoluteFilePath ();
	info += "\nDeletionDate=";
	info += QDateTime::currentDateTime ().toString ("yyyy-MM-ddThh:mm:ss.zzzZ");
	info += "\n";
	QString trashname = original.fileName ();
	QString infopath = TrashPathInfo + "/" + trashname + ".trashinfo";
	QString filepath = TrashPathFiles + "/" + trashname;
	int nr = 1;
	while (QFileInfo (infopath).exists () || QFileInfo (filepath).exists ()) {
		nr++;
		trashname = original.baseName () + "." + QString::number (nr);
		if (!original.completeSuffix ().isEmpty ()) {
			trashname += QString (".") + original.completeSuffix ();
		}
		infopath = TrashPathInfo + "/" + trashname + ".trashinfo";
		filepath = TrashPathFiles + "/" + trashname;
	}
	QDir dir;
	if (!dir.rename (original.absoluteFilePath (), filepath)) {
		return "move to trash failed";
	}
	File infofile;
	infofile.createUtf8 (infopath, info);
	return "";
}
#endif
