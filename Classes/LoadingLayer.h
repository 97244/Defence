#pragma once
#include "BaseLayer.h"  
class LoadingLayer :public BaseLayer {
public:
	virtual bool init();
	CREATE_FUNC(LoadingLayer);
	static Scene* scene();
	void loadCallBack(Ref *pSender);// �첽����ͼƬʱ �Ļص�����  
	LoadingLayer();
private:
	int loadingNum;//������¼��ǰ�ļ���ͼƬ������  
	int totalNum;// һ��Ҫ���ص�ͼƬ����  
	bool setUpdateView();// ������ʼ��ҳ��� ����������  
};
