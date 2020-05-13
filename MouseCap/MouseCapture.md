//code MouseCapture
/*
    关于鼠标的捕获与画橡皮线
*/

#### 1.利用鼠标的移动画橡皮线
一般来说利用鼠标的移动划线, 会画一片黑色

代码:

![图示](https://raw.githubusercontent.com/konalo-X/pic/master/20200513220434.gif)

```cpp

//目的是随着鼠标的移动画虚线,但是画过的线一直存在所以一片漆黑
void CMainWindow::InvertLine(CDC* pDC, CPoint ptFrom, CPoint ptTo)
{
    CPen pen(PS_DASH, 0, RGB(0, 0, 0));
    HGDIOBJ oldPen =pDC->SelectObject(pen);
    pDC->MoveTo(ptFrom);
    pDC->LineTo(ptTo);
    pDC->SelectObject(oldPen);
}
//移动鼠标划线

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point)
{
    CClientDC dc(this);
    //CPoint ptTmp(point);
    if (m_bTracking)
    {
        //避免画的虚线被覆盖变成实线
        dc.SetBkMode(TRANSPARENT);
        //用来擦掉上一条画的线
        InvertLine(&dc, m_ptFrom, m_ptTo);
        //画当前的线
        InvertLine(&dc, m_ptFrom, point);
        m_ptTo = point;
        
    }
}
```
利用SetROP2函数可以有效擦除已画的线

```cpp
//原型:
//Sets the current drawing mode. 
int SetROP2(
   int nDrawMode 
);


```
![图片](https://raw.githubusercontent.com/konalo-X/pic/master/20200513224747.png)

效果:
![图片](https://raw.githubusercontent.com/konalo-X/pic/master/20200513223314.gif)

代码:
利用颜色反转来划线,之前的旧线
```cpp
void CMainWindow::InvertLine(CDC* pDC, CPoint ptFrom, CPoint ptTo)
{
    int nOldMode = pDC->SetROP2(R2_NOT);
    CPen pen(PS_DASH, 0, RGB(0, 0, 0));
    HGDIOBJ oldPen =pDC->SelectObject(pen);
    pDC->MoveTo(ptFrom);
    pDC->LineTo(ptTo);
    pDC->SelectObject(oldPen);
    pDC->SetROP2(nOldMode);
}

```

#### 2.利用鼠标的捕获***SetCapture***与***ReleaseCapture***
与***GetCapture***
```c++
void CMainWindow::OnLButtonDown(UINT nFlags,CPoint point)
{
    //避免鼠标移出客户区无法捕获
    if(m_bCaptureEnabled)
        SetCapture();

    m_bTracking = TRUE;
    m_ptFrom = point;
    m_ptTo = point;
   

}
```

**无法捕获的效果**
![图片](https://raw.githubusercontent.com/konalo-X/pic/master/20200513225606.gif)

```C++

void CMainWindow::OnLButtonUp(UINT nFlags,CPoint point)
{
    

  
    if (m_bTracking)
    {
        m_bTracking = FALSE;
        //getcapture 返回捕获鼠标的对象
        if(GetCapture()==this)
        //释放捕获
            ::ReleaseCapture();
    }
	CClientDC dc(this);

	InvertLine(&dc, m_ptFrom, point);

	CPen RedPen(PS_SOLID, 16, RGB(255, 0, 0));
	HGDIOBJ OldPen = dc.SelectObject(RedPen);

	dc.MoveTo(m_ptFrom);
	dc.LineTo(point);
    dc.SelectObject(OldPen);
}

```

#### 3.NCMessage的处理-要传递给父类默认处理函数处理

```cpp
/*
       m_bCaptureEnabled = m_bCaptureEnabled ? FALSE : TRUE;用于频繁改变FALSE/TRUE的写法
*/
void CMainWindow::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    if (nHitTest == HTCAPTION)
    {
       m_bCaptureEnabled = m_bCaptureEnabled ? FALSE : TRUE;
       SetWindowText( m_bCaptureEnabled ? _T("Mouse Capture Demo(capture Enabled)"):_T("Mouse Capture Demo(capture Disabled)"));
    }
    //传递给父类默认处理函数处理
    CFrameWnd::OnNcLButtonDown(nHitTest, point);
    
}
```

