#include "static_collection-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>
#include <fstream>

Static_collection::Static_collection(std::string const& name) : TaskContext(name){

  //JointState
  this->addPort("JointState", port_joint_state);
  //FriJointState
  this->addPort("FriJointState", port_fri_joint_state);
  this->addPort("MassMatrix", port_mass_matrix);

  this->addPort("fromKRL", port_from_krl);
  this->addPort("toKRL", port_to_krl);

  this->addProperty("Filename", filename);
}

bool Static_collection::configureHook(){

  for (size_t ii(0); ii < (size_t) FRI_USER_SIZE; ++ii) {
    to_krl.realData[ii] = 0.0f;
    to_krl.intData[ii] = 0;
  }
  to_krl.boolData = 0;
  to_krl.fill = 0;

  return true;
}

bool Static_collection::startHook(){
  return true;
}

void Static_collection::updateHook(){

  if (port_from_krl.read(from_krl) == NewData ) {

   if (from_krl.intData[15] == 1 && to_krl.intData[15] == 0) {
    //Read Data
    port_joint_state.read(joint_state);
    port_fri_joint_state.read(fri_joint_state);
    port_mass_matrix.read(mass_matrix);

    Eigen::Matrix<float, 7, 1> cur_pos;
    Eigen::Matrix<float, 7, 1> cur_torque;
    for (size_t ii(0); ii < (size_t) 7; ++ii) {
      cur_pos[ii] = joint_state.position[ii];
      cur_torque[ii] = fri_joint_state.gravity[ii];
    }
    Eigen::Matrix<float, 49, 1> cur_mass;
    for (size_t ii(0); ii < (size_t) 49; ++ii) {
      cur_mass[ii] = mass_matrix.mass[ii];
    }
    std::cout << "Position: " << cur_pos.transpose() << std::endl;
    std::cout << "Gravity: " << cur_torque.transpose() << std::endl;
    std::cout << "Mass: " << cur_mass.transpose() << std::endl;

    position.push_back(cur_pos);
    torque.push_back(cur_torque);
    mass.push_back(cur_mass);
    
    to_krl.intData[15] = 1;
   }
  else if (from_krl.intData[15] == 0 && to_krl.intData[15] == 1) {
    to_krl.intData[15] = 0;
  }

  }
    port_to_krl.write(to_krl);
  
}

void Static_collection::stopHook() {

   std::ofstream f;
    f.open (filename.c_str());
    f.precision(10);

    for (size_t ii(0); ii < (size_t) position.size(); ++ii) {
	for (size_t jj(0); jj < (size_t) 7; ++jj) {
          f << position[ii][jj] << " ";
        }
	for (size_t jj(0); jj < (size_t) 7; ++jj) {
          f << torque[ii][jj] << " ";
        }
	for (size_t jj(0); jj < (size_t) 49; ++jj) {
          f << mass[ii][jj] << " ";
        }
        f << "\n";
    }

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
