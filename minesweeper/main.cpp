#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(400, 400), "Minesweeper Minigame");

	int w = 32; // Sprite width
	int grid[12][12]; // For check
	int spriteGrid[12][12]; // For showing

	Texture texture;
	texture.loadFromFile("images/tiles.jpg");
	Sprite sprite(texture);

	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			spriteGrid[i][j] = 10;

			if ((rand() % 5) == 0) {
				grid[i][j] = 9;
			}
			else {
				grid[i][j] = 0;
			}
		}
	}

	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			int bombs = 0;

			if (grid[i][j] == 9) continue;

			if (grid[i - 1][j - 1] == 9) bombs++;
			if (grid[i    ][j - 1] == 9) bombs++;
			if (grid[i + 1][j - 1] == 9) bombs++;
			if (grid[i - 1][j    ] == 9) bombs++;
			if (grid[i + 1][j    ] == 9) bombs++;
			if (grid[i - 1][j + 1] == 9) bombs++;
			if (grid[i    ][j + 1] == 9) bombs++;
			if (grid[i + 1][j + 1] == 9) bombs++;

			grid[i][j] = bombs;
		}
	}

	while (app.isOpen()) {

		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;
		
		Event e;

		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.key.code == Mouse::Left) {
					spriteGrid[x][y] = grid[x][y];
				}
				else if (e.key.code == Mouse::Right) {
					spriteGrid[x][y] = 11;
				}
			}
		}

		app.clear(Color::White);

		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {

				if ((x >= 1 && x <= 10) && (y >= 1 && y <= 10) && (spriteGrid[x][y] == 9)) {
					spriteGrid[i][j] = grid[i][j];
				}

				sprite.setTextureRect(IntRect(spriteGrid[i][j] * w, 0, w, w));
				sprite.setPosition(i * w, j * w);
				app.draw(sprite);
			}
		}

		app.display();
	}

	return 0;
}
