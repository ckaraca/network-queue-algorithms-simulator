// ee512.cpp : Copyright 2002 - Cem KARACA
//

#include "ee512.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;
	INITCOMMONCONTROLSEX cc;
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EE512, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	srand((int)time(NULL));
	// Perform application initialization:
	if (!InitInstance (hInstance)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_EE512);
	hMenu=GetMenu(hWnd);
	hMenu1= GetSubMenu(hMenu,3);
	CheckMenuRadioItem(hMenu1,ID_PRIORITY_ABOVENORMAL,ID_PRIORITY_HIGHEST,ID_PRIORITY_NORMAL,MF_BYCOMMAND);
	CheckMenuRadioItem(hMenu,ID_1 ,ID_4, ID_1, MF_BYCOMMAND );
	EnableMenuItem(hMenu,ID_STOP,MF_GRAYED);
	EnableMenuItem(hMenu,ID_RESUME,MF_GRAYED);
	cc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	cc.dwICC = ICC_BAR_CLASSES | ICC_UPDOWN_CLASS ;
	InitCommonControlsEx(&cc);
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_CLASSDC;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EE512);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= CreateSolidBrush(RGB(204,204,204));
	wcex.lpszMenuName	= (LPCSTR)IDC_EE512;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_SHOW);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message) 
	{
		case WM_CREATE:
			SetTimer(hWnd,1,quanta,NULL);	
			hRed = CreateSolidBrush(RGB(255,0,0));
			hGreen = CreateSolidBrush(RGB(0,255,0));
			hBlack = CreateSolidBrush(RGB(0,0,0));
			CreateWindow("STATIC","static",SS_BLACKFRAME |
				WS_CHILD | WS_VISIBLE,0,175,470,55,hWnd,NULL,hInst,NULL);
			CreateWindow("STATIC","static",SS_BLACKFRAME |
				WS_CHILD | WS_VISIBLE,0,235,470,55,hWnd,NULL,hInst,NULL);
			CreateWindow("STATIC","static",SS_BLACKFRAME |
				WS_CHILD | WS_VISIBLE,0,295,250,55,hWnd,NULL,hInst,NULL);
			CreateWindow("STATIC","static",SS_BLACKFRAME |
				WS_CHILD | WS_VISIBLE,260,295,210,55,hWnd,NULL,hInst,NULL);
			CreateWindow("STATIC","static",SS_BLACKFRAME |
				WS_CHILD | WS_VISIBLE,0,355,250,55,hWnd,NULL,hInst,NULL);
			hEboxWnd = 	CreateWindow("EDIT", "edit Box", WS_CHILD | WS_VISIBLE | ES_CENTER |
				ES_NUMBER | ES_READONLY  ,
				360,315,45,20,hWnd,NULL,hInst,NULL);
			udWnd = CreateUpDownControl(
                    WS_CHILD | WS_BORDER | WS_VISIBLE |
                    UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_NOTHOUSANDS,
                    5, 5, 24, 12,
                    hWnd,
                    IDD_UPDOWN,
                    hInst,
                    hEboxWnd,
                    300, 10, quanta);
			hTrack = CreateWindow(TRACKBAR_CLASS,
				"Track Bar",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP ,
				5,195,200,30,hWnd,NULL,hInst,NULL);
			SendMessage(hTrack,TBM_SETRANGE,(WPARAM)1,(LPARAM)MAKELONG(10,500));
			SendMessage(hTrack,TBM_SETPOS,(WPARAM)1,(LPARAM)200);
			hTrack1= CreateWindow(TRACKBAR_CLASS,
				"Track Bar1",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP  ,
				5,255,200,30,hWnd,NULL,hInst,NULL);
			SendMessage(hTrack1,TBM_SETRANGE,(WPARAM)1,(LPARAM)MAKELONG(600,999));
			SendMessage(hTrack1,TBM_SETPOS,(WPARAM)1,(LPARAM)800);
			hTrack2= CreateWindow(TRACKBAR_CLASS,
				"Track Bar2",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP   ,
				5,315,200,30,hWnd,NULL,hInst,NULL);
			SendMessage(hTrack2,TBM_SETRANGE,(WPARAM)1,(LPARAM)MAKELONG(10,300));
			SendMessage(hTrack2,TBM_SETPOS,(WPARAM)1,(LPARAM)150);
				hTrack3= CreateWindow(TRACKBAR_CLASS,
				"Track Bar3",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP  ,
				5,375,200,30,hWnd,NULL,hInst,NULL);
			SendMessage(hTrack3,TBM_SETRANGE,(WPARAM)1,(LPARAM)MAKELONG(500,999));
			SendMessage(hTrack3,TBM_SETPOS,(WPARAM)1,(LPARAM)500);
			hCheck1= CreateWindow("button",
				"Use Poisson time interval", BS_AUTOCHECKBOX| WS_CHILD | WS_VISIBLE ,
				250,200,210,20,hWnd,NULL,hInst,NULL);
			hCheck2= CreateWindow("button",
				"Use Poisson Packet Size", BS_AUTOCHECKBOX| WS_CHILD | WS_VISIBLE ,
				250,260,210,20,hWnd,NULL,hInst,NULL);
			
			break;

		case WM_COMMAND:  //BM_GETCHECK
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			
			switch (wmId)
			{
				
				case BN_CLICKED:
					if((HWND)lParam==hCheck1) Check1 = SendMessage(hCheck1,BM_GETCHECK,0,0);
					if((HWND)lParam==hCheck2) Check2 = SendMessage(hCheck2,BM_GETCHECK,0,0);
					
					
					break;
				case ID_START:
					EnableMenuItem(hMenu,ID_START,MF_GRAYED);
					EnableMenuItem(hMenu,ID_STOP,MF_ENABLED);
					
					t1=CreateThread(NULL, 0,
                       (LPTHREAD_START_ROUTINE)Source, 
                       (LPVOID) hWnd, 0, &Tid1);
					hdc=GetDC(hWnd);
					TextOut(hdc,10,0,"Starting source",15);
					ReleaseDC(hWnd,hdc);
					t2=CreateThread(NULL, 0,
                       (LPTHREAD_START_ROUTINE)Queue1, 
                       (LPVOID) hWnd, 0, &Tid2);
					t3=CreateThread(NULL, 0,
                       (LPTHREAD_START_ROUTINE)Queue2, 
                       (LPVOID) hWnd, 0, &Tid3);
					t5=CreateThread(NULL, 0,
                       (LPTHREAD_START_ROUTINE)Queue3, 
                       (LPVOID) hWnd, 0, &Tid4);
					t6=CreateThread(NULL, 0,
                       (LPTHREAD_START_ROUTINE)Queue4, 
                       (LPVOID) hWnd, 0, &Tid6);
					
					break;
				case ID_PRIORITY_ABOVENORMAL:		 // must be below but I didn't change it
					CheckMenuRadioItem(hMenu1,ID_PRIORITY_ABOVENORMAL,ID_PRIORITY_HIGHEST,ID_PRIORITY_ABOVENORMAL,MF_BYCOMMAND);
					SetThreadPriority(t1,THREAD_PRIORITY_IDLE);
					SetThreadPriority(t2,THREAD_PRIORITY_IDLE);
					SetThreadPriority(t3,THREAD_PRIORITY_IDLE);
					SetThreadPriority(t5,THREAD_PRIORITY_IDLE);
					SetThreadPriority(t6,THREAD_PRIORITY_IDLE);
					SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_IDLE );
					break;
				case ID_PRIORITY_NORMAL:
					SetThreadPriority(t1,THREAD_PRIORITY_NORMAL);
					SetThreadPriority(t2,THREAD_PRIORITY_NORMAL);
					SetThreadPriority(t3,THREAD_PRIORITY_NORMAL);
					SetThreadPriority(t5,THREAD_PRIORITY_NORMAL);
					SetThreadPriority(t6,THREAD_PRIORITY_NORMAL);
					SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_NORMAL );
					CheckMenuRadioItem(hMenu1,ID_PRIORITY_ABOVENORMAL,ID_PRIORITY_HIGHEST,ID_PRIORITY_NORMAL,MF_BYCOMMAND);
					break;
				case ID_PRIORITY_HIGHEST:
					SetThreadPriority(t1,THREAD_PRIORITY_HIGHEST);
					SetThreadPriority(t2,THREAD_PRIORITY_HIGHEST);
					SetThreadPriority(t3,THREAD_PRIORITY_HIGHEST);
					SetThreadPriority(t5,THREAD_PRIORITY_HIGHEST);
					SetThreadPriority(t6,THREAD_PRIORITY_HIGHEST);
					SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST );
					CheckMenuRadioItem(hMenu1,ID_PRIORITY_ABOVENORMAL,ID_PRIORITY_HIGHEST,ID_PRIORITY_HIGHEST,MF_BYCOMMAND);
					break;

				case ID_1:			
					sc=1;
					CheckMenuRadioItem(hMenu,ID_1 ,ID_6, ID_1, MF_BYCOMMAND  );
					break;
				case ID_2:
					sc=2;
					CheckMenuRadioItem(hMenu,ID_1 ,ID_6, ID_2, MF_BYCOMMAND  );
					break;
				case ID_3:
					sc=3;
					CheckMenuRadioItem(hMenu,ID_1 ,ID_6, ID_3, MF_BYCOMMAND  );
					break;
				case ID_4:
					sc=4;
					CheckMenuRadioItem(hMenu,ID_1 ,ID_6, ID_4, MF_BYCOMMAND  );
					break;
				
				case ID_STOP:
					EnableMenuItem(hMenu,ID_RESUME,MF_ENABLED);
					EnableMenuItem(hMenu,ID_STOP,MF_GRAYED);
					SuspendThread(t1);
					SuspendThread(t2);
					SuspendThread(t3);
					SuspendThread(t5);
					SuspendThread(t6);

					break;
				case ID_RESUME:
					EnableMenuItem(hMenu,ID_STOP,MF_ENABLED);
					EnableMenuItem(hMenu,ID_RESUME,MF_GRAYED);
					ResumeThread(t1);
					ResumeThread(t2);
					ResumeThread(t3);
					ResumeThread(t5);
					ResumeThread(t6);
					break;
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case ID_PLOT_1:
					hDlg=CreateDialog(hInst,MAKEINTRESOURCE(IDD_LARGE), hWnd, (DLGPROC)Dialog);
					break;

				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

		case WM_VSCROLL:
			if(udWnd==(HWND)lParam) 
			{
				quanta = SendMessage(udWnd,UDM_GETPOS,0,0);
				SetTimer(hWnd,1,quanta,NULL);	
			}				
			break;
		case WM_HSCROLL:
			switch(LOWORD(wParam))
			{
				case TB_TOP:
				case TB_BOTTOM:
				case TB_LINEDOWN:
				case TB_THUMBPOSITION:
				case TB_THUMBTRACK:
				case TB_PAGEUP:
				case TB_LINEUP:
				case TB_PAGEDOWN:
				if(hTrack == (HWND)lParam) 
				{
					delay= SendMessage(hTrack, TBM_GETPOS, 0,0);
					hdc=GetDC(hWnd);
					wsprintf(szBuffer1,"%lu  ",delay);
					TextOut(hdc,210,200,szBuffer1,lstrlen(szBuffer1));
					ReleaseDC(hWnd,hdc);
				}
				if(hTrack1 == (HWND)lParam) 
				{
					PKT_SIZE= SendMessage(hTrack1, TBM_GETPOS, 0,0);
					hdc=GetDC(hWnd);
					wsprintf(szBuffer1,"%d  ",(int)PKT_SIZE);
					TextOut(hdc,210,265,szBuffer1,lstrlen(szBuffer1));
					ReleaseDC(hWnd,hdc);
				}
				if(hTrack2 == (HWND)lParam) 
				{
					delay1= SendMessage(hTrack2, TBM_GETPOS, 0,0);
					hdc=GetDC(hWnd);
					wsprintf(szBuffer1,"%d  ",delay1);
					TextOut(hdc,210,330,szBuffer1,lstrlen(szBuffer1));
					ReleaseDC(hWnd,hdc);
				}
				if(hTrack3 == (HWND)lParam) 
				{
					SinkPacket= SendMessage(hTrack3, TBM_GETPOS, 0,0);
					hdc=GetDC(hWnd);
					wsprintf(szBuffer1,"%d  ",SinkPacket);
					TextOut(hdc,210,385,szBuffer1,lstrlen(szBuffer1));
					ReleaseDC(hWnd,hdc);
				}
				break;
					
			}
			break;
		case WM_TIMER:
			quanta1++;
			if(quanta1>3) quanta1=0;

			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			SetBkColor(hdc,RGB(204,204,204));
			RECT rt;
			GetClientRect(hWnd, &rt);
			TextOut(hdc,0,175,"Source packet sending time interval",35);
			TextOut(hdc,0,235,"Source Packet Size",18);
			TextOut(hdc,0,295,"Server Delay Value",18);
			TextOut(hdc,265,295,"RR Quanta:",10);
			TextOut(hdc,0,355,"Sink Packet Size  ",18);
			wsprintf(szBuffer1,"%lu   ",delay);
			TextOut(hdc,210,200,szBuffer1,lstrlen(szBuffer1));
			wsprintf(szBuffer1,"%lu   ",(int)PKT_SIZE);
			TextOut(hdc,210,265,szBuffer1,lstrlen(szBuffer1));
			wsprintf(szBuffer1,"%d   ",delay1);
			TextOut(hdc,210,330,szBuffer1,lstrlen(szBuffer1));
			wsprintf(szBuffer1,"%d",SinkPacket);
			TextOut(hdc,210,385,szBuffer1,lstrlen(szBuffer1));
			MoveToEx(hdc,50,60,NULL);
			LineTo(hdc,90,60);
			MoveToEx(hdc,130,60,NULL);
			LineTo(hdc,160,45);
			MoveToEx(hdc,130,60,NULL);
			LineTo(hdc,160,75);
			MoveToEx(hdc,560,45,NULL);
			LineTo(hdc,600,45);
			MoveToEx(hdc,560,75,NULL);
			LineTo(hdc,600,75);
			MoveToEx(hdc,130,60,NULL);
			LineTo(hdc,160,15);
			MoveToEx(hdc,130,60,NULL);
			LineTo(hdc,160,105);
			MoveToEx(hdc,560,15,NULL);
			LineTo(hdc,600,15);
			MoveToEx(hdc,560,105,NULL);
			LineTo(hdc,600,105);
			Draw10Rect(hdc,160,65);
			Draw10Rect(hdc,160,35);
			Draw10Rect(hdc,160,5);
			Draw10Rect(hdc,160,95);
			Draw(hdc,0);
			DrawSink(hdc,1,0);
			DrawSink(hdc,2,0);
			DrawSink(hdc,3,0);
			DrawSink(hdc,4,0);
			TextOut(hdc,632,7,"S1",2);
			TextOut(hdc,632,37,"S2",2);
			TextOut(hdc,632,67,"S3",2);
			TextOut(hdc,632,97,"S4",2);
			//DrawText(hdc,"2002-Cem KARACA",15,&rt,	DT_BOTTOM | DT_RIGHT );
			EndPaint(hWnd, &ps);
			 
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

/* A thread of execution within the process. */
DWORD WINAPI Source(LPVOID param)
{
  	HDC hdc;
	
	unsigned long poisson=0;
	
	for(;;)
	{
		if(Check2==1) pkt=nexp(PKT_SIZE); else pkt=PKT_SIZE;
		Stack+=(int)pkt;
		BytesSent+=pkt/1024;
		hdc=GetDC(hWnd);
		SetBkColor(hdc,RGB(204,204,204));
		Draw(hdc,0);
		//wsprintf(szBuffer,"packets: %d and packet size is: %d and delay is %lu    ",count,(int)pkt,poisson);
		//TextOut(hdc,20,20,szBuffer,lstrlen(szBuffer));
		ReleaseDC(hWnd,hdc);
		count++;
		if(Check1==1) poisson =(unsigned long ) nexp(delay);else poisson=delay; // ~200 ms
		Sleep(poisson/2);
		hdc=GetDC(hWnd);
		SetBkColor(hdc,RGB(204,204,204));
		Draw(hdc,1);
		PacketsSent++;
		Sleep(poisson/2);
		DrawSink(hdc,1,2);
		DrawSink(hdc,2,2);
		DrawSink(hdc,3,2);
		DrawSink(hdc,4,2);
	if(Stack>0)
	{
		int min=0;
		
		switch(sc)
		{
		case 1:
			wsprintf(szBuffer1,"Round Robin Selected :S%d      ",rr+1);
			TextOut(hdc,220,135,szBuffer1,lstrlen(szBuffer1));
			switch(quanta1)
			{
			case 0:
				q1+=(Stack/SinkPacket);q1b+=Stack;Stack=0;q1s+=q1;
				ResumeThread(t2);
				Draw10RectR(hdc,(int)q1,1);
				break;
			case 1:
				q2+=(Stack/SinkPacket);q2b+=Stack;Stack=0;rr=2;q2s+=q2;
				ResumeThread(t3);
				Draw10RectR(hdc,(int)q2,2);
				break;
			case 2:
				q3+=(Stack/SinkPacket);q3b+=Stack;Stack=0;rr=3;q3s+=q3;
				ResumeThread(t5);
				Draw10RectR(hdc,(int)q3,3);
				break;
			case 3:
				q4+=(Stack/SinkPacket);q4b+=Stack;Stack=0;rr=0;q4s+=q4;
				ResumeThread(t6);
				Draw10RectR(hdc,(int)q4,4);
				break;
			}
			break;
		case 2:
			int ran;
			ran=rand() %4;
			wsprintf(szBuffer1,"Random Selected Server #:%d     ",ran+1);
			TextOut(hdc,220,135,szBuffer1,lstrlen(szBuffer1));
			switch(ran)
			{
			case 0:
				q1+=(Stack/SinkPacket);q1b+=Stack;Stack=0;q1s+=q1;
				ResumeThread(t2);
				Draw10RectR(hdc,(int)q1,1);
				break;
			case 1:
				q2+=(Stack/SinkPacket);q2b+=Stack;Stack=0;q2s+=q2;
				ResumeThread(t3);
				Draw10RectR(hdc,(int)q2,2);
				break;
			case 2:
				q3+=(Stack/SinkPacket);q3b+=Stack;Stack=0;q3s+=q3;
				ResumeThread(t5);
				Draw10RectR(hdc,(int)q3,3);
				break;
			case 3:
				q4+=(Stack/SinkPacket);q4b+=Stack;Stack=0;q4s+=q4;
				ResumeThread(t6);
				Draw10RectR(hdc,(int)q4,4);
				break;
			}
			break;
		case 3:
			
			if(q1<=q2 && q1<=q3 && q1<=q4) min =0;
			if(q2<=q1 && q2<=q3 && q2<=q4) min =1;
			if(q3<=q1 && q3<=q2 && q3<=q4) min =2;
			if(q4<=q1 && q4<=q2 && q4<=q3) min =3;
			wsprintf(szBuffer1,"Shortest Queue Selected: S%d      ",min+1);
			TextOut(hdc,220,135,szBuffer1,lstrlen(szBuffer1));
			switch(min)
			{
			case 0:
				q1+=(Stack/SinkPacket);q1b+=Stack;Stack=0;q1s+=q1;
				ResumeThread(t2);
				Draw10RectR(hdc,(int)q1,1);
				break;
			case 1:
				q2+=(Stack/SinkPacket);q2b+=Stack;Stack=0;q2s+=q2;
				ResumeThread(t3);
				Draw10RectR(hdc,(int)q2,2);
				break;
			case 2:
				q3+=(Stack/SinkPacket);q3b+=Stack;Stack=0;q3s+=q3;
				ResumeThread(t5);
				Draw10RectR(hdc,(int)q3,3);
				break;
			case 3:
				q4+=(Stack/SinkPacket);q4b+=Stack;Stack=0;q4s+=q4;
				ResumeThread(t6);
				Draw10RectR(hdc,(int)q4,4);
				break;
			}
			break;
		case 4:
			wsprintf(szBuffer1,"Periodically Selected :S%d      ",rr+1);
			TextOut(hdc,220,135,szBuffer1,lstrlen(szBuffer1));
			switch(rr)
			{
			case 0:
				q1+=(Stack/SinkPacket);rr=1;q1b+=Stack;Stack=0;q1s+=q1;
				ResumeThread(t2);
				Draw10RectR(hdc,(int)q1,1);
				break;
			case 1:
				q2+=(Stack/SinkPacket);rr=2;q2b+=Stack;Stack=0;rr=2;q2s+=q2;
				ResumeThread(t3);
				Draw10RectR(hdc,(int)q2,2);
				break;
			case 2:
				q3+=(Stack/SinkPacket);rr=3;q3b+=Stack;Stack=0;rr=3;q3s+=q3;
				ResumeThread(t5);
				Draw10RectR(hdc,(int)q3,3);
				break;
			case 3:
				q4+=(Stack/SinkPacket);rr=0;q4b+=Stack;Stack=0;rr=0;q4s+=q4;
				ResumeThread(t6);
				Draw10RectR(hdc,(int)q4,4);
				break;

			}
			break;


		}
	}

	ReleaseDC(hWnd,hdc);

	}
  return 0;
}

/* A thread of execution within the process. */
DWORD WINAPI Queue1(LPVOID param)
{
	HDC hdc;
	for(;;)
	{
		if(q1>0)
		{
			if(q1>=80) { q1L+=q1-80;q1bL+=(q1-80)*SinkPacket; }
			Sleep(delay1/2);
			hdc=GetDC(hWnd);
			Draw10RectG(hdc,(int)q1,1);
			q1--;
			DrawSink(hdc,1,1);
			ReleaseDC(hWnd,hdc);
			Sleep(delay1/2);
		} else SuspendThread(t2);
	}


  
  return 0;
}

/* A thread of execution within the process. */
DWORD WINAPI Queue2(LPVOID param)
{
	HDC hdc;
	for(;;)
	{
		if(q2>0)
		{
			if(q2>=80) { q2L+=q2-80; q2bL+=(q2-80)*SinkPacket; }
			Sleep(delay1/2);
			hdc=GetDC(hWnd);
			Draw10RectG(hdc,(int)q2,2);
			q2--;
			DrawSink(hdc,2,1);
			ReleaseDC(hWnd,hdc);
			Sleep(delay1/2);
		}  else SuspendThread(t3);
	}


  
  return 0;
}

/* A thread of execution within the process. */
DWORD WINAPI Queue3(LPVOID param)
{
	HDC hdc;
	for(;;)
	{
		if(q3>0)
		{
			
			if(q3>=80) { q3L+=q3-80; q3bL+=(q3-80)*SinkPacket; }
			Sleep(delay1/2);
			hdc=GetDC(hWnd);
			Draw10RectG(hdc,(int)q3,3);
			q3--;
			DrawSink(hdc,3,1);
			ReleaseDC(hWnd,hdc);
			Sleep(delay1/2);
			
		} else SuspendThread(t5);
		

	}
	return 0;
}

/* A thread of execution within the process. */
DWORD WINAPI Queue4(LPVOID param)
{
	HDC hdc;
	for(;;)
	{
		if(q4>0)
		{
			if(q4>=80) { q4L+=q4-80; q4bL+=(q4-80)*SinkPacket; }
			Sleep(delay1/2);			
			hdc=GetDC(hWnd);
			Draw10RectG(hdc,(int)q4,4);
			q4--;
			DrawSink(hdc,4,1);
			ReleaseDC(hWnd,hdc);
			Sleep(delay1/2);
		} else SuspendThread(t6);
	}
  return 0;
}



double nexp(double mean )		// Returns negative exponential of mean
{
	int i;
	double res;
	i = rand();
	res=(double)i/RAND_MAX;
	return(-mean*log(res) );
}


int Draw(HDC hdc,int status)
{
	if(status==1) SelectObject(hdc, hRed); else SelectObject(hdc, hGreen);
	RECT rt;
	rt.left=90,rt.right=130,rt.bottom=75,rt.top=45;
	FillRect(hdc,&rt,NULL);
	FrameRect(hdc,&rt,hBlack);
	Ellipse(hdc,10,45,50,75);
	return 0;
}

int Draw10Rect(HDC hdc,int x,int y)
{
	int i;RECT rect;
	rect.left=x,rect.right=x+401;rect.top=y,rect.bottom=y+20;
	FillRect(hdc,&rect,hGreen);
	FrameRect(hdc,&rect,hBlack);
	x+=5;
	for(i=0;i<79;i++)
	{
		MoveToEx(hdc,x,y,NULL);
		LineTo(hdc,x,y+20);
		x+=5;
	}
	return 0;
}

int Draw10RectR(HDC hdc,int level,int queue)
{
	if(level>=80) level=80;
	int x=560,y,i;RECT rect;
	if(queue==1) y=5; else if(queue==2)y=35;
	else if(queue==3)y=65; else if(queue==4)y=95;
	x-=level*5;
	for(i=0;i<level;i++)
	{
		rect.left=x,rect.right=x+6;rect.top=y,rect.bottom=y+20;
		FillRect(hdc,&rect,hRed);
		FrameRect(hdc,&rect,hBlack);
		x+=5;
	}
	return 0;
}



int Draw10RectG(HDC hdc,int level,int queue)
{
	int x=160,y,rev;
	if(queue==1) y=5;  else if(queue==2) y=35;
	else if(queue==3) y=65; else if(queue==4) y=95;
	rev=80-level;
	if(rev>=0)
	{
		x+=rev*5;
		RECT rect;
		rect.left=x,rect.right=x+6;rect.top=y,rect.bottom=y+20;
		FillRect(hdc,&rect,hGreen);
		FrameRect(hdc,&rect,hBlack);
	}
	return 0;
}

int DrawSink(HDC hdc,int Source,int status)
{
	if(status==1) SelectObject(hdc, hRed); else SelectObject(hdc, hGreen);
	if(Source==1) Ellipse(hdc,600,0,630,30); 
	else if(Source==2) Ellipse(hdc,600,30,630,60); 
	else if(Source==3)Ellipse(hdc,600,60,630,90);
	else if(Source==4) Ellipse(hdc,600,90,630,120); 
	return 0;
}

LRESULT CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR buffer[255];
	switch (message)
	{
		case WM_INITDIALOG:
			SetTimer(hDlg,1,500,NULL);	
			return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDC_BUTTON1 ) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			
			if (LOWORD(wParam) == IDC_BUTTON2 ) 
			{
				PacketsSent=0;q1s=q2s=q3s=q4s=0;
				BytesSent=q1b=q2b=q3b=q4b=0;
			}
			break;
		case WM_TIMER:
			wsprintf(buffer,"%d",PacketsSent);
			SetDlgItemText(hDlg,IDC_STAT1,buffer);
			wsprintf(buffer,"%d kB",(int)(BytesSent));
			SetDlgItemText(hDlg,IDC_STAT2,buffer);
			wsprintf(buffer,"%d",(int)(q1s-q1L));
			SetDlgItemText(hDlg,IDC_STAT3,buffer);
			wsprintf(buffer,"%d",(int)(q2s-q2L));
			SetDlgItemText(hDlg,IDC_STAT4,buffer);
			wsprintf(buffer,"%d",(int)(q3s-q3L));
			SetDlgItemText(hDlg,IDC_STAT5,buffer);
			wsprintf(buffer,"%d",(int)(q4s-q4L));
			SetDlgItemText(hDlg,IDC_STAT6,buffer);
			
			wsprintf(buffer,"%d",(int)q1L);
			SetDlgItemText(hDlg,IDC_STAT11,buffer);
			wsprintf(buffer,"%d",(int)q2L);
			SetDlgItemText(hDlg,IDC_STAT12,buffer);
			wsprintf(buffer,"%d",(int)q3L);
			SetDlgItemText(hDlg,IDC_STAT13,buffer);
			wsprintf(buffer,"%d",(int)q4L);
			SetDlgItemText(hDlg,IDC_STAT14,buffer);

			wsprintf(buffer,"%d",(int)q1bL/1024);
			SetDlgItemText(hDlg,IDC_STAT15,buffer);
			wsprintf(buffer,"%d",(int)q2bL/1024);
			SetDlgItemText(hDlg,IDC_STAT16,buffer);
			wsprintf(buffer,"%d",(int)q3bL/1024);
			SetDlgItemText(hDlg,IDC_STAT17,buffer);
			wsprintf(buffer,"%d",(int)q4bL/1024);
			SetDlgItemText(hDlg,IDC_STAT18,buffer);

			wsprintf(buffer,"%d kB",(int)q1b/1024);
			SetDlgItemText(hDlg,IDC_STAT7,buffer);
			wsprintf(buffer,"%d kB",(int)q2b/1024);
			SetDlgItemText(hDlg,IDC_STAT8,buffer);
			wsprintf(buffer,"%d kB",(int)q3b/1024);
			SetDlgItemText(hDlg,IDC_STAT9,buffer);
			wsprintf(buffer,"%d kB",(int)q4b/1024);
			SetDlgItemText(hDlg,IDC_STAT10,buffer);
			break;
	}
    return FALSE;
}
