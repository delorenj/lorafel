//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILE_H
#define LORAFEL_TILE_H

#include <vector>
#include <iostream>
#include "cocos2d.h"
#include "SwappyGrid.h"
#include "MatchPattern.h"
#include "StatResult.h"
#include "AIStrategy.h"
#include "TrajectoryParticle.h"
#include "Globals.h"

#define TILE_CENTER cocos2d::Vec2(getPosition().x+getContentSize().width/2, getPosition().y+getContentSize().height/2)
#define PTILE_CENTER(tile) cocos2d::Vec2(tile->getPosition().x + tile->getContentSize().width/2, tile->getPosition().y + tile->getContentSize().height/2)
#define PTILE_LEFT(tile) tile->getPosition()
#define PTILE_TOP(tile) cocos2d::Vec2(tile->getPosition().x, tile->getPosition().y + tile->getContentSize().height)
#define PTILE_RIGHT(tile) cocos2d::Vec2(tile->getPosition().x + tile->getContentSize().width, tile->getPosition().y)
#define PTILE_LEFT_CENTER(tile) cocos2d::Vec2(tile->getPosition().x, tile->getPosition().y + tile->getContentSize().height/2)
#define PTILE_TOP_CENTER(tile) cocos2d::Vec2(tile->getPosition().x + tile->getContentSize().width/2, tile->getPosition().y + tile->getContentSize().height)
#define PTILE_RIGHT_CENTER(tile) cocos2d::Vec2(tile->getPosition().x + tile->getContentSize().width, tile->getPosition().y + tile->getContentSize().height/2)
#define PTILE_BOTTOM_CENTER(tile) cocos2d::Vec2(tile->getPosition().x + tile->getContentSize().width/2, tile->getPosition().y)
namespace lorafel {
    class SwappyGrid;
    class StatResult;
    class Match;

    typedef std::vector<Tile*> TileColumn;
    typedef std::vector<TileColumn*> TileGrid;

    class Tile : public cocos2d::Sprite {

    public:
        typedef struct {
            int frequency;
            std::function<Tile*(void)> create;
        } TileConfig;

        typedef std::vector<TileConfig*> TileConfigs;

        enum Color {
            NONE,       // Has not been visited
            RED,        // Has been visited
            YELLOW,     // Is part of a complete axis match set
            GREEN,      // Is part of a match set
            BLACK       // Is not part of a match set
        };

        virtual bool init(cocos2d::ValueMap args);
        virtual void onExit() override {
            cocos2d::Node::onExit();
            removeAllChildrenWithCleanup(true);
        }
        virtual void onMatch(Match* pMatch);

//        CREATE_FUNC(Tile);
        static Tile* create(cocos2d::ValueMap args) {
            Tile *pRet = new(std::nothrow) Tile();
            if (pRet && pRet->init(args))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        const unsigned int MIN_MATCH_SIZE = 3;
        void addStatResult(StatResult* pStatResult) { m_pStatResults->insert(pStatResult); }
        std::set<StatResult *>* getStatResults() const { return m_pStatResults; };

        const std::string& getTileName() const;
        void setTileName(const std::string name);
        void setGrid(SwappyGrid* pGrid);
        SwappyGrid* getGrid();
        void initOptions();
        virtual void addEvents();
        Color getVisitColor() const { return m_color; }
        void setVisitColor(const Color color) { m_color = color; }
        virtual int getVisitOrder() const { return m_firstVisit; }
        virtual void setVisitOrder(int firstVisit) { Tile::m_firstVisit = firstVisit; }
        virtual std::string getVisitCountAsString();

        Tile* getLeft(lorafel::TileGrid *pGrid = nullptr) const;
        Tile* getTop(TileGrid* pGrid = nullptr) const;
        Tile* getBottom(TileGrid* pGrid = nullptr) const;
        Tile* getRight(TileGrid* pGrid = nullptr) const;
        const cocos2d::Vec2 getGridPos() const;
        const cocos2d::Vec2 getGridPosInTempGrid(TileGrid* pGrid) const;

        // Default tile matching algorithm is simple...
        // If the tiles have the same name, they match
        virtual bool isMatch(Tile* pTile) const { return pTile->getTileName() == this->getTileName(); };
        virtual const unsigned int getMinMatchSize() const { return MIN_MATCH_SIZE; };
        virtual void remove();
        virtual bool freelyMovable();
        void moveToGridPos(int x, int y);

        virtual bool isSwappable() { return true; }
        virtual bool isStackable() { return true; }
        virtual int getRandHit(Tile* pTile);

        void setHp(int hp) { m_hp = hp; }
        void setMaxHp(int hp) { m_maxHp = hp; }
        int getHp() const { return m_hp; }
        int getMaxHp() const { return m_maxHp; }

        AIStrategy* getStrategy() const { return m_pStrategy; };
        void setStrategy(AIStrategy* strategy) { m_pStrategy = strategy; }
        void showTrajectoryLine(cocos2d::Vec2 dest);
        void hideTrajectoryLine();
        void setGlow(const int color);
        virtual Tile* generateLootTile();

        TileConfigs* getLoot();

        void onHooked();
        int getId() { return m_id; }


    protected:
        int m_id;
        std::string m_tileName;
        std::string m_className;
        cocos2d::ValueMap m_arguments;
        SwappyGrid* m_pSwappyGrid;
        AIStrategy* m_pStrategy;
        Color m_color = NONE;
        int m_firstVisit = 0;
        int m_hp = 0;
        int m_maxHp = 0;
        cocos2d::ClippingRectangleNode* m_pClippingMask = nullptr;

        std::set<StatResult*>* m_pStatResults;
        /**
         *  Set of patterns to match against.
         *  i.e. Straight lines, Solid blocks,
         *  border blocks, etc..
         */
        std::set<MatchPattern*>* m_pMatchPatterns;
        cocos2d::Vec2 getSwapVec(cocos2d::Touch *pTouch);
        TrajectoryParticle* m_pTrajectoryLine = nullptr;
        TileConfigs* m_pLoot;
        bool m_animated = false;
        int m_animationType = AnimationType::NONE;

        void setAnimationFrames(std::string initialFrame);
        std::vector<std::string> m_frames;
    };
}

#endif //LORAFEL_TILE_H
