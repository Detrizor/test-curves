#pragma once

#include <qobject.h>

class gui;

class CComputeObject : public QObject
{
	Q_OBJECT

public:
	CComputeObject() { m_iThreadNum = 0; }

signals:
	void Finished();

public slots:
	void Start();

private:
	unsigned short m_iThreadNum;
	static gui* m_pGui;

public:
	void SetThreadNum(int val) { m_iThreadNum = val; }
	static void SetGui(gui* g) { m_pGui = g; }
};
