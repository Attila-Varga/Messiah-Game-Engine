//
//  SceneNode.hpp
//  Game Editor
//
//  Created by Attila Varga on 12/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef SceneNode_hpp
#define SceneNode_hpp

#include "ModelAsset.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <list>

namespace DMGS {
    
    class SceneNode
    {
    public:
        SceneNode();
        SceneNode(std::string pName);
        ~SceneNode();
        
        void addChild(SceneNode * child);
        void attachGameObject(DMGS::ModelAsset* object);
        
        void render(Camera* cam);
        
        //transformations
        
        void setPosition(glm::vec3 _position);
        void setPosition(float x, float y, float z);
        void setScale(glm::vec3 _scale);
        void setScale(float x, float y, float z);
        
        void rotate(float degree, glm::vec3 axis);
        void translate(glm::vec3 direction);
        void translate(float x, float y, float z);
        
        /**
         Rotate the Scene Node to the given direction vector
        */
        void lookAt(glm::vec3 direction);
        
        bool hasChild();
        bool drawable();
        
        ModelAsset* getAttachedObject() const { return attachedModel; }
        
        std::string getName() const { return mName; }
        
        glm::mat4 getOrientation() const { return orientation; }
        
    private:
        void setupTransformation();
        
        SceneNode* parent;
        
        std::string mName;
        std::list<SceneNode*> mChildrenList;
        

        bool renderable;
        
        int mNumberOfChildren;
        
        glm::vec3 position;
        glm::vec3 scale;
        glm::mat4 orientation;
        
        float upVector;
        float rightVector;
        
        
        //full transformation
        glm::mat4 transformation;
        
        ModelAsset* attachedModel;
    };
}



#endif /* SceneNode_hpp */
