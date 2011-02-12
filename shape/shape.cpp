#include "shape.h"

Shape::Shape(Ogre::SceneManager* sceneMgr, std::string shapeName, int x, int y, int z)
{
	//character traits
    	mShapeName = shapeName;

    	//starting position
    	xPos = x;
    	yPos = y;
    	zPos = z;

	//the all powerful SceneManager
	mSceneManager = sceneMgr;

        //actually create and show the model on screen...assuming you put it somewhere visible etc.
       // setupModel();
}

Shape::~Shape()
{
}

void Shape::setupModel()
{
	
	// create scene nodes for the models at regular angular intervals
	mSceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
		
	// put character in starting spawn spot
	mSceneNode->translate(xPos, yPos, zPos, Node::TS_LOCAL);

}

void Shape::cleanupContent()
{
	mSceneNode      = NULL;
}









