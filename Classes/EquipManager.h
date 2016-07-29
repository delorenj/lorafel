//
// Created by Jarad DeLorenzo on 7/29/16.
//

#ifndef LORAFEL_EQUIPSTATUS_H
#define LORAFEL_EQUIPSTATUS_H

namespace lorafel {
    class EquipManager : public cocos2d::Node {
    public:
        bool init() override;
        CREATE_FUNC(EquipManager);

        std::string getItemNameByEquipMask(int mask) const;
        void setEquippedItem(int mask, std::string itemName);

    protected:
        cocos2d::UserDefault* m_pData;
    };
}

#endif //LORAFEL_EQUIPSTATUS_H
