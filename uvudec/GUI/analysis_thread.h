/*
UVNet Universal Decompiler (uvudec)
Copyright 2010 John McMaster <JohnDMcMaster@gmail.com>
Licensed under the terms of the LGPL V3 or later, see COPYING for details
*/

#ifndef UVD_GUI_ANALYSIS_THREAD_H
#define UVD_GUI_ANALYSIS_THREAD_H

#include "GUI/uvudec.ui.h"
#include <QThread>
#include <QMutex>
#include <QObject>
#include "uvd/util/types.h"
#include "uvd/core/uvd.h"

class UVDMainWindow;
class UVDAnalysisAction;
class UVDEvent;
class UVDGUIAnalysisThread : public QThread
{
	Q_OBJECT

public:
	UVDGUIAnalysisThread();
	~UVDGUIAnalysisThread();
	uv_err_t init();

	void run();
	uv_err_t runLoop();
	//Will be free'd internally
	void queueAnalysis(UVDAnalysisAction *action);

	uv_err_t beginAnalysis();
	//uv_err_t disassembleRange(UVDIterator iterBegin, UVDIterator iterEnd);

	uv_err_t initializeUVDCallbacks();
	uv_err_t handleUVDEvent(const UVDEvent *event);

	uv_err_t printLogEntry(const std::string &line);

signals:
	//We finished disassembling the next line, line is the result
	//void lineDisassembledMonospaced(QString name);
	//void lineDisassembledHTML(QString name);
	void newFunction(QString functionName);
	void deleteFunction(QString functionName);
	void printLog(QString line);
	//void setDisassemblyAreaActive(bool);
	
	//For hexdump, strings
	void binaryStateChanged();
	//Analysis may have changed the way disassembling works
	void assemblyChanged();
	//Update strings view
	void stringsChanged();

protected:
	uv_err_t getNextAction(UVDAnalysisAction **action);

public:
	UVDMainWindow *m_mainWindow;
	//
	std::list<UVDAnalysisAction *> m_analyisActionsQueue;
	//For adding analysis events
	QMutex m_analyisActionsQueueMutex;
	//For performing GUI operations
	//We must wait until no analysis is running so that we can update the GUI state
	QMutex m_uvdMutex;
	//Add some sort of queue here to queue up analsis events
	uint32_t m_active;
};

#endif

