#include "libjson.h"
#include "cocos2d.h"
USING_NS_CC;
#include <fstream>
using namespace std;

class PageScene : public CCScene
{
public:
	~PageScene();

	virtual void onEnter();
	virtual void onExit();

	void jsonprep();
	void play(JSONNODE* filenode);
	void run();
	int sizeoffile(wifstream& jsonfile);

private:
	json_char *pJSON;
	JSONNODE *file_n;
};