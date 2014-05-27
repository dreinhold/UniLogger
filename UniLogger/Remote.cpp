//#include "stdafx.h"
#include "Remote.h"
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

#define BUFSIZE MAX_PATH
//#define UNICODE 
#define FILENAME "sdrsharptrunking.log"

/*
Called when a voice role receiver is idle.
The arguments are guaranteed to remain stable for the duration of the function call. 
However, the called function should return ASAP to prevent blocking the application.
rx - receiver to park on a voice channel.
ch - conventional voice channel (_site is likely NULL).
*/
void Park(const RX *rx, const Channel *ch)
{
	Log("Park", rx, ch, NULL, NULL);
}

/*
Called when a signal role receiver follows a control channel.
The arguments are guaranteed to remain stable for the duration of the function call. 
However, the called function should return ASAP to prevent blocking the application.
rx - receiver chasing a control channel.
ch - control channel
*/
void Control(const RX *rx, const Channel *ch)
{
	Log("Control", rx, ch, NULL, NULL);
}

/*
Called when a voice role receiver follows a voice channel.
The arguments are guaranteed to remain stable for the duration of the function call. 
However, the called function should return ASAP to prevent blocking the application.
rx - receiver chasing a voice channel.
ch - voice channel
src - speaking party with radio ID.
tgt - audience party (may be a talkgroup or radio).
*/
void Listen(const RX *rx, const Channel *ch, const Address *src, const Address *tgt)
{
	Log("Listen", rx, ch, src, tgt);
}

void Log(char* action, const RX *rx, const Channel *ch, const Address *src, const Address *tgt)
{
	ofstream logfile;
	logfile.open(FILENAME);
	logfile << "action\treceiver\tfrequency\ttargetid\ttargetlabel\tsourceid\tsourcelabel\n";
	logfile << action << "\t" << rx->_label << "\t" << ch->_Hz;
	if (tgt != NULL){
		logfile  << "\t" << tgt->_ID << "\t" << tgt->_label;
	}
	// Why does this *possibly* crash Unitrunker?
	if (src != NULL && src->_ID != NULL) {
			logfile << "\t" << src->_ID;
			if (src->_label != NULL) {
				logfile << "\t" << src->_label;
			}
	}
	logfile << "\n";
	logfile.close();
}