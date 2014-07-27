//
// Created by morten on 30/06/14.
//


#pragma once

#include "kick/2d/component2d.h"
#include "kick/scene/game_object.h"
#include "kick/2d/font.h"
#include "kick/math/bounds2d.h"
#include "kick/core/event_listener.h"


namespace kick {
    class Font;
    class Mesh;

    class Text : public Component2D {
    public:
        Text(GameObject *gameObject);
        Font * getFont() const;
        void setFont(Font *font);
        virtual void render(EngineUniforms *engineUniforms);
        std::string const & getText() const;
        void setText(std::string const &text);
        Bounds2D getBounds();
        Shader* getShader() const override;
        Material * getMaterial() const;
        void setMaterial(Material *material);

        virtual int getRenderOrder();

        glm::vec2 getAnchor() const;
        void setAnchor(glm::vec2 anchor);
    private:
        EventListener<Font*> eventListener;
        Bounds2D bounds;
        void updateVertexBuffer();
        Font *font = nullptr;
        Mesh *mesh = nullptr;
        MeshData *meshData = nullptr;
        std::string text;
        glm::vec2 anchor{0,0};
        Material* material = nullptr;
    };
}


