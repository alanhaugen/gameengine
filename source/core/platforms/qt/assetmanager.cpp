#include "assetmanager.h"
#include <qdiriterator.h>



AssetManager::AssetManager()
{
    ImportMesh(AssethPath);
}


void AssetManager::ImportMesh(const QString &AssethPath)
{
    //goes through the filesystem starting at assethPath. adn finds all files with the filter .obj
    QDirIterator it(AssethPath, QDir::Files,QDirIterator::Subdirectories);


    //check if there more files
    while (it.hasNext())
    {
        QFileInfo File(it.next());
        if(FileType == "*."+File.suffix())
        {
            qDebug()<<"Found:"<< File.filePath() <<" \n";
            //Log("Found:"+ File.filePath().toStdString() +" \n");

            QString name = File.baseName();

            auto mesh = std::make_unique<Mesh>(File.filePath().toStdString().c_str());

            mMesh.push_back(std::move(mesh));
            mFilesNames.insert(name,mMesh.size()-1);
            mFilesPath.insert(name,File.filePath());
        }
        else if(TextureType == "*."+File.suffix())
        {
            qDebug()<<"FoundTextures:"<< File.filePath() <<" \n";
            QString name = File.baseName();

            auto Texture = std::make_unique<QString>(File.filePath().toStdString().c_str());

            mTextures.push_back(std::move(Texture));
            mTexturesPath.insert(name,File.filePath());
        }


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

    return mFilesPath.value(Name,QString());
}

QStringList AssetManager::GetTexturesNames() const
{
     return mTexturesPath.keys();
}
