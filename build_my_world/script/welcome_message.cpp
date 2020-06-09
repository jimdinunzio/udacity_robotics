#include <gazebo/gazebo.hh>

namespace gazebo
{
  class WorldPluginMyRobot : public WorldPlugin
  {
    public:
      WorldPluginMyRobot() 
	: WorldPlugin()
      {
        printf("Welcome to Jim's world!\n");
      }

      void Load(physics:: WorldPtr _world, sdf::ElementPtr _sdf)
      {
        
      }
  };
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)

}
