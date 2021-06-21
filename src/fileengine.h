#ifndef FILEENGINE_H
#define FILEENGINE_H

#include <QAbstractListModel>
#include <QFileInfo>
#include <QObject>

struct Folder {
    Folder() = default;
    //    создание модели со всеми папками со всех дисков
    //    Folder(const int level, const int parentIndex, const QString &path) :
    //        m_level(level), m_parentIndex(parentIndex), m_path(path) {}
    //    int m_parentIndex;
    //
    Folder(const int level, const QString &path, const int childrenCount, const bool isOpen) :
        m_level(level), m_path(path), m_childrenCount(childrenCount), m_isOpen(isOpen) {}
    Folder(const int level, const QString &path, const int childrenCount) :
        m_level(level), m_path(path), m_childrenCount(childrenCount) {}

    bool m_isOpen;
    int m_level;
    int m_childrenCount;
    QString m_path;
};

class FileEngine: public QAbstractListModel
{
    Q_OBJECT
public:
    FileEngine(QObject *parent = nullptr);

    enum Roles {
        IsOpen,
        ChildrenCount,
        Level,
        Path
    };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void nextFolder(const int index);
    Q_INVOKABLE void previousFolder(const int index);
    Q_PROPERTY(bool showFile READ showFile WRITE setShowFile NOTIFY showFileChanged)

    bool showFile() const;

signals:
    void showFileChanged();

private slots:
    void setShowFile(bool newShowFile);

private:
    QList<Folder> m_dirList;
    QList<QString> m_fileList;
    void updateData();
    //    void createFolderList(const QFileInfoList &pathList, const int listIndex);

    //создание модели со всеми папками со всех дисков
    //    void addFolderList(const Folder &previousFolder);
    //

    bool m_showFile;
};

#endif // FILEENGINE_H
