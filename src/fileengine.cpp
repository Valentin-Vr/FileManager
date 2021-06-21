#include "fileengine.h"

#include <QDebug>
#include <QDir>
#include <QFileInfoList>

//static QString PATH = QDir::rootPath();

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

    //создание модели со всеми папками со всех дисков
    //    for (int i = 0; i < 2; ++i) {
    //        int tempCount = m_dirList.count() - 1;
    //        if (m_dirList.count() == 0)
    //            tempCount = 0;
    //        Folder folder(0, tempCount, mainFolderList[i].filePath());
    //        m_dirList.append(folder);
    //        addFolderList(folder);
    //    }
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
                              foldersCount);
            if (foldersCount > 0)
                nextFolder.m_isOpen = false;
            else nextFolder.m_isOpen = true;
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
        for (int i = 0; i < previousFolder.m_childrenCount; ++i)
            m_dirList.removeAt(index + 1);
        m_dirList[index].m_isOpen = false;
        updateData();
    }
}

void FileEngine::updateData()
{
    beginResetModel();
    endResetModel();
}

//void FileEngine::nextFolder(const Folder &previousFolder)
//{
//    QDir tempWay(previousFolder.m_path);
//    QFileInfoList tempFolderList = tempWay.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
//    if (tempFolderList.count() > 0) {
//        for (int i = 0; i < tempFolderList.count(); ++i) {
//            Folder nextFolder(previousFolder.m_level + 1,
//                              previousFolder.m_parentIndex + 1 + i,
//                              tempFolderList[i].filePath());
//            m_dirList.insert(previousFolder.m_parentIndex + i + 1, nextFolder);
//        }
//    }
//}

//создание модели со всеми папками со всех дисков
//void FileEngine::addFolderList(const Folder &previousFolder)
//{
//    QDir tempWay(previousFolder.m_path);
//    QFileInfoList tempFolderList = tempWay.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
//    if (tempFolderList.count() > 0) {
//        for (int i = 0; i < tempFolderList.count(); ++i) {
//            Folder nextFolder(previousFolder.m_level + 1,
//                              previousFolder.m_parentIndex,
//                              tempFolderList[i].filePath());
//            m_dirList.append(nextFolder);
//            addFolderList(nextFolder);
//        }
//    }
//}
//

bool FileEngine::showFile() const
{
    return m_showFile;
}

void FileEngine::setShowFile(bool newShowFile)
{
    if (m_showFile == newShowFile)
        return;
    m_showFile = newShowFile;
    emit showFileChanged();
}
