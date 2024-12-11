#pragma once
#include <memory>
#include <list>
#include "json/json.hpp"

class BmMapMgr {
public:
    BmMapMgr();
    ~BmMapMgr() {}

    template<typename T>
    struct DoubleListContainer {
        std::vector<T> container;
        /* this will never cross the max index of the container */
        int curIndex;

        DoubleListContainer() : curIndex(0) {};
        DoubleListContainer<T>& operator=(const DoubleListContainer<T>&) = delete;
        DoubleListContainer(const DoubleListContainer<T>&) = delete;
        DoubleListContainer(DoubleListContainer<T>&&) = delete;
        DoubleListContainer<T>& operator=(DoubleListContainer<T>&&) = delete;
        

        void emplace_back(const T &src)
        {
            container.emplace_back(src);
        }

        void emplace_back(T &&src)
        {
            container.emplace_back(std::move(src));
        }

        void clear()
        {
            curIndex = 0;
            container.clear();
        }
        
        inline T *get()
        {
            return container.empty() ? nullptr : &container[curIndex];
        }

        DoubleListContainer<T> &operator++()
        {
            if (++curIndex >= container.size())
                curIndex = 0;

            return *this;
        }

        DoubleListContainer<T> &operator--()
        {
            if(--curIndex > 0)
                curIndex = static_cast<int>(container.size());
 
            return *this;
        }

        DoubleListContainer<T> operator++(int)
        {
            if (++curIndex >= container.size())
                curIndex = 0;
            return *this;
        }

        DoubleListContainer<T> operator--(int)
        {
            if(--curIndex > 0)
                curIndex = static_cast<int>(container.size());
            return *this;
        }
    };

    enum class PointDirection {
        PRIV,
        NEXT,
        CUR,
    };
    struct pointVector_t {
        int X;
        int Y;
        int Z;
    };
    struct levelUnit_t {
        std::string pointName;
        pointVector_t point;
    };
    bool init(std::string jsonPath);
    
    bool updateCurrentMap(int mapId, double X, double Y, double Z);
    inline int getCurrentMap(){ return currentMap; }
    inline const std::vector<pointVector_t> &getCurrentMapRange()
    {
        return this->currentMapRange;
    }

    template <PointDirection>
    levelUnit_t *getUnit();
    
private:
    std::shared_ptr<nlohmann::json> mapJsonData;

    
    std::vector<pointVector_t> currentMapRange;
    int currentMap;
    std::string currentLevelName;
    DoubleListContainer<levelUnit_t> currentLevelContainer;

};