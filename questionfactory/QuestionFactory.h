#ifndef QUESTIONFACTORY_H_
#define QUESTIONFACTORY_H_

#include <vector>
#include <string>

class QuestionFactory
{
public:
	QuestionFactory();
	~QuestionFactory();

    virtual std::string getQuestion()
    {
        mQuestion = "What is the meaning of Life the Universe and Everything?";
        mCorrectAnswer = "42";
        return mQuestion;
    }

	virtual bool        checkAnswer();

	std::string convertInt  (int number);
	virtual void        keyNumberHit(std::string number);

	std::string getPlayerAnswer () { return mPlayerAnswer;  }
	std::string getCorrectAnswer() { return mCorrectAnswer; }

	void        setPlayerAnswer(std::string playerAnswer) { mPlayerAnswer = playerAnswer; }

	void resetVariables();

protected:
	std::string mQuestion;
	std::string mPlayerAnswer;
	std::string mCorrectAnswer;

};

#endif
