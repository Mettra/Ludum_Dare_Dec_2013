#include <string>
#include <vector>

enum State
{
  STATE_LEVEL,
  STATE_RELOAD,
  STATE_NEWLEVEL,
  STATE_QUIT
};

class StateManager
{
public:
  void Initialize();
  void LoadLevel(std::string levelName)
  {
    this->levelName = levelName;
    nextState = STATE_NEWLEVEL;
  }

  void NextLevel();

  void Update();
  class TileLevel *GetLevel(){ return level; }


private:
  class TileLevel *level;

  unsigned int levelCount;

  State state;
  State nextState;
  State prevState;

  std::string levelName;
  std::vector<std::string> levels;
};