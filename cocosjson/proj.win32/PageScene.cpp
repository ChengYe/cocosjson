#include "PageLayer.h"
#include "PageScene.h"

PageScene::PageScene()
{
}

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

	jsonprep();
	if (file_n == NULL){
		wcout<<L"Invalid JSON Node from pagescene::play"<<endl;
		return;
	}
	pageindex = json_begin(file_n);
	PageLayer* pPL = new PageLayer(*pageindex);
	addChild(pPL);
	this->schedule(schedule_selector(PageScene::NextPage), pPL->GetCurPageLen());
	//CCLog("first page");
	pPL->autorelease();

	//------------
	//for testing
	//------------
	//this->schedule(schedule_selector(PageScene::NextPage), 3.0f);
	//schedulecounter = 0;

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
	file_n = json_parse(pJSON);
}

void PageScene::NextPage(CCTime dt)
{
	//------------
	//for testing
	//------------
	//schedulecounter++;
	//if (schedulecounter < 7)
	//{
	//	CCLog("lalalala %d", schedulecounter);
	//	this->unschedule(schedule_selector(PageScene::NextPage));
	//	this->schedule(schedule_selector(PageScene::NextPage), 2.0f);
	//}
	//else{
	//	this->unschedule(schedule_selector(PageScene::NextPage));
	//	CCLog("The end");
	//}

	++pageindex;
	if (pageindex != json_end(file_n))
	{
		this->unschedule(schedule_selector(PageScene::NextPage));
		if (*pageindex == NULL){
			wcout<<L"Invalid JSON Node from pagescene::play"<<endl;
			return;
		}

		if (json_type(*pageindex) == JSON_NODE){
			this->removeAllChildrenWithCleanup(true);
			PageLayer* pPL = new PageLayer(*pageindex);
			this->addChild(pPL);
			this->schedule(schedule_selector(PageScene::NextPage), pPL->GetCurPageLen());
			//CCLog("second page");
			pPL->autorelease();
		}
	}
	else{
		this->unschedule(schedule_selector(PageScene::NextPage));
		CCLog("The End");
	}
}

int PageScene::sizeoffile(wifstream& jsonfile)
{
	jsonfile.seekg(0, ios::end);
	int filesize = jsonfile.tellg();
	jsonfile.seekg(0, ios::beg);

	return filesize;
}