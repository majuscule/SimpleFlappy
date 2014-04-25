#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    
    // add physics
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->getPhysicsWorld()->setGravity(Vect(0, -900));
    
    // add a layer to the scene
    auto layer = GameScene::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // add pipes layer
    m_pipes = Sprite::create();
    this->addChild(m_pipes);
    
    // add ground
    m_ground = Sprite::create("ground.png");
    auto groundSize = m_ground->getContentSize();
    m_ground->setPosition(Point(visibleSize.width/2,
                              groundSize.height/2));
    auto groundBody = PhysicsBody::createBox(groundSize);
    groundBody->setContactTestBitmask(true);
    m_ground->setPhysicsBody(groundBody);
    groundBody->setDynamic(false);
    this->addChild(m_ground, 0);
    
    
    // add start label
    auto label = LabelTTF::create("Start", "Arial", 48);
    auto item = MenuItemLabel::create(label,
                                      CC_CALLBACK_1(GameScene::startGame, this));
	item->setPosition(Point(visibleSize.width/2,
                               visibleSize.height/2));
    m_start = Menu::create(item, NULL);
    m_start->setPosition(Point::ZERO);
    this->addChild(m_start, 1);
    
    
    // add touch listner
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // add contact listner
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // schedule updating pipes
    this->schedule(schedule_selector(GameScene::runPipes), 0.01f);
    
    return true;
}
                         
void GameScene::startGame(Ref* pSender)
{
    m_flying = true;
    
    // clear from the previous run;
    if (m_bird != NULL) m_bird->removeFromParent();
    m_pipes->removeAllChildren();
    
    // hide start and add bird
    m_start->setVisible(false);
    this->addBird();
    
    // start updating pipes
    this->scheduleUpdate();
}


bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    if (m_flying)
        m_bird->getPhysicsBody()->setVelocity(Vect(0,260));
    return true;
}

void GameScene::addBird()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_bird = Sprite::create("bird.png");
    auto birdSize = m_bird->getContentSize();
    m_bird->setPosition(Point(visibleSize.width/2,
                              visibleSize.height/2));
    auto birdBody = PhysicsBody::createCircle(birdSize.width/2);
    birdBody->setContactTestBitmask(true);
    birdBody->setLinearDamping(0.0f);
    birdBody->setDynamic(true);
    birdBody->setGravityEnable(true);
    m_bird->setPhysicsBody(birdBody);
    this->addChild(m_bird, 0);
}

void GameScene::runPipes(float time)
{
    if (m_flying == false) return;

    // spacing between two pipes
    int space = 250;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Node * last = NULL;
    
    // slide and check the current pipes
    Vector< Node * > & pipes = m_pipes->getChildren();
    for (auto p : pipes)
    {
        if (p->getPositionX()+space<0)
            p->removeFromParent();
        else {
            p->setPositionX(p->getPositionX()-3);
            last = p;
        }
    }
    
    // time to add new pipes
    if (last == NULL || last->getPositionX()<visibleSize.width-space) {
        auto down = Sprite::create("down_pipe.png");
        auto downSize = down->getContentSize();
        auto up = Sprite::create("up_pipe.png");
        auto upSize = down->getContentSize();
        int gap = 200;
        Size groundSize = m_ground->getContentSize();
        int offset = visibleSize.height+rand()%int(upSize.height+downSize.height+gap
                                -visibleSize.height+groundSize.height);
        addPipe(up, visibleSize.width+upSize.width/2,
                offset-upSize.height/2);
        addPipe(down, visibleSize.width+downSize.width/2,
                offset-upSize.height-gap-downSize.height/2);
    }
    
}

void GameScene::addPipe(Sprite*pipe, int x, int y)
{
    auto pipeSize = pipe->getContentSize();
    pipe->setPosition(Point(x,y));
    auto pipeBody = PhysicsBody::createBox(pipeSize);
    pipeBody->setContactTestBitmask(true);
    pipeBody->setDynamic(false);
    pipeBody->setGravityEnable(false);
    pipe->setPhysicsBody(pipeBody);
    m_pipes->addChild(pipe);
    
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    m_flying = false;
    
    // add a bit action for collision
    m_bird->getPhysicsBody()->setVelocity(Vect(-50,50));
    
    m_start->setVisible(true);
    this->unscheduleUpdate();
    return true;
}



