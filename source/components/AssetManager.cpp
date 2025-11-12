#include "AssetManager.h"
#include <qdiriterator.h>



AssetManager::AssetManager()
{
    ImportMesh(AssethPath);
}


void AssetManager::ImportMesh(const QString &AssethPath)
{
    //goes through the filesystem starting at assethPath. adn finds all files with the filter .obj
    QDirIterator it(AssethPath,QStringList() << FileType, QDir::Files,QDirIterator::Subdirectories);


    //check if there more files
    while (it.hasNext())
    {
        QFileInfo File(it.next());
         qDebug()<<"Found:"<< File.filePath() <<" \n";

        QString name = File.baseName();

        auto mesh = std::make_unique<Mesh>(File.filePath().toStdString().c_str());
        mMesh.push_back(std::move(mesh));
        mFilesNames.insert(name,mMesh.size()-1);
        mFilesPath.insert(name,File.filePath());

    }


}

QStringList AssetManager::GetMeshNames() const
{

    return mFilesNames.keys();

}

QString AssetManager::FindMesh(const QString &Name)
{
    if(!mFilesPath.contains(Name))
    {
        qDebug()<<"does not have: "<<Name;
        return QString();
    }

   return mFilesPath[Name];
}
