#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

Color blue = { 14, 54, 124, 255 };
Color yellow = { 251, 162, 87, 255 };
Color red = { 244, 66, 66, 255 };

int cellSize = 30;
int cellCount = 25;

class Snake {
public:
	deque<Vector2> body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
	Vector2 direction = { 1,0 };

	void Draw()
	{
		for (unsigned int i = 0; i < body.size(); i++)
		{
			float x = body[i].x;
			float y = body[i].y;
			Rectangle segment = Rectangle{ x * cellSize, y * cellSize, (float)cellSize, (float)cellSize };
			DrawRectangleRounded(segment, 0.5, 6, yellow);

		}
	}

	void Update()
	{
		body.pop_back();
		body.push_front(Vector2Add(body[0], direction));

	}

};

class Food {
public:
	Vector2 position ;
	Texture2D texture;

	//food constructor
	Food()
	{
		Image image = LoadImage("C:/Users/abdullah/source/repos/HelloWorld/HelloWorld/bullet.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPos();
	}

	//food destructor
	~Food()
	{
		UnloadTexture(texture);
	}

	//drawing the food
	void Draw() 
	{
		DrawTexture(texture, position.x*cellSize, position.y*cellSize, WHITE);
	}
	
	//places food at random locations each time
	Vector2 GenerateRandomPos()
	{
		float x = GetRandomValue(0, cellCount - 1); 
		float y = GetRandomValue(0, cellCount - 1);
		return Vector2{ x, y };
	}
};

int main() 
{
	cout << "starting the game..." << endl;
	InitWindow(cellSize*cellCount, cellSize*cellCount, "My Snake");
	SetTargetFPS(60);

	Food food = Food();
	Snake snake = Snake();

	while(WindowShouldClose() == false)
	{
		BeginDrawing();

		// Drawing
		ClearBackground(blue);
		food.Draw();
		snake.Draw();
		snake.Update(); 
		EndDrawing();

	}

	CloseWindow();
	return 0;
}

