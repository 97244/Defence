#pragma once
#include "BaseLayer.h"
//  ���������  ���ڿ����߽���
class AboutCoderLayer:public BaseLayer{
public:
	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(AboutCoderLayer);
	void menuReturnCallBack(Ref*pSender); // ������ذ�ť �������¼�
private:
	bool setUpdateView();
};
