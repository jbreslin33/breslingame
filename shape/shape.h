#ifndef SHAPE_H
#define SHAPE_H

#include "Ogre.h"
#include "OIS.h"

using namespace Ogre;

class Shape
{

public:

Shape(Ogre::SceneManager* mSceneMgr, std::string name, std::string mesh, int xPos, int yPos, int zPos); 
~Shape();

SceneNode* getSceneNode() { return mSceneNode; }

protected:

void setupModel();
void cleanupContent();

//objects
Ogre::SceneManager* mSceneManager;
SceneNode*          mSceneNode;

//stats
std::string mShapeName;
std::string mMeshName;
int xPos;
int yPos;
int zPos;

};

#endif

