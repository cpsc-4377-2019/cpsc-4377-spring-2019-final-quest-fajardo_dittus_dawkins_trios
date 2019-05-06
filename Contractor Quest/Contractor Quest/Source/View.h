#ifndef VIEW_H
#define VIEW_H

class View {
	public:
		View();
		View(float, float);
		~View();

		//Getters
		float getPosX();
		float getPosY();

		void update(float);

	private:
		//Members
		float posX;
		float posY;
};

#endif