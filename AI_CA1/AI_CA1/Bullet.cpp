#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(string Tag, Texture & LoadedTexture, Vector2f InputPosition, float Direction)
{
	Type = Tag;

	BulletTexture = LoadedTexture;

	BulletSprite.setTexture(BulletTexture);

	BulletSprite.setOrigin(BulletTexture.getSize().x / 2, BulletTexture.getSize().x / 2);

	Position = InputPosition;

	BulletSprite.setPosition(Position);

	Velocity = Vector2f(sin((Direction / 180 * 3.14f)), -cos((Direction / 180 * 3.14f)));
	Velocity = Vector::Normalise(Velocity);

	Speed = 8.0f;

	Alive = true;

	TimeAlive = 0;
}

Bullet::~Bullet()
{

}

void Bullet::Render(RenderSystem * Renderer)
{
	Renderer->RenderSprite(BulletSprite);
}

void Bullet::Update(unsigned int DT)
{
	Position += Velocity * Speed;
	BulletSprite.setPosition(Position);

	TimeAlive += DT / 600.0f;

	if (TimeAlive > 1.0f)
	{
		Dead();
	}
}

void Bullet::Dead()
{
	Alive = false;
}