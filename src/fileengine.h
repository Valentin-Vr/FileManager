#ifndef FILEENGINE_H
#define FILEENGINE_H

#include <QAbstractListModel>
#include <QFileInfo>
#include <QObject>

struct Folder {
    Folder() = default;
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
    Q_INVOKABLE void createFileList(const QString &path);

    Q_PROPERTY(QStringList fileList READ fileList WRITE setFileList NOTIFY fileListChanged);

public slots:
    void setFileList(const QStringList &fileList);

signals:
    void fileListChanged();

private:
    QList<Folder> m_dirList;
    QStringList m_fileList;
    const QStringList &fileList() const;

    void updateData();
};

#endif // FILEENGINE_H
