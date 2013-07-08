#ifndef OROCOS_DATA_COLLECTION_COMPONENT_HPP
#define OROCOS_DATA_COLLECTION_COMPONENT_HPP

#include <rtt/RTT.hpp>

class Data_collection : public RTT::TaskContext{
  public:
    Data_collection(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
};
#endif
