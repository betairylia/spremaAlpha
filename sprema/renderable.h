#pragma once
class renderable
{
	public:
		renderable();
		virtual ~renderable();

		virtual void render(/*...*/) = 0;//���û��ƺ���
};

