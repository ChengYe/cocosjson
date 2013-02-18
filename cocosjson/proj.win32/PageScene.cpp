#include "JSONParser.h"
#include "PageScene.h"

PageScene::~PageScene()
{
	if (pJSON)
		delete []pJSON;
	if (file_n)
		json_delete(file_n);
}

void PageScene::onEnter()
{
	CCScene::onEnter();
	//do 
	//{
	//	CC_BREAK_IF(!CCScene::init());
	//	CCMenuItemImage* pCloseItem = CCMenuItemImage::create(
	//		"CloseNormal.png",
	//		"CloseSelected.png",
	//		this,
	//		menu_selector(JSONParser::menuCloseCallback));
	//	CC_BREAK_IF(!pCloseItem);
	//	pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
	//	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	//	CC_BREAK_IF(!pMenu);
	//	pMenu->setPosition(CCPointZero);
	//	this->addChild(pMenu, 1);
	//} while (0);
}

void PageScene::onExit()
{
	CCScene::onExit();
}

void PageScene::jsonprep()
{
	//read json file
	wifstream jsonfile("p2.json");
	if (jsonfile == NULL)
		cout<<"failed to read json file"<<endl;
	int filesize = sizeoffile(jsonfile);
	pJSON = new json_char[filesize+1];
	jsonfile.read(pJSON, filesize);
	pJSON[filesize]='\0';
	//wcout<<pJSON<<endl;
	file_n = json_parse(pJSON);
}

void PageScene::play(JSONNODE* filenode)
{
	if (filenode == NULL){
		wcout<<L"Invalid JSON Node from pagescene::play"<<endl;
		return;
	}

	JSONNODE_ITERATOR i = json_begin(filenode);
	while (i != json_end(filenode)){
		if (*i == NULL){
			wcout<<L"Invalid JSON Node from pagescene::play"<<endl;
			return;
		}

		if (json_type(*i) == JSON_NODE){
			CCScene* pS = CCDirector::sharedDirector()->getRunningScene();
			if (pS != NULL){
				this->removeAllChildrenWithCleanup(true);
				JSONParser* pJSONParser = new JSONParser();
				pJSONParser->PageParse(*i);
				addChild(pJSONParser);
				CCDirector::sharedDirector()->replaceScene(this);
				pJSONParser->autorelease();
			}
			else{
				JSONParser* pJSONParser = new JSONParser();
				pJSONParser->PageParse(*i);
				addChild(pJSONParser);
				CCDirector::sharedDirector()->runWithScene(this);
				pJSONParser->autorelease();
			}
		}
		++i;
	}
	
}

void PageScene::run()
{
	jsonprep();
	play(file_n);
}

int PageScene::sizeoffile(wifstream& jsonfile)
{
	jsonfile.seekg(0, ios::end);
	int filesize = jsonfile.tellg();
	jsonfile.seekg(0, ios::beg);

	return filesize;
}