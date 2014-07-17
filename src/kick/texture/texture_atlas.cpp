//
// Created by morten on 30/06/14.
//


#include "kick/texture/texture_atlas.h"
#include <rapidjson/document.h>



using namespace std;
using namespace glm;

namespace kick {

    namespace {
        ivec2 whToVec2(rapidjson::Value &val) {
            return {val["w"].GetInt(), val["h"].GetInt()};
        }

        ivec4 xywhToVec4(rapidjson::Value &val) {
            return {val["x"].GetInt(), val["y"].GetInt(), val["w"].GetInt(), val["h"].GetInt()};
        }
    }

    TextureAtlas::TextureAtlas(Project *project) : ProjectAsset(project) {
        shader = Project::loadShader("assets/shaders/sprite.shader");
    }

    bool TextureAtlas::load(std::string filename, std::string texture) {
        this->texture = Project::loadTexture2D(texture);
        string textureAtlas;
        if (!Project::loadTextResource(filename, textureAtlas)){
            return false;
        }

        atlas.clear();

        rapidjson::Document d;
        d.Parse<0>(textureAtlas.c_str());
        auto &frames = d["frames"];
        for (auto itr = frames.MemberBegin(); itr != frames.MemberEnd(); ++itr){
            TextureAtlasEntry entry;
            auto& val = itr->value;
            entry.rotated = val["rotated"].GetBool();
            entry.trimmed = val["trimmed"].GetBool();
            entry.frame = xywhToVec4(val["frame"]);
            entry.spriteSourceSize = xywhToVec4(val["spriteSourceSize"]);
            entry.sourceSize = whToVec2(val["sourceSize"]);
            atlas[itr->name.GetString()] = entry;
        }
        auto &meta = d["meta"];
        textureSize = whToVec2(meta["size"]);
        return true;
    }

    Texture2D *TextureAtlas::getTexture() const {
        return texture;
    }

    TextureAtlasEntry TextureAtlas::get(std::string name) {
        return atlas[name];
    }

    glm::ivec2 TextureAtlas::getTextureSize() const {
        return textureSize;
    }

    Shader *TextureAtlas::getShader() const {
        return shader;
    }

    void TextureAtlas::setShader(Shader *shader) {
        TextureAtlas::shader = shader;
    }
}