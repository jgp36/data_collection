#ifndef OROCOS_STATIC_COLLECTION_COMPONENT_HPP
#define OROCOS_STATIC_COLLECTION_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <lwr_fri/typekit/Types.hpp>
#include <sensor_msgs/typekit/Types.hpp>
#include <Eigen/Geometry>

#include <kuka_lwr_fri/friComm.h>
#include <kuka_lwr_fri/typekit/Types.hpp>

using namespace RTT;

class Static_collection : public RTT::TaskContext{
  public:
    Static_collection(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

    //Ports and messages
    InputPort<sensor_msgs::JointState> port_joint_state;
    sensor_msgs::JointState joint_state;
    InputPort<lwr_fri::FriJointState> port_fri_joint_state;
    lwr_fri::FriJointState fri_joint_state;
    InputPort<lwr_fri::MassMatrix> port_mass_matrix;
    lwr_fri::MassMatrix mass_matrix;

    InputPort<tFriKrlData> port_from_krl;
    OutputPort<tFriKrlData> port_to_krl;

    tFriKrlData from_krl;
    tFriKrlData to_krl;

    std::vector< Eigen::Matrix<float, 7, 1> > position;
    std::vector< Eigen::Matrix<float, 7, 1> > torque;
    std::vector< Eigen::Matrix<float, 49, 1> > mass;

    std::string filename;
};
#endif

