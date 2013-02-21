#include "libjson.h"
#include "cocos2d.h"
USING_NS_CC;
#include <fstream>
using namespace std;

class PageScene : public CCScene
{
public:
	PageScene();
	~PageScene();

	virtual void onEnter();
	virtual void onExit();

	void jsonprep();
	void NextPage(CCTime dt);
	void PreviousPage();

	int sizeoffile(wifstream& jsonfile);

private:
	JSONNODE_ITERATOR pageindex;
	json_char *pJSON;
	JSONNODE *file_n;

	//for testing
	int schedulecounter;
};