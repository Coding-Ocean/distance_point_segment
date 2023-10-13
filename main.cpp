#define A_
#ifdef A_
#include<windows.h>
#include "libOne.h"
void gmain()
{
	window(1000, 1000);
	hideCursor();
	COLOR col1{ 200,200,200 };
	COLOR col2{ 0,200,200 };
	COLOR col3{ 190,190,0 };
	COLOR col4{ 250,0,250 };
	VECTOR a{ 300,700 };
	VECTOR b{ 700,300 };
	VECTOR p{ 100,100 };
	bool clampFlag = true;

	POINT pt{ 350, 350 };
	ClientToScreen(HWnd, &pt);
	SetCursorPos(pt.x, pt.y);

	while (notQuit)
	{
		clear(0);
		if (isTrigger(KEY_SPACE))clampFlag = !clampFlag;
		p = { mouseX,mouseY };
		VECTOR ab = b - a;
		VECTOR ap = p - a;
		float t = dot(ab, ap) / dot(ab, ab);	float save_t = t;
		if (clampFlag) if (t > 1)t = 1; else if (t < 0)t = 0;
		float d = (ap - ab * t).mag() / 500;

		//ベクトルapに垂直な線
		strokeWeight(1);
		stroke(170);
		line(a.x, a.y, a.x - ab.y, a.y + ab.x);
		line(a.x, a.y, a.x + ab.y, a.y - ab.x);
		line(b.x, b.y, b.x - ab.y, b.y + ab.x);
		line(b.x, b.y, b.x + ab.y, b.y - ab.x);

		//メイン図形
		arrow(a, b, col1, 5);
		arrow(a, p, col1, 5);
		line(a + ab * t, p, col3, 5);
		line(a, a + ab * t, col1, 1);
		point(a + ab * t, col2, 15);
		point(a, col2, 15);
		point(b, col2, 15);
		point(p, col2, 15);

		//図中文字
		text("a", VECTOR(a.x - ab.x * 0.05f, a.y - ab.y * 0.05f), BCENTER, col2, 50);
		text("b", VECTOR(b.x + ab.x * 0.05f, b.y + ab.y * 0.05f), BCENTER, col2, 50);
		ap.normalize();
		text("p", p.x + ap.x * 33, p.y + ap.y * 33);
		text("→", VECTOR(a.x + ab.x * t + 2, a.y + ab.y * t - 15), TOP, col2, 50);
		text("ab", VECTOR(a.x + ab.x * t, a.y + ab.y * t + 20), TOP, col2, 50);
		text("  *", VECTOR(a.x + ab.x * t, a.y + ab.y * t + 20), TOP, col1, 50);
		text("   t", VECTOR(a.x + ab.x * t, a.y + ab.y * t + 20), TOP, col4, 50);

		//上部文字列
		textSize(40);
		fill(col4);
		float x = 200;
		char buf[32];
		sprintf_s(buf, "%3.2f", save_t);
		text(let("t=") + buf, 0, 0); text("t=dot(ab, ap) / dot(ab, ab)", x, 0);
		if (clampFlag) {
			fill(col4);
			sprintf_s(buf, "%3.2f", t);
			text(let("t=") + buf, 0, 50); text("t=clamp(t, 0, 1)", x, 50);
			fill(col3);
			sprintf_s(buf, "%3.2f", d);
			text(let("d=") + buf, 0, 100); text("d=length(ap - ab * t)", x, 100);
		}
		else {
			fill(col3);
			sprintf_s(buf, "%3.2f", d);
			text(let("d=") + buf, 0, 100); text("d=length(ap - ab * t)", x, 100);
		}
	}
}
#endif
#ifdef B_
#include "libOne.h"
void gmain()
{
	window(1000, 1000);
	COLOR col1{ 200,200,200 };
	COLOR col2{ 0,200,200 };
	COLOR col3{ 190,190,0 };
	COLOR col4{ 250,0,250 };
	VECTOR a{ 0,100 };
	VECTOR b{ 150,450 };
	hideCursor();
	bool flag = true;
	float cnt = 0;
	angleMode(RADIANS);
	while (notQuit)
	{
		clear(0);
		a.x = 500 + Cos(0 + cnt) * 200;
		a.y = 500 - Cos(1 + cnt) * 200;
		b.x = 500 + Cos(1.5 + cnt) * 200;
		b.y = 500 - Cos(4.5 + cnt) * 200;
		cnt += 0.01f;
		strokeWeight(20);
		stroke(0, 200, 200);
		point(a.x, a.y);

		stroke(200, 200, 0);
		point(b.x, b.y);

		strokeWeight(5);
		stroke(200);
		line(a.x, a.y, b.x, b.y);
	}
}
#endif
