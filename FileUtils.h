//
// Created by altat on 25/03/2024.
//

#ifndef FILEUTILS_H
#define FILEUTILS_H



class FileUtils {
public:
    enum FilePathType {
        TEXTURES,ASSETS,MODELS
    };

    static const char* RootPath();
    static const char* GetFilePath(const char* path);
    static const char* GetPath(FilePathType file_path);
    static const char* GetFilePath(FilePathType file_path,const char* fileName);
};



#endif //FILEUTILS_H
