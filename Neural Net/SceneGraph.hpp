//
//  SceneGraph.hpp
//  Game Editor
//
//  Created by Attila Varga on 12/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef SceneGraph_hpp
#define SceneGraph_hpp

#include "SceneNode.hpp"

#include <list>
#include <string>

namespace DMGS
{
    class SceneGraph
    {
    public:
        SceneGraph();
        ~SceneGraph();
        
        void addSceneNodeToRoot(SceneNode* object);
        
        SceneNode* getRootSceneNode() const;
        
        SceneNode* getSceneNodeByName(std::string name);
        
        //Returns the main node list
        std::list<SceneNode*> getAllSceneNodes() const;
    private:
        SceneNode* mRootSceneNode;
        
        //The main list holding all the scene nodes
        std::list<SceneNode*> mNodeList;
    };
}

#endif /* SceneGraph_hpp */
