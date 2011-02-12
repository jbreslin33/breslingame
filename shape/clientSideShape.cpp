#include "clientSideShape.h"

ClientSideShape::ClientSideShape(Ogre::SceneManager* sceneMgr, std::string shapeName,int x, int y, int z,std::string meshName) : Shape(sceneMgr,shapeName,x,y,z)
{
	//character traits
    	mMeshName  = meshName;

	setupModel();
}

ClientSideShape::~ClientSideShape()
{
}

void ClientSideShape::setupModel()
{

	Shape::setupModel();
	Ogre::LogManager::getSingletonPtr()->logMessage("*** ClientSideShape::setUpModel() ***");

	//SceneNode* sn = NULL;
	Entity* entity = NULL;
	
	// create entity and attach mesh to it
	entity = mSceneManager->createEntity(mShapeName, mMeshName);
	mSceneNode->attachObject(entity);

}

