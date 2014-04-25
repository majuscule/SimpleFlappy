#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}
    
private:
    cocos2d::PhysicsWorld* m_world;
    cocos2d::Sprite* m_ground;
    cocos2d::Sprite* m_bird;
    cocos2d::Sprite* m_pipes;
    cocos2d::Menu* m_start;
    
    bool m_flying = false;
    
    void addBird();
    void startGame(Ref* pSender);
    
    void runPipes(float time);
    void addPipe(cocos2d::Sprite*pipe, int x, int y);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
    
};

#endif // __GAME_SCENE_H__
