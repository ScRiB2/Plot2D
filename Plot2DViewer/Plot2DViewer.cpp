#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene2D.h"
#include "Matrix.h"
#include "AffineTransform.h"
#include "Model2D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� �������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,400,400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Scene2D
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������
	
Scene2D scene(X0,Y0,px,py);

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch(msg)
	{
	case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);				// ����� �������������� � ������ Camera2D ������, ����������� �� ������� ������� ������� ���� hWnd
			//scene.Plot(dc, Parabola);		// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������
			//scene.ParametricPlot(dc, ParametricX, ParametricY);
			//scene.Polar(dc, ParametricX, ParametricY);
			scene.Render(dc);
			ReleaseDC(hWnd,dc);
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}

	case WM_SIZE:
		{
			HDC dc = GetDC(hWnd);
			scene.SetResolution(dc);
			ReleaseDC(hWnd,dc);
			InvalidateRect(hWnd,nullptr,false);
			return 0;
		}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case VK_LEFT:
			{
				scene.model.Apply(Translation(-0.5, 0));
				break;
			}
			case VK_RIGHT:
			{
				scene.model.Apply(Translation(0.5, 0));
				break;
			}
			case VK_UP:
			{
				scene.model.Apply(Translation(0, 0.5));
				break;
			}
			case VK_DOWN:
			{
				scene.model.Apply(Translation(0, -0.5));
				break;
			}
			case 0x51:
			{
				// Q
				scene.model.Apply(Rotation(M_PI_4 / 4));
				break;
			}
			case 0x45:
			{
				// E
				scene.model.Apply(Rotation(-M_PI_4 / 4));
				break;
			}
			case 0x41:
			{
				// A
				double x = scene.model.GetVertexX(1);
				double y = scene.model.GetVertexY(1);
				scene.model.Apply(Translation(-x, -y));
				scene.model.Apply(Rotation(M_PI_4 / 8));
				scene.model.Apply(Translation(x, y));
				break;
			}
			case 0x46:
			{
				// F
				double x1 = scene.model.GetVertexX(1);
				double y1 = scene.model.GetVertexY(1);
				double x2 = scene.model.GetVertexX(2);
				double y2 = scene.model.GetVertexY(2);
				scene.model.Apply(Reflection(x1, x2, y1, y2));
				break;
			}
		}
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	case WM_MOUSEWHEEL:
		{
			int s = GET_WHEEL_DELTA_WPARAM(wParam);
			scene.changeSize(s > 0 ? +1: -1);
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}

	case WM_LBUTTONDOWN:
		{
			scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	case WM_LBUTTONUP:
		{
			scene.StopDragging();
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if (scene.IsDragging())
			{
				scene.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}

	default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}
	return 0;
}
