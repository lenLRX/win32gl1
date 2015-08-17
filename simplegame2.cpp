#include "stdafx.h"
#include "simplegame2.h"

using namespace std;
simplegame2::simplegame2(string name) :Scene(name), bulletInTheWorld(0), maxBulletInTheWorld(5)
{

}

simplegame2::~simplegame2()
{
	delete world;
}

void simplegame2::init()
{
	srand(time(NULL));
	initPhysics();
	Sprite* s = new Sprite("core2.png", 1);
	s->setpos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	s->setsize(20, 20);
	playerSprite = addchild(s);
	Director::getTheInstance()->registerKey(VK_A);    //注册键盘事件
	Director::getTheInstance()->registerKey(VK_S);
	Director::getTheInstance()->registerKey(VK_D);
	Director::getTheInstance()->registerKey(VK_W);
	Director::getTheInstance()->registerEvent(this, &simplegame2::shoot);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(200 / PTM_RATIO, 200 / PTM_RATIO);
	b2Body *body = world->CreateBody(&bodyDef);
	body->SetUserData(s);
	bodyDef.bullet = false;

	b2CircleShape circle;

	circle.m_p.Set(0.0f, 0.0f);

	circle.m_radius = 22.0f / PTM_RATIO;



	// 夹具定义
	b2FixtureDef fixtureDef;
	fixtureDef.restitution = 0.8f;
	//设置夹具的形状
	fixtureDef.shape = &circle;
	//设置密度
	fixtureDef.density = 1.0f;
	//设置摩擦系数
	fixtureDef.friction = 0.0f;
	fixtureDef.isSensor = true;
	//使用夹具固定形状到物体上	
	body->CreateFixture(&fixtureDef);
	playerBody = body;
	world->SetContactListener(this);
}

void simplegame2::update(float dt)
{
	if (playerSprite && !pausing)
	{
		Sprite* c = getChildByID(playerSprite);
		///////////////////
		//跟随鼠标
		/*
		POINT MOUSE = Director::getTheInstance()->getMousePos();
		Size s = c->getsize();
		c->setpos(MOUSE.x-s.width/2, MOUSE.y-s.height/2);
		*/
		Point pos = c->getpos();
		float speed = 10;
		if (_keys[VK_W])
		{
			pos.y += speed;
		}
		if (_keys[VK_S])
		{
			pos.y -= speed;
		}
		if (_keys[VK_D])
		{
			pos.x += speed;
		}
		if (_keys[VK_A])
		{
			pos.x -= speed;
		}
		if (pos.x > WINDOW_WIDTH)
		{
			pos.x = WINDOW_WIDTH;
		}
		if (pos.y > WINDOW_HEIGHT)
		{
			pos.y = WINDOW_HEIGHT;
		}
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (pos.y < 0)
		{
			pos.y = 0;
		}
		c->setpos(pos);
		playerBody->SetTransform(b2Vec2(pos.x / PTM_RATIO, pos.y / PTM_RATIO), 0.0f);
		//Point mouse = Director::getTheInstance()->getMousePos();

		//c->setrotation(atan2(mouse.y - pos.y, mouse.x - pos.x) + 90.0 / 180 * M_PI);

	}

	float timeStep = dt;
	int32 velocityIterations = 8;
	int32 positionIterations = 1;

	world->Step(timeStep, velocityIterations, positionIterations);


	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr) {
			Sprite* sprite = (Sprite*)b->GetUserData();
			Point pt;
			pt.x = b->GetPosition().x *	PTM_RATIO;
			pt.y = b->GetPosition().y * PTM_RATIO;
			sprite->setpos(pt);
			float rot = b->GetAngle();
			sprite->setrotation(rot);
		}
		else
		{
			break;
		}
	}
}

void simplegame2::initPhysics()
{
	b2Vec2 gravity;

	gravity.Set(0.0f, 0.0f);

	world = new b2World(gravity);

	world->SetAllowSleeping(true);

	world->SetContinuousPhysics(true);

	b2BodyDef groundBodyDef;

	groundBodyDef.position.Set(0, 0);

	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2EdgeShape groundBox;

	groundBox.Set(b2Vec2(0, 0), b2Vec2(WINDOW_WIDTH / PTM_RATIO, 0));

	groundBody->CreateFixture(&groundBox, 0);

	groundBox.Set(b2Vec2(0, WINDOW_HEIGHT / PTM_RATIO), b2Vec2(WINDOW_WIDTH / PTM_RATIO, WINDOW_HEIGHT / PTM_RATIO));

	groundBody->CreateFixture(&groundBox, 0);

	groundBox.Set(b2Vec2(0, WINDOW_HEIGHT / PTM_RATIO), b2Vec2(0, 0));

	groundBody->CreateFixture(&groundBox, 0);

	groundBox.Set(b2Vec2(WINDOW_WIDTH / PTM_RATIO, WINDOW_HEIGHT / PTM_RATIO), b2Vec2(WINDOW_WIDTH / PTM_RATIO, 0));

	groundBody->CreateFixture(&groundBox, 0);
}

void simplegame2::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	Sprite* spriteA = (Sprite*)bodyA->GetUserData();
	Sprite* spriteB = (Sprite*)bodyB->GetUserData();
	if (spriteA&&spriteB)
	{
		if (spriteA->getid() == playerSprite)
		{
			world->DestroyBody(bodyB);
			removeChildByID(spriteB->getid());
		}
		else if (spriteB->getid() == playerSprite)
		{
			world->DestroyBody(bodyA);
			removeChildByID(spriteA->getid());
		}

	}
}

void simplegame2::shoot(EventMsg msg)
{
	if (msg._event.type == DOWN&&playerSprite)
	{
		Sprite* sprite = new Sprite("CloseNormal.png", 0);
		addchild(sprite);
		Sprite* c = getChildByID(playerSprite);
		Point pt = c->getpos();
		Point p = msg._event.point;
		sprite->setsize(32, 32);
		sprite->setpos(pt);

		float dir = atan2(p.y - pt.y, p.x - pt.x);

		//物体定义
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(pt.x / PTM_RATIO, pt.y / PTM_RATIO);
		b2Body *body = world->CreateBody(&bodyDef);
		body->SetUserData(sprite);
		bodyDef.bullet = true;

		b2CircleShape circle;

		circle.m_p.Set(0.0f, 0.0f);

		circle.m_radius = 0.5f;



		// 夹具定义
		b2FixtureDef fixtureDef;
		fixtureDef.restitution = 1.0f;
		//设置夹具的形状
		fixtureDef.shape = &circle;
		//设置密度
		fixtureDef.density = 1.0f;
		//设置摩擦系数
		fixtureDef.friction = 0.0f;
		//使用夹具固定形状到物体上	
		body->CreateFixture(&fixtureDef);
		//body->ApplyLinearImpulse(b2Vec2(rand() / (float)RAND_MAX * 10, rand() / (float)RAND_MAX * 10), b2Vec2(1.0f, 1.0f), true);
		b2MassData massdata;
		body->GetMassData(&massdata);
		float Velocity = 20;
		body->SetLinearVelocity(b2Vec2(Velocity*cos(dir), Velocity*sin(dir)));
		body->SetAngularVelocity((0.5 - rand() / (float)RAND_MAX));
	}
}

void simplegame2::clean()
{
	//第一步：删除精灵
	if (_sprites.size())
	{
		vector<Sprite*>::iterator it = _sprites.begin();
		while (it != _sprites.end())
		{
			delete (*it);
			it = _sprites.erase(it);
		}
	}

	if (_keyBoardEventList.size())
	{
		vector<Sprite*>::iterator it = _keyBoardEventList.begin();
		while (it != _keyBoardEventList.end())
		{
			it = _keyBoardEventList.erase(it);
		}
	}
	if (_mouseEventList.size())
	{
		vector<Sprite*>::iterator it = _mouseEventList.begin();
		while (it != _mouseEventList.end())
		{
			it = _mouseEventList.erase(it);
		}
	}
	//第二步，删除世界
	delete world;
}