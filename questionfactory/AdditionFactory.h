#ifndef ADDITIONFACTORY_H_
#define ADDITIONFACTORY_H_

#include "QuestionFactory.h"

#include <vector>
#include <string>

class AdditionFactory : public QuestionFactory
{
public:
	AdditionFactory();
	~AdditionFactory();

	virtual std::string getQuestion();

};

#endif
