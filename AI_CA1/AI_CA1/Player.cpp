#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Init(string Tag, Vector2f position)
{
	Type = Tag;

	TextureHandler = TextureLoader::Instance();

	PlayerTexture = TextureHandler->getTexture("Player");

	PlayerSprite.setTexture(PlayerTexture);

	PlayerSprite.setOrigin(PlayerTexture.getSize().x / 2, PlayerTexture.getSize().y / 2);

	Position = position;
	PlayerSprite.setPosition(Position);

	HeartTexture = TextureHandler->getTexture("Heart");
	HeartPosition = Vector2f(280, 157);

	for (int i = 0; i < 3; i++)
	{
		Differences.push_back(Vector2f(0, 0));
		Hearts.push_back(Sprite());
		Hearts.at(i).setTexture(HeartTexture);
		Differences.at(i) = HeartPosition - Position;
		HeartPosition.x += 70;
		Hearts.at(i).setPosition(Position + Differences.at(i));
	}

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 0.0f;

	WorkersCollected = 0;
	MaxWorkers = 2;

	if (!Font.loadFromFile("Assets/OpenSans.ttf"))
	{
		cout << "Font not loaded" << endl;
	}

	TextPosition = Vector2f(500, 170);
	TextDifference = TextPosition - Position;

	WorkerText.setFont(Font);
	WorkerText.setPosition(Position + TextDifference);
	WorkerText.setFillColor(Color::White);
	WorkerText.setCharacterSize(24);
	WorkerText.setString("Workers Collected: " + to_string(WorkersCollected) + "/" + to_string(MaxWorkers));
	return true;
}

bool Player::Init(string Tag, Texture & LoadedTexture, float x, float y)
{
	Type = Tag;

	PlayerTexture = LoadedTexture;

	PlayerSprite.setTexture(PlayerTexture);

	PlayerSprite.setOrigin(8.0f, 8.0f);

	Position = Vector2f(x, y);
	PlayerSprite.setPosition(Position);

	HeartTexture = TextureHandler->getTexture("Heart");
	HeartPosition = Vector2f(0, 0);

	for (int i = 0; i < 3; i++)
	{
		cout << HeartPosition.x << " , " << HeartPosition.y << endl;
		Hearts.push_back(Sprite());
		Hearts.at(i).setTexture(HeartTexture);
		Hearts.at(i).setPosition(HeartPosition);
		HeartPosition.x + 70;
	}

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 0.0f;

	return true;
}

void Player::Update(unsigned int DT)
{
	WorkerText.setPosition(Position + TextDifference);

	for (int i = 0; i < Lives; i++)
	{
		Hearts.at(i).setPosition(Position + Differences.at(i));
	}

	Movement();
	SetVelocity();
}

void Player::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(PlayerSprite);
	Renderer->RenderText(WorkerText);

	for (int i = 0; i < Hearts.size(); i++)
	{
		Renderer->RenderSprite(Hearts.at(i));
	}
	
}

void Player::Movement()
{
	Position +=  Velocity;

	cout << Position.x << " , " << Position.y << endl;

	PlayerSprite.setPosition(Position);
}

void Player::Input(string Movement)
{
	// Orientation of sprite
	if (Movement == "RIGHT")
	{
		Orientation += 2.0f;
	}
	else if (Movement == "LEFT")
	{
		Orientation -= 2.0f;
	}

	PlayerSprite.setRotation(Orientation);

	// Speed of player
	if (Movement == "UP")
	{
		if (Speed < MaxSpeed)
		{
			Speed += 0.05f;
		}
	}
	else if (Movement == "DOWN")
	{
		if (Speed > MinSpeed)
		{
			Speed -= 0.05f;

			if (Speed < MinSpeed)
			{
				Speed = MinSpeed;
			}
		}
	}
}

void Player::SetVelocity()
{
	Velocity = Vector2f(sin((Orientation / 180 * 3.14f)), -cos((Orientation / 180 * 3.14f)));
	Velocity = Vector::Normalise(Velocity);
	Speed *= 0.99f;
	Velocity *= Speed;
}

void Player::Collision(string ObjType)
{
	if(ObjType == "Wall")
	{
		Position -= Velocity * MaxSpeed;
		PlayerSprite.setPosition(Position);
		Speed = 0;
	}
	else if (ObjType == "AlienNest")
	{
		Position -= Velocity * MaxSpeed;
		PlayerSprite.setPosition(Position);
		Speed = 0;
	}
	else if (ObjType == "Worker")
	{
		WorkersCollected++;
		WorkerText.setString("Workers Collected: " + to_string(WorkersCollected) + "/" + to_string(MaxWorkers));

		if (WorkersCollected >= MaxWorkers)
		{
			//game win
			WorkerText.setString("Winner");
		}
	}
	else if (ObjType == "Missile")
	{
		if (Lives > 0)
		{
			Lives--;
			Hearts.pop_back();
		}
		cout << Lives << endl;
	}
}