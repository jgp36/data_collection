#include "data_collection-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>

Data_collection::Data_collection(std::string const& name) : TaskContext(name){
  std::cout << "Data_collection constructed !" <<std::endl;
}

bool Data_collection::configureHook(){
  std::cout << "Data_collection configured !" <<std::endl;
  return true;
}

bool Data_collection::startHook(){
  std::cout << "Data_collection started !" <<std::endl;
  return true;
}

void Data_collection::updateHook(){
  std::cout << "Data_collection executes updateHook !" <<std::endl;
}

void Data_collection::stopHook() {
  std::cout << "Data_collection executes stopping !" <<std::endl;
}

void Data_collection::cleanupHook() {
  std::cout << "Data_collection cleaning up !" <<std::endl;
}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(Data_collection)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(Data_collection)
