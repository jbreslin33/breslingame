#ifndef SUBTRACTIONFACTORY_H_
#define SUBTRACTIONFACTORY_H_

#include "QuestionFactory.h"

#include <vector>
#include <string>

class SubtractionFactory : public QuestionFactory
{
public:
	SubtractionFactory();
	~SubtractionFactory();

	virtual std::string getQuestion();

};

#endif
