#include "shape.h"

Shape::Shape(Ogre::SceneManager* sceneMgr, std::string shapeName,std::string meshName, int x, int y, int z)
{
	//character traits
    	mShapeName = shapeName;
    	mMeshName  = meshName;

    	//starting position
    	xPos = x;
    	yPos = y;
    	zPos = z;

	//the all powerful SceneManager
	mSceneManager = sceneMgr;

        //actually create and show the model on screen...assuming you put it somewhere visible etc.
        setupModel();
}

Shape::~Shape()
{
}

void Shape::setupModel()
{
	//SceneNode* sn = NULL;
	Entity* entity = NULL;

	// create scene nodes for the models at regular angular intervals
	mSceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
		
	// put character in starting spawn spot
	mSceneNode->translate(xPos, yPos, zPos, Node::TS_LOCAL);

	// create entity and attach mesh to it
	entity = mSceneManager->createEntity(mShapeName, mMeshName);
	mSceneNode->attachObject(entity);

}

void Shape::cleanupContent()
{
	mSceneNode      = NULL;
}









