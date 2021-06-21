#include "fileengine.h"

#include <QDebug>
#include <QDir>
#include <QFileInfoList>

FileEngine::FileEngine(QObject *parent): QAbstractListModel (parent)
{
    QFileInfoList mainDiscList = QDir::drives();
    for (int i = 0; i < mainDiscList.count(); ++i) {
        QDir tempWay(mainDiscList[i].filePath());
        QFileInfoList tempNextFoldersList = tempWay.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
        int foldersCount = tempNextFoldersList.count();
        Folder folder(0, mainDiscList[i].filePath(), foldersCount, !foldersCount);
        m_dirList.append(folder);
    }
}

QVariant FileEngine::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    switch (role) {
    case IsOpen:
        return m_dirList[index.row()].m_isOpen;
    case ChildrenCount:
        return m_dirList[index.row()].m_childrenCount;
    case Level:
        return m_dirList[index.row()].m_level;
    case Path:
        return m_dirList[index.row()].m_path;
    }
    return QVariant();
}

int FileEngine::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_dirList.size();
}

QHash<int, QByteArray> FileEngine::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[IsOpen] =         "isOpen";
    roles[ChildrenCount] =  "childrenCount";
    roles[Level] =          "level";
    roles[Path] =           "path";
    return roles;
}

void FileEngine::nextFolder(const int index)
{
    Folder previousFolder = m_dirList[index];
    if (previousFolder.m_childrenCount > 0 && !previousFolder.m_isOpen) {
        QDir previousWay(previousFolder.m_path);
        QFileInfoList nextFoldersList = previousWay.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
        for (int i = 0; i < nextFoldersList.count(); ++i) {
            QDir tempWay(nextFoldersList[i].filePath());
            QFileInfoList tempNextFoldersList = tempWay.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
            int foldersCount = tempNextFoldersList.count();
            Folder nextFolder(previousFolder.m_level + 1,
                              nextFoldersList[i].filePath(),
                              foldersCount,
                              !foldersCount);
            m_dirList.insert(index + 1 + i, nextFolder);
        }
        m_dirList[index].m_isOpen = true;
        updateData();
    }
}

void FileEngine::previousFolder(const int index)
{
    Folder previousFolder = m_dirList[index];
    if (previousFolder.m_isOpen && previousFolder.m_childrenCount > 0) {
        for (int i = 0; i < previousFolder.m_childrenCount; ++i) {
            FileEngine::previousFolder(index + 1);
            m_dirList.removeAt(index + 1);
        }
        m_dirList[index].m_isOpen = false;
        updateData();
    }
}

void FileEngine::createFileList(const QString &path)
{
    QDir tempWay(path);
    QFileInfoList tempFileList = tempWay.entryInfoList((QDir::Files));
    QStringList fileList;
    for (int i = 0; i < tempFileList.count(); ++i)
        fileList.append(tempFileList[i].fileName());
    setFileList(fileList);
}

void FileEngine::updateData()
{
    beginResetModel();
    endResetModel();
}

const QStringList &FileEngine::fileList() const
{
    return m_fileList;
}

void FileEngine::setFileList(const QStringList &fileList)
{
    if (m_fileList == fileList)
        return;
    m_fileList = fileList;
    emit fileListChanged();
}
