#include "Player.h"
#include "Cube.h"

void Player::ReduceAmmo()
{
	ammo--;
}

void Player::ReloadGun()
{
	ammo = clipSize;
}

void Player::ReduceHealth(float damage)
{
	health -= damage;
}

void Player::Shoot(std::unique_ptr<class Cube> &bullet)
{
	//shoot
	bullet->setBullet();
	bullet->setRot(wnd.Gfx().cam.getYaw());
	bullet->setScale(0.2f, 0.2f, 0.2f);
	bullet->setPos(wnd.Gfx().cam.getPos().x + sin(wnd.Gfx().cam.getYaw()), 0, wnd.Gfx().cam.getPos().z + cos(wnd.Gfx().cam.getYaw()));

	ReduceAmmo();
}

XMFLOAT3 Player::GetPos()
{
	return playerPos;
}

Camera& Player::PlayerCam()
{
	return playerCam;
}

void Player::Move(float delta)
{
	dt = delta;
	if(input.KeyIsPressed('A'))
	{
		traveling = direction::left;
	}
	else if (input.KeyIsPressed('D'))
	{
		traveling = direction::right;
	}
	else if (input.KeyIsPressed('W'))
	{
		traveling = direction::forward;
	}
	else if (input.KeyIsPressed('S'))
	{
		traveling = direction::back;
	}
	if (input.KeyIsPressed('Q'))
	{
		playerCam.Rotate(-speed * dt, 0.0f);
	}
	else if (input.KeyIsPressed('E'))
	{
		playerCam.Rotate(speed * dt, 0.0f);
	}
	if (input.KeyIsPressed('O'))
	{
		playerCam.Rotate(0.0f, speed * dt);
	}
	else if (input.KeyIsPressed('P'))
	{
		playerCam.Rotate(0.0f, -speed * dt);
	}

	Translate(traveling);
	playerCam.UpdateCamera();
	playerPos = playerCam.getPos();
	traveling = direction::stationary;
}

int Player::GetAmmoAmount()
{
	return ammo;
}

void Player::Translate(direction dir)
{
	switch (dir)
	{
	case Player::direction::stationary:
		break;
	case Player::direction::forward:
		playerCam.Translate(0.0f, speed * dt);
		break;
	case Player::direction::back:
		playerCam.Translate(0.0f, -speed * dt);
		break;
	case Player::direction::left:
		playerCam.Translate(-speed * dt, 0.0f);
		break;
	case Player::direction::right:
		playerCam.Translate(speed * dt, 0.0f);
		break;
	}
}