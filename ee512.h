
#if !defined(AFX_EE512_H__B119B87A_E830_4870_9F0F_5EE2A8C0ACCE__INCLUDED_)
#define AFX_EE512_H__B119B87A_E830_4870_9F0F_5EE2A8C0ACCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include <windows.h>
#include <windowsx.h>
#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <process.h>
#include <time.h>
#define IDD_UPDOWN   202
#define MAX_LOADSTRING	100
double  PKT_SIZE=800; // bytes/sec
int SinkPacket=500;
// Global Variables:
HINSTANCE hInst;
HMENU hMenu,hMenu1;
TCHAR szTitle[MAX_LOADSTRING];// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];// The title bar text
DWORD Tid1, Tid2, Tid3, Tid4,Tid6; /* thread IDs */
double pkt;
int Draw(HDC,int);
int Draw10Rect(HDC,int ,int );
int Draw10RectR(HDC,int,int);
int Draw10RectG(HDC,int,int);
int DrawSink(HDC hdc,int Source,int status);

unsigned long delay=200;
int sc=1,delay1=150;
HBRUSH hRed,hGreen,hBlack;
double q1=0,q2=0,q3=0,q4=0;
int rr=0;
double q1s=0,q2s=0,q3s=0,q4s=0;
double q1b=0,q2b=0,q3b=0,q4b=0;
double q1bL=0,q2bL=0,q3bL=0,q4bL=0;
double q1L=0,q2L=0,q3L=0,q4L=0;
int Stack=0;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Dialog(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI Source(LPVOID param);
DWORD WINAPI Queue1(LPVOID param);
DWORD WINAPI Queue2(LPVOID param);
DWORD WINAPI Queue3(LPVOID param);
DWORD WINAPI Queue4(LPVOID param);
DWORD WINAPI Sink(LPVOID param);

double nexp(double);
HANDLE t1,t2,t3,t5,t6;
HWND hWnd,hDlg;
static HWND hTrack,hTrack1,hTrack2,hTrack3,hCheck1,hCheck2,udWnd,hEboxWnd;
TCHAR szBuffer[255],szBuffer1[255];
int count=0,Check1=0,Check2=0;
int PacketsSent=0,quanta=100,quanta1=0;
double BytesSent=0;
#endif // !defined(AFX_EE512_H__B119B87A_E830_4870_9F0F_5EE2A8C0ACCE__INCLUDED_)
