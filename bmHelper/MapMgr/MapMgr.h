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

        static_assert(std::is_move_constructible<T>::value, "T must be move constructible");

        DoubleListContainer() : curIndex(0) {};
        DoubleListContainer<T>& operator=(const DoubleListContainer<T>&src) noexcept
        {
            if (&src != this) {
                container = src.container;
                curIndex = src.curIndex;
                if (src.curIndex < 0 || src.curIndex >= src.container.size())
                    curIndex = 0;
            }
            return *this;
        }
        DoubleListContainer(const DoubleListContainer<T>& src) noexcept
        {
            container = src.container;
            curIndex = src.curIndex;
            if (src.curIndex < 0 || src.curIndex >= src.container.size())
                curIndex = 0;

        }
        DoubleListContainer(DoubleListContainer<T>&& src) noexcept
            : container(std::move(src.container)), curIndex(src.curIndex)
        {
            if (src.curIndex < 0 || src.curIndex >= src.container.size())
                curIndex = 0;
        }

        DoubleListContainer<T>& operator=(DoubleListContainer<T>&& src) noexcept
        {
            if (this != &src) {
                container = std::move(src.container);
                curIndex = src.curIndex;
                if(src.curIndex < 0 || src.curIndex >= src.container.size())
                    curIndex = 0;
            }
            return *this;
        }
        

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
            if (++curIndex > container.size() - 1)
                curIndex = 0;

            return *this;
        }

        DoubleListContainer<T> &operator--()
        {
            if(--curIndex < 0)
                curIndex = static_cast<int>(container.size() - 1);
 
            return *this;
        }

        DoubleListContainer<T> operator++(int)
        {
            if (++curIndex > container.size() - 1)
                curIndex = 0;
            return *this;
        }

        DoubleListContainer<T> operator--(int)
        {
            if(--curIndex < 0)
                curIndex = static_cast<int>(container.size() - 1);
            return *this;
        }
    };

    enum class PointDirection {
        PREV,
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
    
    std::string& menuUp()
    {
        return menuContainer.up();
    }

    std::string& menuDown()
    {

        return menuContainer.down();
    }

    levelUnit_t& menuLeft()
    {


        return menuContainer.left();

    }

    levelUnit_t& menuRight()
    {

        return menuContainer.right();
    }

private:
    std::shared_ptr<nlohmann::json> mapJsonData;

    
    std::vector<pointVector_t> currentMapRange;
    int currentMap;
    std::string currentLevelName;
    DoubleListContainer<levelUnit_t> currentLevelContainer;


    struct MenuContainer {
        std::map<std::string, DoubleListContainer<levelUnit_t>> levelContainer;
        DoubleListContainer<std::string> mapContainer;

        MenuContainer() {}
        MenuContainer(std::map<std::string, DoubleListContainer<levelUnit_t>> &srcLevelContainer, DoubleListContainer<std::string> &srcMapContainer) : levelContainer(srcLevelContainer), mapContainer(srcMapContainer) {}

        MenuContainer& operator=(MenuContainer &src) noexcept
        {
            if (this != &src) {
                levelContainer = src.levelContainer;
                mapContainer = src.mapContainer;
            }
            
            return *this;
        }

        MenuContainer& operator=(MenuContainer&& src) noexcept
        {
            if (this != &src) {
                levelContainer = std::move(src.levelContainer);
                mapContainer = std::move(src.mapContainer);
            }
            return *this;
        }

        std::string &up()
        {
            --mapContainer;
            return *mapContainer.get();
        }

        std::string &down()
        {
            ++mapContainer;
            return *mapContainer.get();
        }

        levelUnit_t& left()
        {
            --levelContainer[*mapContainer.get()];

            return *levelContainer[*mapContainer.get()].get();

        }

        levelUnit_t& right()
        {
            ++levelContainer[*mapContainer.get()];
            return *levelContainer[*mapContainer.get()].get();
        }

    };

    MenuContainer menuContainer;


};