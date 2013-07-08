#include "static_collection-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>
#include <fstream>

Static_collection::Static_collection(std::string const& name) : TaskContext(name){

  //JointState
  this->addPort("JointState", port_joint_state);
  //FriJointState
  this->addPort("FriJointState", port_fri_joint_state);

  this->addProperty("Filename", filename);
}

bool Static_collection::configureHook(){
  return true;
}

bool Static_collection::startHook(){
  return true;
}

void Static_collection::updateHook(){

  char in;
  std::cin  >> in;
  
   if (in == 'q') {
    //Stop and Write Data
    std::cout << "Stopping" << std::endl;

    std::ofstream f;
    f.open (filename.c_str());

    for (size_t ii(0); ii < (size_t) position.size(); ++ii) {
	for (size_t jj(0); jj < (size_t) 7; ++jj) {
          f << position[ii][jj] << " ";
        }
	for (size_t jj(0); jj < (size_t) 7; ++jj) {
          f << torque[ii][jj] << " ";
        }
	for (size_t jj(0); jj < (size_t) 7; ++jj) {
          f << ext_torque[ii][jj] << " ";
        }
        f << "\n";
    }
   }
   else {
    //Read Data
    port_joint_state.read(joint_state);
    port_fri_joint_state.read(fri_joint_state);

    Eigen::Matrix<float, 7, 1> cur_pos;
    Eigen::Matrix<float, 7, 1> cur_torque;
    Eigen::Matrix<float, 7, 1> cur_ext_torque;
    for (size_t ii(0); ii < (size_t) 7; ++ii) {
      cur_pos[ii] = joint_state.position[ii];
      cur_torque[ii] = fri_joint_state.gravity[ii];
      cur_ext_torque[ii] = fri_joint_state.estExtJntTrq[ii];
    }
    std::cout << "Position: " << cur_pos.transpose() << std::endl;
    std::cout << "Gravity: " << cur_torque.transpose() << std::endl;
    std::cout << "External Torque: " << cur_ext_torque.transpose() << std::endl;

    position.push_back(cur_pos);
    torque.push_back(cur_torque);
    ext_torque.push_back(cur_ext_torque);

    this->trigger();
   }
  
}

void Static_collection::stopHook() {
}

void Static_collection::cleanupHook() {
}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(Static_collection)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(Static_collection)
