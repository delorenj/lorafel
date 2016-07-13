//
// Created by Jarad DeLorenzo on 7/11/16.
//

#ifndef LORAFEL_GRID_H
#define LORAFEL_GRID_H

namespace lorafel {
    template<class T>
    class Grid {
    public:
        Grid() {
            m_pDic = new std::map<std::pair<int, int>, T>();
        }

        ~Grid() {
            delete m_pDic;
            m_pDic = nullptr;
        }

        void insert(T item, int x, int y) {
            auto loc = std::make_pair(x,y);
            insert(item, loc);
        }

        void insert(T item, std::pair<int, int> loc) {
            m_pDic->insert(make_pair(loc, item));
        }

        T get(int x, int y) {
            auto loc = std::make_pair(x,y);
            return get(loc);
        }

        T get(std::pair<int, int> loc) {
            return m_pDic->at(loc);
        }

        void swap(std::pair<int, int> loc1, std::pair<int, int> loc2) {
            auto temp = get(loc1);
            insert(get(loc2), loc1);
            insert(temp, loc1);
        }

    protected:
        std::map<std::pair<int, int>, T>* m_pDic;
    };
}

#endif //LORAFEL_GRID_H
