//
// Created by altat on 25/03/2024.
//

#include "FileUtils.h"

#include <iostream>
#include <string.h>

#include <string>
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>


const char* FileUtils::RootPath() {
    return  std::filesystem::current_path().string().c_str();
}

const char * FileUtils::GetFilePath(const char *path) {
        std::string parentDir = (std::filesystem::current_path()).string();
        std::cout << "Parent " << parentDir << std::endl;
        std::string texPath = path;
        // Dynamically allocate memory for the C-style string
        size_t bufferSize = parentDir.length() + texPath.length() + 1;
        char* result = new char[bufferSize];

        // Use strcpy_s instead of strcpy

        strcpy(result, (parentDir + texPath).c_str());
        return result;
}

const char * FileUtils::GetPath(FilePathType file_path) {
    if(file_path == ASSETS) {
        return FileUtils::GetFilePath("/assets/");
    }else if(file_path == TEXTURES) {
        return FileUtils::GetFilePath("/textures/");
    }else if(file_path == MODELS) {
        return FileUtils::GetFilePath("/models/");
    }
}

const char* FileUtils::GetFilePath(FilePathType file_path, const char *fileName) {

    std::string s = (std::string(GetPath(file_path))+std::string(fileName));
    char* c = new char[s.size() + 1];
    strcpy(c, s.c_str());
    return c;
}


