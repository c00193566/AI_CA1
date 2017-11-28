#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Init(string Tag, string path, Vector2f position)
{
	Type = Tag;

	if (!(PlayerTexture.loadFromFile(path)))
	{
		cout << "Could not load texture for player" << endl;
		return false;
	}

	PlayerSprite.setTexture(PlayerTexture);

	PlayerSprite.setOrigin(8.0f, 8.0f);

	Position = position;
	PlayerSprite.setPosition(Position);

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 0.0f;

	Friction = 0.8f;

	return true;
}

bool Player::Init(string Tag, string Path, float x, float y)
{
	Type = Tag;

	if (!(PlayerTexture.loadFromFile(Path)))
	{
		cout << "Could not load texture for player" << endl;
		return false;
	}

	PlayerSprite.setTexture(PlayerTexture);

	PlayerSprite.setOrigin(8.0f, 8.0f);

	Position = Vector2f(x, y);
	PlayerSprite.setPosition(Position);

	Velocity = Vector2f(0, 0);

	Orientation = 0.0f;

	Speed = 0.0f;

	Friction = 0.1f;

	return true;
}

void Player::Update(unsigned int DT)
{
	Movement();
	SetVelocity();
}

void Player::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(PlayerSprite);
}

void Player::Movement()
{
	Position += Velocity;

	PlayerSprite.setPosition(Position);
}

void Player::Input(string Movement)
{
	// Orientation of sprite
	if (Movement == "RIGHT")
	{
		Orientation += 1.0f;
	}
	else if (Movement == "LEFT")
	{
		Orientation -= 1.0f;
	}

	PlayerSprite.setRotation(Orientation);

	// Speed of player
	if (Movement == "UP")
	{
		if (Speed < MaxSpeed)
		{
			Speed += 0.05f;
			cout << Speed << endl;
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
}