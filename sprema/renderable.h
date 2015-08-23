#pragma once
class renderable
{
	public:
		renderable();
		virtual ~renderable();

		virtual void render(/*...*/) = 0;//调用绘制函数
};

