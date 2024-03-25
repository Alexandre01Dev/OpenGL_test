//
// Created by altat on 25/03/2024.
//

#include <fstream>
#include "model.h"

#include "base64.h"

std::string get_file_contents(const char* filename)
{
    std::cout<< "Hey !" << std::endl;
    std::cout << filename << std::endl;
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Model::Model(const char *file,bool reverted) {
    Model::reverted = reverted;
    std::cout << "MODEL LOADING ! from " << &file << std::endl;
    std::cout << "MODEL LOADING ! from " << file << std::endl;
    std::cout << "MODEL LOADING ! from " << *file << std::endl;

    std::string text = get_file_contents(file);
    std::cout << "PARSING!" << std::endl;
    Model::JSON = json::parse(text);
    std::cout << "PARSED !" << std::endl;
    Model::file = file;
    std::cout << "GET DATA !" << std::endl;
    Model::data = getData();
    std::cout << "TRANVERSE NODE !" << std::endl;
    tranverseNode(0);
}

std::vector<Texture> Model::getTextures() {
    std::cout << "LOAD TEX 1!" << std::endl;
    std::vector<Texture> textures;

    std::string fileStr = std::string(file);
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
    std::cout << "LOAD TEX 2!" << std::endl;

    for (unsigned int i = 0; i < JSON["images"].size(); ++i) {
        std::string texPath = JSON["images"][i]["uri"];

        bool skip = false;
        for (unsigned int j = 0; j < loadedTexName.size(); ++j) {
            if (loadedTexName[j] == texPath) {
                textures.push_back(loadedTex[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            if (texPath.find("baseColor") != std::string::npos){
                Texture* diffuse = new Texture(fileDirectory.c_str(), texPath.c_str(), loadedTex.size(), DIFFUSE);
                std::cout << "PODFSKVFPL" <<std::endl;
                std::cout << diffuse->type << std::endl;
                textures.push_back(*diffuse);
                loadedTex.push_back(*diffuse);
                loadedTexName.push_back(texPath);
            } else if (texPath.find("metallicRoughness") != std::string::npos) {
                Texture* specular = new Texture(fileDirectory.c_str(), texPath.c_str(), loadedTex.size(), DIFFUSE);

                textures.push_back(*specular);
                loadedTex.push_back(*specular);
                loadedTexName.push_back(texPath);
            }
        }
    }
    std::cout << "LOAD TEX END!" << std::endl;
    std::cout << "LOAD TEX " << textures.size() << std::endl;
    std::cout << "RETURN TEX " << textures.data() << std::endl;
    return textures;
}

void Model::loadMesh(unsigned int indMesh) {
    std::cout << "LOAD MESH 1!" << std::endl;
    unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
    std::cout << "LOAD MESH 2!" << std::endl;
    unsigned int normalAccInd =JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
    std::cout << "LOAD MESH 3!" << std::endl;
    unsigned int texAccInd =JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    std::cout << "LOAD MESH 4!" << std::endl;
    unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];
    std::cout << "LOAD MESH 5!" << std::endl;
    std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
    std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
    std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
    std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
    std::vector<float>texVec = getFloats(JSON["accessors"][texAccInd]);
    std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);
    std::cout << "LOAD MESH 6!" << std::endl;
    std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
    std::cout << "LOAD MESH 6.1!" << std::endl;
    std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
    std::cout << "LOAD MESH 7!" << std::endl;
    std::vector<Texture> textures = getTextures();
    std::cout << "LOADED WOW!" << std::endl;
    std::cout << "LOAD MESH 8!" << std::endl;
    std::cout << "PTDR " << textures.size() << std::endl;
    std::cout << "PTDR " << textures.size() << std::endl;
    meshes.emplace_back(vertices, indices, textures);
    std::cout << "LOAD MESH 9!" << std::endl;
}

void Model::tranverseNode(unsigned int nextNode, glm::mat4 matrix) {
    std::cout << "TRANVERSE NODE 1!" << std::endl;
    json node = JSON["nodes"][nextNode];
    std::cout << "TRANVERSE NODE 2!" << std::endl;
    glm::vec3 translation = glm::vec3(0.0f,0.0f,0.0f);
    if(node.find("translation") != node.end()) {
        float transValues[3];
        for (unsigned int i = 0; i < node["translation"].size(); ++i) {
            transValues[i] = node["translation"][i];
        }
        translation = glm::make_vec3(transValues);
    }
    glm::quat rotation = glm::quat(1.0f,0.0f,0.0f,0.0f);
    if(node.find("rotation") != node.end()) {
        float rotValues[4] = {
            node["rotation"][3],
            node["rotation"][0],
            node["rotation"][1],
             node["rotation"][2]
        };
        rotation = glm::make_quat(rotValues);
    }
    glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
    if(node.find("scale") != node.end()) {
        float scaleValues[3];
        for (unsigned int i = 0; i < node["scale"].size(); ++i) {
            scaleValues[i] = node["scale"][i];
        }
        scale = glm::make_vec3(scaleValues);
    }

    glm::mat4 matNode = glm::mat4(1.0f);
    if(node.find("matrix") != node.end()) {
        float matValues[16];
        for (unsigned int i = 0; i < node["matrix"].size(); ++i) {
            matValues[i] = node["matrix"][i];
        }
        matNode = glm::make_mat4(matValues);
    }

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);
    std::cout << "TRANVERSE NODE 3!" << std::endl;
    trans = glm::translate(trans,translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca,scale);

    glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

    if (node.find("mesh") != node.end()) {
        translationsMeshes.push_back(translation);
        rotationsMeshes.push_back(rotation);
        scalesMeshes.push_back(scale);
        matricesMeshes.push_back(matNextNode);

        loadMesh(node["mesh"]);
    }

    if(node.find("children") != node.end()) {
        for (unsigned int i = 0; i < node["children"].size(); ++i) {
            tranverseNode(node["children"][i],matNextNode);
        }
    }
}

void Model::Draw(ProgramShader *shader, Camera &camera,
    glm::vec3 translation,
    glm::quat rotation,
    glm::vec3 scale) {


    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader,camera,matricesMeshes[i],translation,rotation,scale,reverted);
    }
}

std::vector<unsigned char> Model::getData()
{
    // Create a place to store the raw text, and get the uri of the .bin file
    std::string bytesText;
    std::string uri = JSON["buffers"][0]["uri"];

    if (uri.rfind("data:application/octet-stream;base64,", 0) == 0) {
        std::string toDecode = uri.substr(uri.find_first_of(',')+1,uri.length());
        std::cout << "DECODE " << toDecode <<  std::endl;
        std::vector<unsigned char> b = base64_decode(toDecode);
        std::cout << "DECODE WITH BASE64" << std::endl;
        std::cout << b.data() << std::endl;;
        return b;
    }else {
        std::string fileStr = std::string(file);
        std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
        bytesText = get_file_contents((fileDirectory + uri).c_str());
        std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
        return data;
    }

    throw std::invalid_argument("Can't find type of file");
    // Store raw text data into bytesText


    // Transform the raw text data into bytes and put them in a vector

}

std::vector<float> Model::getFloats(json accessor) {
    std::vector<float> floatVec;

    unsigned int buffViewInd = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int numPerVert;
    if (type == "SCALAR") numPerVert = 1;
    else if (type == "VEC2") numPerVert = 2;
    else if (type == "VEC3") numPerVert = 3;
    else if (type == "VEC4") numPerVert = 4;
    else throw std::invalid_argument("Type is not valid (not SCALAR ; VEC2/3/4)");

    unsigned int beginningOfData = byteOffset + accByteOffset;
    unsigned int lengthOfData = count * 4 * numPerVert;
    for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData;) {
        unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        std::memcpy(&value, bytes, sizeof(float));
        floatVec.push_back(value);
    }
    return floatVec;
}



std::vector<GLuint> Model::getIndices(json accessor) {
    std::vector<GLuint> indices;
    std::cout << "LOAD INDICES 1!" << std::endl;
    unsigned int buffViewInd = accessor.value("bufferView", 0);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    unsigned int componentType = accessor["componentType"];
    std::cout << "LOAD INDICES 2!" << std::endl;

    // Get properties from the bufferView
    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    // Get indices with regards to their type: unsigned int, unsigned short, or short
    unsigned int beginningOfData = byteOffset + accByteOffset;
    if (componentType == 5125)
    {
        std::cout << "LOAD INDICES 6!" << std::endl;
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
        {
            std::cout << "LOAD INDICES 6.1!" << std::endl;
            unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
            std::cout << "LOAD INDICES 6.2!" << std::endl;
            unsigned int value;
            std::cout << "LOAD INDICES 6.3!" << std::endl;
            std::memcpy(&value, bytes, sizeof(unsigned int));
            std::cout << "LOAD INDICES 6.4!" << std::endl;
            indices.push_back((GLuint)value);
        }
    } else if (componentType == 5123) {
        // unsigned short type
        std::cout << "LOAD INDICES PRE 5!" << std::endl;
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2;) {
            unsigned char bytes[] = {data[i++], data[i++]};
            unsigned short value;
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.push_back(value);
            std::cout << "LOAD INDICES 5!" << std::endl;
        }
    } else if (componentType == 5122) {
        std::cout << "LOAD INDICES PRE 6!" << std::endl;
        // short type
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2;) {
            unsigned char bytes[] = {data[i++], data[i++]};
            short value;
            std::memcpy(&value, bytes, sizeof(short));
            indices.push_back(value);
            std::cout << "LOAD INDICES 6!" << std::endl;
        }
    }
    return indices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec) {
    std::vector<glm::vec2> vectors;
    for (int i = 0; i < floatVec.size();) {
        vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec) {
    std::vector<glm::vec3> vectors;
    for (int i = 0; i < floatVec.size();) {
        vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec) {
    std::vector<glm::vec4> vectors;
    for (int i = 0; i < floatVec.size();) {
        vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
    }
    return vectors;
}

std::vector<Vertex> Model::assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
                                            std::vector<glm::vec2> texUVs) {
    std::cout << "Assemble vertices" << std::endl;
    std::vector<Vertex> vertices;
    std::cout << "Assemble vertices 2" << std::endl;
    for (int i = 0; i < positions.size(); i++) {
        std::cout << "Assemble vertices 3" << std::endl;
        vertices.push_back
         (
             Vertex
             {
                 positions[i],
                 normals[i],
                 glm::vec3(1.0f, 1.0f, 1.0f),
                 texUVs[i]
             }
         );
    }
    std::cout << "Assemble vertices 4" << std::endl;
    return vertices;
}
